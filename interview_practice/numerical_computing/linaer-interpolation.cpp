#include <cmath>
#include <iostream>
#include <iomanip>

// lerp = Linear Interpolation
// bilerp = Bilinear Interpolation

// 单线性插值-公式实现：等价于 C++20 的 std::lerp
float lerp(float a, float b, float t) {
    return (1.0f - t) * a + t * b;
}

// 单线性插值-普通计算
float lerp_case(float x0, float y0, float x1, float y1, float x) {
    if (x0 == x1) return y0;
    float t = (x - x0) / (x1 - x0);
    return lerp(y0, y1, t);
}

// 双线性插值-公式实现：
// 等价于 两次横向 lerp 和一次纵向 lerp（或者 2 纵向 + 1 横向）
float bilerp(float Q00, float Q10, float Q01, float Q11, 
    float tx, float ty) {
    float R0 = lerp(Q00, Q10, tx);
    float R1 = lerp(Q01, Q11, tx);
    return lerp(R0, R1, ty);
}

// 双线性插值-图像采样：
// 图像本质是离散二维数组，很多操作会产生非整数坐标，故需要线性插值。
float sampler_bilinear(const float* img, int W, int H, float u, float v) {
    auto camp = [](int low, int high, float x) -> int {
        int ix = static_cast<int>(std::floor(x));
        return std::max(low, std::min(ix, high));
    };
    // 取距离（u，v）最近的四个坐标。floor(x)+1=floor(x+1)
    int x0 = camp(0, W - 1, u);
    int x1 = camp(0, W - 1, u + 1);
    int y0 = camp(0, H - 1, v);
    int y1 = camp(0, H - 1, v + 1);

    // x 方向的便宜比例，即归一化距离
    float tx = u - std::floor(u);
    float ty = v - std::floor(v);

    int Q00 = img[y0 * W + x0];
    int Q10 = img[y0 * W + x1];
    int Q01 = img[y1 * W + x0];
    int Q11 = img[y1 * W + x1];

    return bilerp(Q00, Q10, Q01, Q11, tx, ty);
}

int main() {
    std::cout << std::fixed << std::setprecision(3);

    // --------------------------------------------------
    // Test 1: lerp_case
    //
    // x:
    //
    // 0 -------- 10
    //
    // y:
    //
    // 100 ------ 200
    //
    // x=5 => y=150
    // --------------------------------------------------

    std::cout << "===== lerp_case =====\n";

    std::cout << "lerp_case(0,100,10,200,5) = "
              << lerp_case(0, 100, 10, 200, 5) << "\n\n";


    // --------------------------------------------------
    // Test 2: sampler_bilinear
    //
    // 图像:
    //
    // y=0:
    // 10 20
    //
    // y=1:
    // 30 40
    //
    // 坐标:
    //
    // (0,0)       => 10
    // (1,0)       => 20
    // (0,1)       => 30
    // (1,1)       => 40
    // (0.5,0.5)   => 25
    //
    // --------------------------------------------------

    std::cout << "===== sampler_bilinear =====\n";

    float img[] = {10, 20, 30, 40};

    int W = 2;
    int H = 2;

    std::cout << "sample(0,0) = "
              << sampler_bilinear(img, W, H, 0.0f, 0.0f) << "\n";

    std::cout << "sample(1,0) = "
              << sampler_bilinear(img, W, H, 1.0f, 0.0f) << "\n";

    std::cout << "sample(0,1) = "
              << sampler_bilinear(img, W, H, 0.0f, 1.0f) << "\n";

    std::cout << "sample(1,1) = "
              << sampler_bilinear(img, W, H, 1.0f, 1.0f) << "\n";

    std::cout << "sample(0.5,0.5) = "
              << sampler_bilinear(img, W, H, 0.5f, 0.5f) << "\n";

    std::cout << "sample(0.25,0.25) = "
              << sampler_bilinear(img, W, H, 0.25f, 0.25f) << "\n";

    return 0;
}