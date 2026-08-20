// 前缀积（对数处理）
#include <vector>
using namespace std;

class PrefixProduct {
private:
    int n;
    vector<long double> _pre_log_abs; // ln(|x|) 的前缀积
    vector<int> _zero_cnt;            // 前缀零的数量：判断区间前缀积是否为0
    vector<int> _neg_cnt;             // 前缀负数数量：判断区间前缀积的正负

public:
    PrefixProduct(const vector<long long>& nums) {
        n = nums.size();
        _pre_log_abs.resize(n + 1, 0);
        _zero_cnt.resize(n + 1, 0);
        _neg_cnt.resize(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            long long v = nums[i - 1];
            _zero_cnt[i] = _zero_cnt[i - 1] + (v == 0);
            _neg_cnt[i] = _neg_cnt[i - 1] + (v < 0);
            if (v == 0) {
                _pre_log_abs[i] = _pre_log_abs[i - 1];
            } else {
                _pre_log_abs[i] = _pre_log_abs[i - 1] + logl(fabsl((long double)v));
            }
        }
    }

    // 检查区间内是否有零
    bool has_zero(int l, int r) const {
        return _zero_cnt[r] - _zero_cnt[l - 1] > 0;
    }

    // 返回区间符号：1或-1
    int range_sign(int l, int r) const {
        int negs = _neg_cnt[r] - _neg_cnt[l - 1];
        return (negs % 2 == 0) ? 1 : -1;
    }

    // 返回区间对数和
    long double range_log_abs(int l, int r) const {
        return _pre_log_abs[r] - _pre_log_abs[l - 1];
    }

    // 返回区间前缀积
    long double range_product(int l, int r) const {
        if (has_zero(l, r)) return 0;
        long double log_abs = range_log_abs(l, r);
        long double res = expl(log_abs);
        return (range_sign(l, r) == 1) ? res : -res;
    }

    // 返回十进制位数估计
    long long range_digits(int l, int r) const {
        if (has_zero(l, r)) return 0;
        long double sum_log10 = range_log_abs(l, r) / logl(10.0);
        long long digits = (long long)floor(sum_log10) + 1;
        return digits;
    }
};