#pragma once
#include "softmax_naive.cpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

// softmax_online
// m_new = max(m_old, x)
// d_new = d_old * exp(m_old - m_new) + exp(x - m_new)

std::vector<float> softmax_online(const std::vector<float>& x) {
    float m = 0.f;
    float d = 0.f;

    for (const float& v : x) {
        float m_old = m;
        m = std::max(m, v);
        d = d * std::exp(m_old - m) + std::exp(v - m);
    }

    std::vector<float> res(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        res[i] = std::exp(x[i] - m) / d;
    }
    return res;
}

int main() {
    std::vector<float> x = {1.0f, 2.0f, 3.0f};

    auto y = softmax_online(x);

    float sum = 0.0f;

    for (float p : y) {
        std::cout << p << " ";
        sum += p;
    }

    std::cout << "\n";

    std::cout << "sum = " << sum << "\n";

    softmax_naive(x);

    sum = 0.0f;
    
    for (float p : y) {
        std::cout << p << " ";
        sum += p;
    }

    std::cout << "\n";

    std::cout << "sum_n = " << sum << "\n";

    return 0;
}