#include <vector>
#include <algorithm>
#include <cmath>

void softmax_naive(std::vector<float> x) {
    float m = *std::max_element(x.begin(), x.end());

    float sum_exp = 0.0f;
    for (float& z : x) {
        z = std::exp(z - m);
        sum_exp += z;
    }

    for (float& z : x) {
        z /= sum_exp;
    }
}