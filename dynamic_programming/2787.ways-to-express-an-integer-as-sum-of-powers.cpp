/*
 * @lc app=leetcode id=2787 lang=cpp
 *
 * [2787] Ways to Express an Integer as Sum of Powers
 *
 * https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description/
 *
 * algorithms
 * Medium (33.95%)
 * Likes:    826
 * Dislikes: 40
 * Total Accepted:    115.2K
 * Total Submissions: 230.9K
 * Testcase Example:  '10\n2'
 *
 * Given two positive integers n and x.
 * 
 * Return the number of ways n can be expressed as the sum of the x^th power of
 * unique positive integers, in other words, the number of sets of unique
 * integers [n1, n2, ..., nk] where n = n1^x + n2^x + ... + nk^x.
 * 
 * Since the result can be very large, return it modulo 10^9 + 7.
 * 
 * For example, if n = 160 and x = 3, one way to express n is n = 2^3 + 3^3 +
 * 5^3.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 10, x = 2
 * Output: 1
 * Explanation: We can express n as the following: n = 3^2 + 1^2 = 10.
 * It can be shown that it is the only way to express 10 as the sum of the 2^nd
 * power of unique integers.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 4, x = 1
 * Output: 2
 * Explanation: We can express n in the following ways:
 * - n = 4^1 = 4.
 * - n = 3^1 + 1^1 = 4.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 300
 * 1 <= x <= 5
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9 + 7;
    // 快速幂
    long long qpow(int n, int x) {
        long long res = 1;
        while (x > 0) {
            if (x & 1) {
                res = res * n % MOD;
            }
            n *= n;
            x >>= 1;
        }
        return res;
    }
    // DP递归
    int numberOfWays1(int n, int x) {
        int m = ceil(pow(n, 1.0 / x));
        vector memo(m + 1, vector<long long>(n + 1, -1));
        auto dfs = [&](auto &dfs, int i, int t) -> long long {
            if (i == 0) {
                return t == 0;
            }
            long long &ans = memo[i][t];
            if (ans != -1) {
                return ans;
            }
            // 不选
            ans = dfs(dfs, i - 1, t);
            // 选
            long long candidate = qpow(i, x);
            if (t >= candidate) {
                ans += dfs(dfs, i - 1, t - candidate);
            }
            return ans;
        };
        return dfs(dfs, m, n) % MOD;
    }

    // DP递推+空间优化+剪枝
    int numberOfWays(int n, int x) {
        vector<long long> f(n + 1);
        f[0] = 1;
        int s = 0;
        for (int i = 1; qpow(i, x) <= n; i++) {
            int v = pow(i, x);
            s = min(s + v, n);
            for (int j = s; j >= v; j--) {
                f[j] += f[j - v];
            }
        }
        return f[n] % MOD;
    }
};
// @lc code=end

