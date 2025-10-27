/*
 * @lc app=leetcode id=70 lang=cpp
 *
 * [70] Climbing Stairs
 *
 * https://leetcode.com/problems/climbing-stairs/description/
 *
 * algorithms
 * Easy (53.60%)
 * Likes:    23844
 * Dislikes: 996
 * Total Accepted:    4.6M
 * Total Submissions: 8.6M
 * Testcase Example:  '2'
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 45
 * 
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归 ETL O(2^n) O(n)
    int climbStairs1(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        return climbStairs1(n - 1) + climbStairs1(n - 2);
    }
    // DP递归+哈希缓存 ETL O(2^n) O(n)
    int climbStairs2(int n) {
        unordered_map<int, int> cache;

        auto iter = [&](auto &iter, int n) -> int {
            if (n == 0 || n == 1) {
                return 1;
            }
            int ans = 0;
            if (cache[n]) {
                ans = cache[n];
            } else {
                ans = climbStairs2(n - 1) + climbStairs2(n - 2);
                cache[n] = ans;
            } 
            return ans;
        };
        return iter(iter, n);
    }

    // DP递归+数组缓存 ETL O(2^n) O(n)
    int climbStairs3(int n) {
        vector<int> cache(n + 1, 0);

        auto iter = [&](auto &iter, int n) -> int {
            if (n == 0 || n == 1) {
                return 1;
            }
            int ans = 0;
            if (cache[n]) {
                ans = cache[n];
            } else {
                ans = climbStairs3(n - 1) + climbStairs3(n - 2);
                cache[n] = ans;
            } 
            return ans;
        };
        return iter(iter, n);
    }
    // DP递推+缓存 DP递推+变量缓存 O(n) O(n)
    int climbStairs4(int n) {
        vector<int> f(n + 1, 0);
        f[0] = f[1] = 1;
        for (int i = 2; i <= n; i++) {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[n];
    }
    // DP递推+变量缓存 O(n) O(1)
    int climbStairs5(int n) {
        int f0 = 1, f1 = 1;
        for (int i = 2; i <= n; i++) {
            int t = f1;
            f1 = f1 + f0;
            f0 = t;
        }
        return f1;
    }

    // 矩阵快速幂 O(logn) O(1)
    // | f(i) | = |1 1||f(i-1)|
    // |f(i-1)|   |1 0||f(i-2)|
    // 即，
    // F(i) = M*F(i-1)
    // F(n) = (M^n)*F(0)
    // F(0) = | f(0) | = |1|
    //        | f(-1)|   |0|
    using matrix = vector<vector<long long>>;
    int climbStairs(int n) {
        matrix m = {
            {1, 1},
            {1, 0}
        };
        matrix f0 = {{1}, {0}};
        matrix fn = pow_mul(m, n, f0);
        return fn[0][0];
    }

    matrix mul(matrix &a, matrix &b) {
        int n = a.size(), m = b[0].size();
        matrix c = matrix(n, vector<long long>(m));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < a[i].size(); k++) {
                if (a[i][k] == 0) {
                    continue;
                }
                for (int j = 0; j < m; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

    matrix pow_mul(matrix a, int n, matrix &f0) {
        matrix ans = f0;
        while (n) {
            if (n & 1) {
                ans = mul(ans, a);
            }
            a = mul(a, a);
            n >>= 1;
        }
        return ans;
    }
};
// @lc code=end

