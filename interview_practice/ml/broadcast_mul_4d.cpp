#include <vector>
#include <array>
#include <stdexcept>

using Shape4 = std::array<int, 4>;

// 计算广播后的输出 shape；不可广播时抛出异常
Shape4 broadcast_shape(const Shape4 &a_shape, const Shape4 &b_shape) {
    Shape4 res;
    for (int i = 0; i < 4; ++i) {
        if (a_shape[i] == b_shape[i]) {
            res[i] = a_shape[i];
        } else if (a_shape[i] == 1) {
            res[i] = b_shape[i];
        } else if (b_shape[i] == 1) {
            res[i] = a_shape[i];
        } else {
            throw std::invalid_argument("Shapes are not broadcastable.");
        }
    }
    return res;
}

// 将线性下标 idx（基于 out_shape）转换为在 src_shape 中的线性下标
// Broadcast 维度（src_shape[d]=1）在 src 中始终取 0
size_t broadcast_index(
    size_t out_idx, const Shape4 &out_shape, const Shape4 &src_shape) {
    size_t src_idx = 0, src_stride = 1;
    for (int d = 3; d >= 0; --d) {
        size_t out_pos = out_idx %  static_cast<size_t>(out_shape[d]); // 当前维度的坐标
        out_idx    /=  static_cast<size_t>(out_shape[d]);
        size_t src_pos = (src_shape[d] == 1) ? 0 : out_pos; // Broadcast 维度强制取 0
        src_idx    += src_pos * src_stride;
        src_stride *=  static_cast<size_t>(src_shape[d]);
    }
    return src_idx;
}

// 4D Broadcast Elementwise 乘法
// 返回 out_shape 的 flat vector
std::vector<float> broadcast_mul_4d(const std::vector<float> &a,
                                    const Shape4 &a_shape,
                                    const std::vector<float> &b,
                                    const Shape4 &b_shape) {
    Shape4 out_shape = broadcast_shape(a_shape, b_shape);

    size_t total = 1;
    for (int d : out_shape) 
        total *= static_cast<size_t>(d);

    std::vector<float> out(total);
    for (size_t i = 0; i < total; ++i) {
        size_t ia = broadcast_index(i, out_shape, a_shape);
        size_t ib = broadcast_index(i, out_shape, b_shape);
        out[i] = a[ia] * b[ib];
    }

    return out;
}