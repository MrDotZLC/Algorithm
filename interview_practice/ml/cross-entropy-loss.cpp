#include <vector>
#include <algorithm>
#include <cmath>

/**
 * 1. 单标签多分类交叉熵（可带权重）
 * 公式：L = m + log(∑_j(e^{z_j - m})) - z_label
 * 参数：
 *      z∈logit
 *      m=logit 最大值
 */
float single_label_multi_class_weighted_ce(
    const std::vector<float>& logits, int label,
    const std::vector<float>& weights, bool is_weighted) {
    float max_logit = *max_element(logits.begin(), logits.end());

    float log_sum_exp = 0.0f;
    for (float z : logits) {
        log_sum_exp += std::exp(z - max_logit);
    }
    log_sum_exp = std::log(log_sum_exp) + max_logit - logits[label];
    return (is_weighted ? weights[label] : 1) * log_sum_exp;
}

/**
 * 2. 多标签二分类交叉熵
 * 公式：L = max(0,z) + log(1 + exp(-|z|)) - y*z
 * 参数：
 *      z：logit
 *      y∈[0,1]
 */
float multi_label_binary_class_ce(const std::vector<float>& logits, 
                                  const std::vector<float>& targets) {
    float loss = 0.0f;
    for (size_t i = 0; i < logits.size(); ++i) {
        float m = std::max(0.0f, logits[i]);
        loss += m + std::log(1 + std::exp(-std::abs(logits[i]))) - targets[i];
    }
    return loss / logits.size();
}