#include <vector>
#include <cmath>

float kl_divergency_loss(const std::vector<float> &teacher,
            const std::vector<float> &student) {
    float loss = 0.0f;

    for (size_t i = 0; i < teacher.size(); ++i) {
        if (teacher[i] > 0) {
            loss += teacher[i] * std::log(teacher[i] / student[i]);
        }
    }

    return loss;
}