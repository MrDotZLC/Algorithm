#include <vector>
#include <cmath>

// RMSNorm（无均值中心化，更高效，LLaMA 使用）
// y_i = (x_i / RMS(x)) * γ_i, RMS(x) = sqrt(1/d * Σ x_i²)
void rms_norm(std::vector<float>& x,
             const std::vector<float>& gamma,
             float eps = 1e-6f) {
    size_t d = x.size();
    float rms = 0.f;
    for (float v : x) rms += v * v;
    rms = std::sqrt(rms / static_cast<float>(d) + eps);
    float inv_std = 1.f / rms;
    for (int i = 0; i < d; ++i) {
        x[i] = x[i] * rms * gamma[i];
    }
}
