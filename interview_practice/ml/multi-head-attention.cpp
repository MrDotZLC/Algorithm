#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

using Mat = std::vector<std::vector<float>>;

class MultiHeadAttention {
public:
    MultiHeadAttention(size_t d_model, size_t num_heads, const Mat& w_q, 
        const Mat& w_k, const Mat& w_v, const Mat& w_o) 
        : d_model_(d_model), num_heads_(num_heads), 
        w_q_(w_q), w_k_(w_k), w_v_(w_v), w_o_(w_o) {
        if (d_model == 0)
            throw std::invalid_argument("d_model must be > 0.");

        if (num_heads == 0)
            throw std::invalid_argument("num_heads must be > 0.");

        if (d_model % num_heads != 0)
            throw std::invalid_argument("d_model must be divisible by num_heads.");

        d_k_ = d_model / num_heads;
        d_v_ = d_k_;
    }

    // 基础矩阵乘
    Mat mat_mul_basic(const Mat& a, const Mat& b) const {
        size_t m = a.size(), k = a[0].size(), n = b[0].size();
        std::vector<std::vector<float>> res(m, std::vector<float>(n, 0));
        for (size_t i = 0; i < m; ++i) {
            for (size_t p = 0; p < k; ++p) {
                for (size_t j = 0; j < n; ++j) {
                    res[i][j] += a[i][p] * b[p][j];
                }
            }
        }
        return res;
    }

    // 转置
    Mat transpose(const Mat& a) const {
        size_t m = a.size(), n = a[0].size();
        std::vector<std::vector<float>> res(n, std::vector<float>(m, 0));
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                res[j][i] = a[i][j];
            }
        }
        return res;
    }

    // 行 softmax (in-place)
    void row_softmax(Mat& a) {
        for (auto& row : a) {
            float m = *max_element(row.begin(), row.end());
            float sum_exp = 0.f;
            for (float& v : row) {
                v = std::exp(v - m); 
                sum_exp += v;
            }
            for (float& v : row) v /= sum_exp;
        }
    }

    // attention 点乘，计算注意力分数
    Mat scaled_dot_product_attention(const Mat& q, const Mat& k, 
        const Mat& v, bool causal_mask = false) {
        size_t m = q.size(), d_k = q[0].size(), n = k.size();
        float inv_std = 1.f / sqrt(d_k);
        Mat scores = mat_mul_basic(q, transpose(k));
        for (auto& row : scores) {
            for (float& v : row) {
                v *= inv_std;
            }
        }

        if (causal_mask) {
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = i + 1; j < n; ++j) {
                    scores[i][j] = -INFINITY;
                }
            }
        }

        row_softmax(scores);

        return mat_mul_basic(scores, v);
    }

    // 线性映射
    Mat linear_projection(const Mat& input, const Mat& w) const {
        return mat_mul_basic(input, w);
    }

    // head 分割
    // 这里默认 d_k_ = d_v_，故不传入 d 维度
    std::vector<Mat> split_heads(const Mat& input) const {
        size_t seq_length = input.size();
        if (input.empty())
            throw std::invalid_argument("input cannot be empty.");

        if (input[0].size() != d_model_) {
            throw std::invalid_argument("input feature dimension != d_model.");
        }

        std::vector<Mat> heads(num_heads_);
        for (size_t h = 0; h < num_heads_; ++h) {
            heads[h] = Mat(seq_length, std::vector<float>(d_k_));
            for (size_t i = 0; i < seq_length; ++i) {
                for (size_t j = 0; j < d_k_; ++j) {
                    heads[h][i][j] = input[i][h * d_k_ + j];
                }
            }
        }
        return heads;
    }

    // head 合并
    Mat combine_heads(const std::vector<Mat>& heads) {
        if (heads.empty())
            throw std::invalid_argument("heads cannot be empty");
        if (heads.size() != num_heads_)
            throw std::invalid_argument("number of heads is incorrect.");
        
        size_t seq_length = heads[0].size();
        Mat res(seq_length, std::vector<float>(d_model_));

        for (size_t h = 0; h < num_heads_; ++h) {
            if (heads[h].size() != seq_length)
                throw std::invalid_argument(
                    "head sequence lengths are inconsistent");

            for (size_t i = 0; i < seq_length; ++i) {
                if (heads[h][i].size() != d_v_)
                    throw std::invalid_argument(
                        "head dimension is incorrect");

                for (size_t j = 0; j < d_v_; ++j) {
                    res[i][h * d_v_ + j] = heads[h][i][j];
                }
            }
        }

        return res;
    }

    // attention 前向
    Mat forward(const Mat& q_input, const Mat& k_input,
        const Mat& v_input, bool causal_mask = false) {
        if (q_input.empty() || k_input.empty() || v_input.empty())
            throw std::invalid_argument("Q/K/V cannot be empty");
        
        if (k_input.size() != v_input.size()) {
            throw std::invalid_argument(
                "K and V sequence lengths must match");
        }

        // 1. Linear projection
        Mat q = linear_projection(q_input, w_q_);
        Mat k = linear_projection(k_input, w_k_);
        Mat v = linear_projection(v_input, w_v_);
        
        // 2. split heads
        std::vector<Mat> q_heads = split_heads(q);
        std::vector<Mat> k_heads = split_heads(k);
        std::vector<Mat> v_heads = split_heads(v);

        // 3. attention
        std::vector<Mat> output_heads(num_heads_);
        for (size_t h = 0; h < num_heads_; ++h) {
            output_heads[h] = scaled_dot_product_attention(
                q_heads[h], k_heads[h], v_heads[h], causal_mask);
        }

        // 4. concat 
        Mat concat = combine_heads(output_heads);

        // 5. output projection
        Mat output = linear_projection(concat, w_o_);

        return output;
    }

private:
    size_t d_model_;
    size_t num_heads_;
    size_t d_k_;
    size_t d_v_;

    Mat w_q_, w_k_, w_v_, w_o_;
};