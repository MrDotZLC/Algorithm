#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

/**
 * 1. layernorm-naive
 * 公式：μ=mean(x)，σ^2=(1/N)*∑(x-μ)^2，\hat(x)=(x-μ)/sqrt(σ^2-ε)
 *      y=γ\hat(x)+β
 */
std::vector<float> layer_norm_naive(const std::vector<float>& x, 
    const std::vector<float>& gamma,
    const std::vector<float>& beta,
    float eps = 1e-5f) {
    const size_t N = x.size();
    // mean μ 均值
    float mean = std::accumulate(x.begin(), x.end(), 0.0f) / N;

    // variance σ^2 方差
    float variance = 0.f;
    for (float v : x) {
        float diff = v - mean;
        variance += diff * diff;
    }
    variance /= N;

    std::vector<float> res(N);
    // norm + project 归一化+仿射变换
    float inv_std = 1.0f / std::sqrt(variance + eps);
    for (size_t i = 0; i < N; ++i) {
        res[i] = gamma[i] * ((x[i] - mean) * inv_std) + beta[i];
    }
    return res;
}

/**
 * 2. Welford online
 * 公式：δ1=xi-M_{i-1}，Mi=M_{i-1}+δ1/i，δ2=xi-Mi=(i-1)*δ1/i
 *       Si=S_{i-1}+δ1δ2
 */
std::vector<float> layer_norm_welford_online(const std::vector<float>& x, 
    const std::vector<float>& gamma,
    const std::vector<float>& beta,
    float eps = 1e-5f) {
    size_t cnt = 0;
    float mean = 0.f;
    float sum_squared_error = 0.f;

    size_t N = x.size();

    for (float v : x) {
        cnt++;
        float d1 = v - mean;
        mean += d1 / cnt;
        float d2 = v - mean;
        sum_squared_error += d1 * d2;
    }

    float variance = sum_squared_error / N;

    std::vector<float> res(N);
    // norm + project 归一化+仿射变换
    float inv_std = 1.0f / std::sqrt(variance + eps);
    for (size_t i = 0; i < N; ++i) {
        res[i] = gamma[i] * ((x[i] - mean) * inv_std) + beta[i];
    }
    return res;
}

/**
 * 3. layernorm welford 并行合并
 * 公式：两个分块 $(d_a, M_a, S_a)$ 和 $(d_b, M_b, S_b)$ 合并
 *      n = n_a + n_b, δ = M_b - M_a, M = M_a + δ * (n_b / n)
 *      S_ab = S_a + S_b + (n_a * n_b * delta ^ 2) / (n_a + n_b)
 */

struct WelfordState {
    size_t cnt = 0;
    float mean = 0.f;
    float sum_squared_error = 0.f;

    void update(float x) {
        ++cnt;
        float d1 = x - mean;
        mean += d1 / cnt;
        float d2 = x - mean;
        sum_squared_error += d1 * d2;
    }
};

void merge(WelfordState& merged, const WelfordState& param) {
    if (merged.cnt == 0) {
        merged = param;
        return;
    }
    if (param.cnt == 0) return;

    size_t na = merged.cnt;
    size_t nb = param.cnt;

    size_t n = na + nb;
    float d = param.mean - merged.mean;
    float mean = merged.mean + d * nb / n;
    float sum_squared_error = 
        merged.sum_squared_error + param.sum_squared_error + 
        na * nb * d * d / n;
    merged.cnt = n;
    merged.mean = mean;
    merged.sum_squared_error = sum_squared_error;
}

std::vector<float> layer_norm_welford_online_merge(
    const std::vector<float>& x, const std::vector<float>& gamma, 
    const std::vector<float>& beta, size_t block_size, 
    float eps = 1e-5f) {
    
    size_t N = x.size();
    
    if (block_size == 0 || N == 0) return {};

    std::vector<WelfordState> states;
    size_t num_block = (N + block_size - 1) / block_size;

    // 逐 block 计算LN
    for (int i = 0; i < num_block; ++i) {
        WelfordState local;
        size_t start = block_size * i;
        size_t end = std::min(start + block_size, N);

        for (size_t j = start; j < end; ++j) {
            local.update(x[j]);
        }
        
        states.emplace_back(local);
    }

    // merge 所有 block
    WelfordState global;
    for (auto& s : states) {
        merge(global, s);
    }

    float mean = global.mean;
    float variance = global.sum_squared_error / global.cnt;
    float inv_std = 1.0f / std::sqrt(variance + eps);

    std::vector<float> res(N);
    // norm + project 归一化+仿射变换
    for (size_t i = 0; i < N; ++i) {
        res[i] = gamma[i] * ((x[i] - mean) * inv_std) + beta[i];
    }
    return res;
}