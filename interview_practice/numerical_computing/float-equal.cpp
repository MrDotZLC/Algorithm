#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>

// 绝对误差
bool float_equal_absolute(float a, float b, float eps = 1e-6) {
    return std::abs(a - b) < eps;
}

// 相对+绝对组合
bool float_equal_relative(float a, float b,
    float rel_eps = 1e-5, float abs_eps = 1e-8) {
    float diff = std::abs(a - b);
    if (diff < abs_eps) return true;
    float largest = std::max(std::abs(a), std::abs(b));
    return diff < largest * rel_eps;
}

// ULP：将 float 二进制转成有符号整数，差值即 ULP 距离
bool float_equal_ulp(float a, float b, int max_ulp = 4) {
    if (std::isnan(a) || std::isnan(b)) return false;
    if (std::signbit(a) != std::signbit(b)) {
        return a == b;
    }

    int32_t ia, ib;
    std::memcpy(&ia, &a, sizeof(float));
    std::memcpy(&ib, &b, sizeof(float));

    return std::abs(ia - ib) <= max_ulp;
}

int main() {
    std::cout << "========== 浮点比较测试 ==========\n\n";

    // 测试用例1：0.1 + 0.2 和 0.3（经典浮点误差）
    float sum = 0.1f + 0.2f;
    float target = 0.3f;
    std::cout << "测试1: 0.1f + 0.2f = " << sum << "  vs  0.3f = " << target << "\n";
    std::cout << "  直接 == : " << (sum == target ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(sum, target) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(sum, target) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(sum, target) ? "相等 ✅" : "不相等 ❌") << "\n\n";

    // 测试用例2：大数 + 微小增量（float精度不足）
    float big1 = 10000.0001f;
    float big2 = 10000.0002f;
    std::cout << "测试2: " << big1 << "  vs  " << big2 << "\n";
    std::cout << "  直接 == : " << (big1 == big2 ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(big1, big2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(big1, big2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(big1, big2) ? "相等 ✅" : "不相等 ❌") << "\n\n";

    // 测试用例3：真正不同的数
    float diff1 = 1.0f;
    float diff2 = 2.0f;
    std::cout << "测试3: " << diff1 << "  vs  " << diff2 << "\n";
    std::cout << "  直接 == : " << (diff1 == diff2 ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(diff1, diff2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(diff1, diff2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(diff1, diff2) ? "相等 ✅" : "不相等 ❌") << "\n\n";

    // 测试用例4：正零和负零
    float pos_zero = 0.0f;
    float neg_zero = -0.0f;
    std::cout << "测试4: +0.0  vs  -0.0\n";
    std::cout << "  直接 == : " << (pos_zero == neg_zero ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(pos_zero, neg_zero) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(pos_zero, neg_zero) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(pos_zero, neg_zero) ? "相等 ✅" : "不相等 ❌") << "\n\n";

    // 测试用例5：NaN
    float nan1 = std::nanf("");
    float nan2 = std::nanf("");
    std::cout << "测试5: NaN  vs  NaN\n";
    std::cout << "  直接 == : " << (nan1 == nan2 ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(nan1, nan2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(nan1, nan2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(nan1, nan2) ? "相等 ✅" : "不相等 ❌") << "\n\n";

    // 测试用例6：接近0的数
    float small1 = 1e-10f;
    float small2 = 2e-10f;
    std::cout << "测试6: " << small1 << "  vs  " << small2 << "\n";
    std::cout << "  直接 == : " << (small1 == small2 ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  绝对误差: " << (float_equal_absolute(small1, small2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  相对误差: " << (float_equal_relative(small1, small2) ? "相等 ✅" : "不相等 ❌") << "\n";
    std::cout << "  ULP     : " << (float_equal_ulp(small1, small2) ? "相等 ✅" : "不相等 ❌") << "\n";

    std::cout << "\n========== 测试完成 ==========\n";
    return 0;
}