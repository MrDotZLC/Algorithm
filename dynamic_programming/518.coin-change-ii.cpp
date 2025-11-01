/*
 * @lc app=leetcode id=518 lang=cpp
 *
 * [518] Coin Change II
 *
 * https://leetcode.com/problems/coin-change-ii/description/
 *
 * algorithms
 * Medium (61.84%)
 * Likes:    10033
 * Dislikes: 229
 * Total Accepted:    904.1K
 * Total Submissions: 1.5M
 * Testcase Example:  '5\n[1,2,5]'
 *
 * You are given an integer array coins representing coins of different
 * denominations and an integer amount representing a total amount of money.
 * 
 * Return the number of combinations that make up that amount. If that amount
 * of money cannot be made up by any combination of the coins, return 0.
 * 
 * You may assume that you have an infinite number of each kind of coin.
 * 
 * The answer is guaranteed to fit into a signed 32-bit integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: amount = 5, coins = [1,2,5]
 * Output: 4
 * Explanation: there are four ways to make up the amount:
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: amount = 3, coins = [2]
 * Output: 0
 * Explanation: the amount of 3 cannot be made up just with coins of 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: amount = 10, coins = [10]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= coins.length <= 300
 * 1 <= coins[i] <= 5000
 * All the values of coins are unique.
 * 0 <= amount <= 5000
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int change1(int amount, vector<int>& coins) {
        int n = coins.size();
        vector memo(n, vector<long long>(amount + 1, -1));
        auto dfs = [&](auto &dfs, int i, int remaining) -> int {
            if (i < 0) {
                return remaining == 0;
            }
            long long &ans = memo[i][remaining];
            if (ans != -1) {
                return ans;
            }
            // 不选
            ans = dfs(dfs, i - 1, remaining);
            // 选
            if (remaining >= coins[i]) {
                ans += dfs(dfs, i, remaining - coins[i]);
            }
            return ans;
        };
        int ans = dfs(dfs, n - 1, amount);
        return ans;
    }

    // DP递推+空间优化
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // 中间无意义转移会溢出报错，使用unsigned避免
        vector<unsigned> f(amount + 1);
        f[0] = 1;
        for (int i = 0; i < n; i++) {
            int c = coins[i];
            for (int j = c; j <= amount; j++) {
                f[j] += f[j - c];
            }
        }
        return f[amount];
    }
};
// @lc code=end

