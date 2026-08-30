#include <vector>
#include <array>
#include <stdexcept>

using Shape4 = std::array<int, 4>;

// 计算广播后的输出 shape；不可广播时抛出异常
Shape4 broadcast_shape(const Shape4 &shape_a, const Shape4 &shape_b) {
    Shape4 res;
    for (int i = 0; i < 4; ++i) {
        if (shape_a[i] == shape_b[i]) {
            res[i] = shape_a[i];
        } else if (shape_a[i] == 1) {
            res[i] = shape_b[i];
        } else if (shape_b[i] == 1) {
            res[i] = shape_a[i];
        } else {
            throw std::invalid_argument("Shapes are not broadcastable.");
        }
    }
    return res;
}

// 将线性下标 idx（基于 out_shape）转换为在 src_shape 中的线性下标
// Broadcast 维度（src_shape[d]=1）在 src 中始终取 0
size_t broadcast_index(
    size_t idx_out, const Shape4 &shape_out, const Shape4 &shape_src) {
    size_t idx_src = 0, stride_src = 1;
    for (int d = 3; d >= 0; --d) {
        size_t pos_out = idx_out %  static_cast<size_t>(shape_out[d]); // 当前维度的坐标
        idx_out    /=  static_cast<size_t>(shape_out[d]);
        size_t pos_src = (shape_src[d] == 1) ? 0 : pos_out; // Broadcast 维度强制取 0
        idx_src    += pos_src * stride_src;
        stride_src *=  static_cast<size_t>(shape_src[d]);
    }
    return idx_src;
}

// 4D Broadcast Elementwise 乘法
// 返回 out_shape 的 flat vector
std::vector<float> broadcast_mul_4d(const std::vector<float> &a,
                                    const Shape4 &shape_a,
                                    const std::vector<float> &b,
                                    const Shape4 &shape_b) {
    Shape4 shape_out = broadcast_shape(shape_a, shape_b);

    size_t total = 1;
    for (int d : shape_out) 
        total *= static_cast<size_t>(d);

    std::vector<float> out(total);
    for (size_t i = 0; i < total; ++i) {
        size_t ia = broadcast_index(i, shape_out, shape_a);
        size_t ib = broadcast_index(i, shape_out, shape_b);
        out[i] = a[ia] * b[ib];
    }

    return out;
}