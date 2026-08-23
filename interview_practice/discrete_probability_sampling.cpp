// Discrete Probability Sampling
//
// | 方法                       | 预处理复杂度 | 单次采样复杂度 |    适用场景     |
// | ---------------------------| ----------- | ------------- | --------------- |
// | 线性扫描 CDF               |    $O(n)$   |     $O(n)$     | 简单实现、小规模 |
// | Prefix Sum + Binary Search |   $O(n)$    |  $O(\log n)$  |     通用方案     |
// | Alias Method               |    $O(n)$   |    $O(1)$     |     大量采样     |
// | 拒绝采样                    |   $O(1)$   |   依赖接受率   | proposal容易生成 |
//
// 问题:
// 给定离散概率分布: p = {p0, p1, ..., p(n-1)}
// 满足: sum(p_i) = 1
// 目标: 每次采样返回下标 i，使 P(return i) = p_i
// 实现:
// 1. CDF + Linear Search
// 2. CDF + Binary Search
// 3. Rejection Sampling
// 4. Alias Method

#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

// 随机数生成器
class RandomGenerator {
public:
    RandomGenerator()
        : rng_(random_device{}()), real_dist_(0.0, 1.0) {}

    double uniform() {
        return real_dist_(rng_);
    }

    int uniform_int(int n) {
        uniform_int_distribution<int> dist(0, n - 1);
        return dist(rng_);
    }

private:
    mt19937 rng_;
    uniform_real_distribution<double> real_dist_;
};

/* 
 * 1. CDF（累计分布函数采样） + Linear Search
 *
 * 思路:
 * 构造累计概率: cdf[i] = sum(p[0...i])
 * 随机生成: u ~ U(0,1)
 * 找到第一个: cdf[i] > u
 * 返回 i
 *
 * 时间复杂度:
 * 构造: O(n)
 * 单次采样: O(n)
 */
class CDFLinearSampler {
public:
    explicit CDFLinearSampler(const vector<double> &probability) {
        double sum = 0;
        for (double p : probability) {
            sum += p;
            cdf_.push_back(sum);
        }
    }

    int sampler() {
        double u = random_.uniform();
        for (int i = 0; i < cdf_.size(); ++i) {
            if (u < cdf_[i]) {
                return i;
            }
        }
        return cdf_.size() - 1;
    }

private:
    vector<double> cdf_;
    RandomGenerator random_;
};

/* 
 * 2. CDF（累计分布函数采样） + Binary Search
 *
 * 思路:
 * 利用 cdf 单调递增，使用 lower_bound 查找第一个 cdf[i] >= u
 * 返回 i
 *
 * 时间复杂度:
 * 构造: O(n)
 * 单次采样: O(log n)
 */
class CDFBinarySampler {
public:
    explicit CDFBinarySampler(const vector<double>& probability) {
        double sum = 0.0;
        for (double p : probability) {
            sum += p;
            cdf_.emplace_back(sum);
        }
    }

    int sampler() {
        double u = random_.uniform();

        auto it = lower_bound(cdf_.begin(), cdf_.end(), u);

        return it - cdf_.begin();
    }

private:
    vector<double> cdf_;
    RandomGenerator random_;
};

/* 
 * 3. Rejection Sampling
 *
 * 思路:
 * 选中每个选项的概率相同：q_i = 1/n
 * 最大概率：p_max=max(p_i)
 * 接受概率：a_i=p_i/p_max
 * 流程：
 *  随机选择 i
 *  生成随机概率 u
 *  u < a_i，则接受 i
 *
 * 时间复杂度:
 * 构造: O(1)
 * 单次采样: 依赖接受率
 */
class RejectionSampler {
public:
    explicit RejectionSampler(const vector<double> probability)
        : p(probability) {
        p_max_ = *max_element(p.begin(), p.end());
    }

    int sampler() {
        while (true) {
            int i = random_.uniform_int(p.size());
            double accept_probability = p[i] / p_max_;
            double u = random_.uniform();
            if (u < accept_probability) {
                return i;
            }
        }
    }

private:
    vector<double> p;
    double p_max_;
    RandomGenerator random_;
};

/* 
 * 4. Alias Method
 *
 * 思路:
 * 将每个选项的概率都放大到 1 ，称作桶 scaled[i]=n*p_i
 * 不足 1 由其他大于 1 的桶补充，补充信息即 alias[i]=桶编号
 * 最大概率：p_max=max(p_i)
 * 接受概率：a_i=p_i/p_max
 * 流程：
 *  随机选择 i
 *  生成随机概率 u
 *  u < scaled[i]，则接受 i，否则接受 alias[i]
 *
 * 时间复杂度:
 * 构造: O(1)
 * 单次采样: 依赖接受率
 */
class AliasSampler {
public:
    AliasSampler(const vector<double>& probability) {
        int n = probability.size();
        p_.assign(n, 1.0);
        alias_.assign(n, 1.0);

        vector<double> scaled(n);

        for (int i = 0; i < n; ++i) {
            scaled[i] = n * probability[i];
        }

        vector<int> small;
        vector<int> large;

        for (int i = 0; i < n; ++i) {
            if (scaled[i] < 1.0) {
                small.push_back(i);
            } else {
                large.push_back(i);
            }
        }

        // 完成后，理论存在两种情况：都为空、small空；
        // 可能因为精度原因导致 small 不为空，视为补充后的概率为1
        while (!small.empty() && !large.empty()) {
            int s = small.back();
            small.pop_back();
            int l = large.back();
            large.pop_back();
            
            p_[s] = scaled[s]; // 不足 1 的不会再有操作，先初始化

            alias_[s] = l; // s 的一部分一定从 l 补，s 的别名设为 l

            scaled[l] -= 1 - scaled[s]; // l 减去“补充到 s 的部分”

            if (scaled[l] < 1.0) { // 判断补充之后，按照残留概率进行大小重分配
                small.push_back(l);
            } else {
                large.push_back(l);
            }
        }
    }

    int sampler() {
        int k = random_.uniform_int(p_.size());
        double u = random_.uniform();
        if (u < p_[k]) {
            return k;
        } else {
            return alias_[k];
        }
    }


private:
    vector<double> p_;
    vector<int> alias_;
    RandomGenerator random_;
};

/*
 * 测试
 */
int main() {
    vector<double> p = {0.1, 0.3, 0.2, 0.4};

    CDFLinearSampler sampler1(p);

    CDFBinarySampler sampler2(p);

    RejectionSampler sampler3(p);

    AliasSampler sampler4(p);

    const int N = 100000;

    vector<int> count1(4);

    vector<int> count2(4);

    vector<int> count3(4);

    vector<int> count4(4);

    for (int i = 0; i < N; i++) {
        count1[sampler1.sampler()]++;

        count2[sampler2.sampler()]++;

        count3[sampler3.sampler()]++;

        count4[sampler4.sampler()]++;
    }

    auto print = [&](const string &name, vector<int> &count) {
        cout << name << "\n";

        for (int c : count) {
            cout << fixed << to_string((double) c / N) << " ";
        }

        cout << "\n\n";
    };

    cout << "Target:\n";

    cout << "0.100 0.300 0.200 0.400\n\n";

    print("CDF Linear Search", count1);

    print("CDF Binary Search", count2);

    print("Rejection Sampling", count3);

    print("Alias Method", count4);

    return 0;
}
