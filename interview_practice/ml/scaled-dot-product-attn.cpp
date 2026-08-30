#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <numeric>

// softmax(Q·K^T)·V
using Mat = std::vector<std::vector<float>>;

Mat mat_mul_basic(const Mat& a, const Mat& b) {
    size_t m = a.size(), k = b.size(), n = b[0].size();
    Mat C(m, std::vector<float>(n, 0.f));
    for (size_t i = 0; i < m; ++i) {
        for (size_t p = 0; p < k; ++p) {
            for (size_t j = 0; j < n; ++j) {
                C[i][j] += a[i][p] * b[p][j];
            }
        }
    }
    return C;
}

// 矩阵转置
Mat transpose(const Mat& a) {
    size_t m = a.size(), n = a[0].size();
    Mat b(n, std::vector<float>(m, 0.f));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            b[j][i] = a[i][j];
        }
    }
    return b;
}

// 行 softmax (in-place)
void row_softmax(Mat& a) {
    for (auto& row : a) {
        float m = *max_element(row.begin(), row.end());
        float sum = 0.f;
        for (float& v : row) {
            v = std::exp(v - m);
            sum += v;
        }
        for (float& v : row) {
            v /= sum;
        }
    }
}

Mat scaled_dot_product_attn(const Mat& Q, const Mat& K, const Mat& V,
                            bool causal_mask = false) {
    size_t nq = Q.size(), dk = Q[0].size(), nk = K.size();
    float scale = 1.f / std::sqrt(dk);
    Mat KT = transpose(K);
    Mat scores = mat_mul_basic(Q, KT);
    for (auto& row : scores) {
        for (float& v : row) {
            v *= scale;
        }
    }

    if (causal_mask) {
        for (int i = 0; i < nq; ++i) {
            for (int j = i + 1; j < nq; ++j) {
                scores[i][j] = -INFINITY;
            }
        }
    }

    row_softmax(scores);

    return mat_mul_basic(scores, V);
}

void print_matrix(const Mat& mat, const std::string& name = "") {
    if (!name.empty()) {
        std::cout << name << ":\n";
    }
    for (const auto& row : mat) {
        for (float v : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << v << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main() {
    // 测试用例1：简单情况
    std::cout << "========== Test Case 1: Simple Attention ==========\n";
    
    // Q: 2个查询，每个维度3
    Mat Q = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    
    // K: 2个键，每个维度3
    Mat K = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    
    // V: 2个值，每个维度2
    Mat V = {
        {1.0f, 2.0f},
        {3.0f, 4.0f}
    };
    
    print_matrix(Q, "Q");
    print_matrix(K, "K");
    print_matrix(V, "V");
    
    Mat result = scaled_dot_product_attn(Q, K, V, false);
    print_matrix(result, "Attention Output (without causal mask)");
    
    // 测试用例2：带因果掩码
    std::cout << "========== Test Case 2: With Causal Mask ==========\n";
    
    Mat Q2 = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    
    Mat K2 = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    
    Mat V2 = {
        {1.0f, 2.0f},
        {3.0f, 4.0f},
        {5.0f, 6.0f}
    };
    
    print_matrix(Q2, "Q");
    print_matrix(K2, "K");
    print_matrix(V2, "V");
    
    Mat result2 = scaled_dot_product_attn(Q2, K2, V2, true);
    print_matrix(result2, "Attention Output (with causal mask)");
    
    // 测试用例3：非对称情况（不同序列长度）
    std::cout << "========== Test Case 3: Asymmetric (nq != nk) ==========\n";
    
    Mat Q3 = {
        {1.0f, 0.5f},
        {0.0f, 1.0f}
    };
    
    Mat K3 = {
        {1.0f, 0.0f},
        {0.5f, 1.0f},
        {0.0f, 0.5f}
    };
    
    Mat V3 = {
        {1.0f, 0.0f},
        {0.0f, 1.0f},
        {0.5f, 0.5f}
    };
    
    print_matrix(Q3, "Q (2x2)");
    print_matrix(K3, "K (3x2)");
    print_matrix(V3, "V (3x2)");
    
    Mat result3 = scaled_dot_product_attn(Q3, K3, V3, false);
    print_matrix(result3, "Attention Output (2x2)");
    
    // 测试用例4：验证 softmax 性质（行和为1）
    std::cout << "========== Test Case 4: Verify Softmax Property ==========\n";
    
    Mat Q4 = {
        {2.0f, -1.0f, 0.5f},
        {-0.5f, 1.5f, -2.0f}
    };
    
    Mat K4 = Q4;  // 自注意力
    Mat V4 = {
        {1.0f, 0.0f},
        {0.0f, 1.0f}
    };
    
    Mat result4 = scaled_dot_product_attn(Q4, K4, V4, false);
    print_matrix(result4, "Self-Attention Output");
    
    // 验证每一行的和是否接近1
    std::cout << "Verifying softmax row sums:\n";
    Mat KT4 = transpose(K4);
    Mat scores4 = mat_mul_basic(Q4, KT4);
    float scale = 1.f / std::sqrt(static_cast<float>(Q4[0].size()));
    for (auto& row : scores4) {
        for (float& v : row) {
            v *= scale;
        }
    }
    row_softmax(scores4);
    
    for (size_t i = 0; i < scores4.size(); ++i) {
        float sum = std::accumulate(scores4[i].begin(), scores4[i].end(), 0.0f);
        std::cout << "Row " << i << " sum: " << std::setprecision(6) << sum 
                  << " (should be 1.0)\n";
    }
    
    return 0;
}