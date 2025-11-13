/*
 * @lc app=leetcode id=2400 lang=cpp
 *
 * [2400] Number of Ways to Reach a Position After Exactly k Steps
 *
 * https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/description/
 *
 * algorithms
 * Medium (36.23%)
 * Likes:    828
 * Dislikes: 67
 * Total Accepted:    37.8K
 * Total Submissions: 103.5K
 * Testcase Example:  '1\n2\n3'
 *
 * You are given two positive integers startPos and endPos. Initially, you are
 * standing at position startPos on an infinite number line. With one step, you
 * can move either one position to the left, or one position to the right.
 * 
 * Given a positive integer k, return the number of different ways to reach the
 * position endPos starting from startPos, such that you perform exactly k
 * steps. Since the answer may be very large, return it modulo 10^9 + 7.
 * 
 * Two ways are considered different if the order of the steps made is not
 * exactly the same.
 * 
 * Note that the number line includes negative integers.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: startPos = 1, endPos = 2, k = 3
 * Output: 3
 * Explanation: We can reach position 2 from 1 in exactly 3 steps in three
 * ways:
 * - 1 -> 2 -> 3 -> 2.
 * - 1 -> 2 -> 1 -> 2.
 * - 1 -> 0 -> 1 -> 2.
 * It can be proven that no other way is possible, so we return 3.
 * 
 * Example 2:
 * 
 * 
 * Input: startPos = 2, endPos = 5, k = 10
 * Output: 0
 * Explanation: It is impossible to reach position 5 from position 2 in exactly
 * 10 steps.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= startPos, endPos, k <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9+7;
    // 记忆化递归
    int numberOfWays1(int startPos, int endPos, int k) {
        // 剪枝
        int d = abs(startPos - endPos);
        if (d > k || d % 2 != k % 2) {
            return 0;
        }
        // 到达从i到endPos需要j步（也可以表示为到达i需要j步，写法不一样）
        vector<vector<long long>> memo(3000, vector<long long>(2000, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> long long {
            long long &res = memo[i + 1000][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            if (abs(i - endPos) > j) {
                return res;
            }
            if (j == 0) {
                return res = 1;
            }
            return res = (dfs(i - 1, j - 1) + dfs(i + 1, j - 1)) % MOD;
        };

        return dfs(startPos, k);
    }

    // DP
    int numberOfWays2(int startPos, int endPos, int k) {
        // 剪枝
        int d = abs(startPos - endPos);
        if (d > k || d % 2 != k % 2) {
            return 0;
        }
        // 到达j需要i步
        vector<vector<long long>> f(k + 1, vector<long long>(3002));
        f[1][startPos + 1 + 1000] = 1;
        f[1][startPos - 1 + 1000] = 1;
        for (int i = 2; i <= k; i++) {
            for (int j = startPos - k + 1000; j <= startPos + k + 1000; j++) {
                f[i][j] = (f[i - 1][j - 1] + f[i - 1][j + 1]) % MOD;
            }
        }
        return (int)f[k][endPos + 1000];
    }

    // 数学排列组合：设向end走了x步，有x-(k-x)=d ==> x=(d+k)/2，则从k步中任意选x步向左，即方案数
    // C_i_j = C_i-1_j + c_i-1_j-1。也可以用乘法逆元C_i_j=c_i_j-1*((i-j+1)/j)
    int numberOfWays(int startPos, int endPos, int k) {
        // 剪枝
        int d = abs(startPos - endPos);
        if (d > k || d % 2 != k % 2) {
            return 0;
        }
        vector<long long> f(k + 1);
        for (int i = 0; i <= k; i++) {
            int pre = 1;
            for (int j = 1; j <= i; j++) {
                int tmp = f[j];
                f[j] = (f[j] + pre) % MOD;
                pre = tmp;
            }
        }
        return f[(d + k) / 2];
    }
};
// @lc code=end

