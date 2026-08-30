#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <cmath>

using Mat = std::vector<std::vector<float>>;

// 单个 Expert：Linear -> ReLU -> Linear
std::vector<float> expert_forward(
    const std::vector<float>& x,
    const Mat& w_a, const Mat& w_b
) {
    const int d = static_cast<int>(x.size());
    const int hidden = static_cast<int>(w_a.size());

    if (hidden == 0)
        throw std::invalid_argument("w_a is empty.");
    if (static_cast<int>(w_a[0].size()) != d)
        throw std::invalid_argument("w_a dimension mismatch.");
    if (static_cast<int>(w_b.size()) != d)
        throw std::invalid_argument("w_a dimension mismatch.");

    // h = ReLU(w_a * x) = (hidden, d) (d)
    std::vector<float> h(hidden, 0.f);
    for (int i = 0; i < hidden; ++i) {
        for (int j = 0; j < d; ++j) {
            h[i] += w_a[i][j] * x[j];
        }
        h[i] = std::max(0.f, h[i]);
    }

    // y = w_b * h = (d, hidden) (hidden)
    std::vector<float> y(d, 0.f);
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < hidden; ++j) {
            y[i] += w_b[i][j] * h[j];
        }
    }

    return y;
}

// MoE：Router -> Top-K -> Softmax -> Experts -> Weighted Sum
std::vector<float> moe_forward(
    const std::vector<float>& x,
    const Mat& w_router, 
    const std::vector<std::pair<Mat, Mat>>& experts,
    int topk = 2
) {
    int d = static_cast<int>(x.size());
    int num_experts = static_cast<int>(experts.size());

    if (num_experts == 0)
        throw std::invalid_argument("no experts.");
    if (topk <= 0 || topk > num_experts)
        throw std::invalid_argument("invalid topk.");
    if (static_cast<int>(w_router.size()) != num_experts)
        throw std::invalid_argument("w_router dimension mismatch.");

    // 1. logits = w_router * x = (num_experts, d) (d)
    std::vector<float> logits(num_experts, 0.f);
    for (int i = 0; i < num_experts; ++i) {
        for (int j = 0; j < d; ++j) {
            logits[i] += w_router[i][j] * x[j];
        }
    }

    // ------------------------------------------------------------
    // 1. Router
    // logits[e] = router_w[e] · x
    // ------------------------------------------------------------
    std::vector<int> indices(num_experts);
    std::iota(indices.begin(), indices.end(), 0);

    std::partial_sort(indices.begin(), indices.begin() + topk, 
        indices.end(), [&](int a, int b) {
            return logits[a] > logits[b];
        });

    indices.resize(topk);

    // ------------------------------------------------------------
    // 3. Stable Softmax on Top-K logits
    // ------------------------------------------------------------
    float m = -INFINITY;
    for (int idx : indices) {
        m = std::max(m, logits[idx]);
    }
    std::vector<float> weights(topk, 0.f);
    float sum = 0.f;
    for (int i = 0; i < topk; ++i) {
        weights[i] = std::exp(logits[indices[i]] - m);
        sum += weights[i];
    }
    for (float& w : weights) {
        w /= sum;
    }

    // ------------------------------------------------------------
    // 4. Expert Forward + Weighted Sum
    // ------------------------------------------------------------
    std::vector<float> output(d, 0.f);
    for (int i = 0; i < topk; ++i) {
        int idx = indices[i];
        auto expert_out = expert_forward(
            x, experts[idx].first, experts[idx].second);
        for (int j = 0; j < d; ++j) {
            output[j] += weights[i] * expert_out[j];
        }
    }

    return output;
}