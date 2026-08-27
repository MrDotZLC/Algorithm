#include <array>
#include <cmath>

// 三维向量 {a} = (a_x, a_y, a_z)，{b} = (b_x, b_y, b_z)：
// a×b={a_y*b_z-a_z*b_y, a_z*b_x-a_x*b_z, a_x*b_y-a_y*b_x}

using Vec3 = std::array<float, 3>;

Vec3 cross(const Vec3& a, const Vec3& b) {
    return {
        a[1]*b[2] - a[2]*b[1],   // i 分量
        a[2]*b[0] - a[0]*b[2],   // j 分量
        a[0]*b[1] - a[1]*b[0]    // k 分量
    };
}