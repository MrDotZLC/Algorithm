/*
 * @lc app=leetcode id=322 lang=cpp
 *
 * [322] Coin Change
 *
 * https://leetcode.com/problems/coin-change/description/
 *
 * algorithms
 * Medium (46.75%)
 * Likes:    20454
 * Dislikes: 522
 * Total Accepted:    2.6M
 * Total Submissions: 5.5M
 * Testcase Example:  '[1,2,5]\n11'
 *
 * You are given an integer array coins representing coins of different
 * denominations and an integer amount representing a total amount of money.
 * 
 * Return the fewest number of coins that you need to make up that amount. If
 * that amount of money cannot be made up by any combination of the coins,
 * return -1.
 * 
 * You may assume that you have an infinite number of each kind of coin.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: coins = [1,2,5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: coins = [2], amount = 3
 * Output: -1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: coins = [1], amount = 0
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= coins.length <= 12
 * 1 <= coins[i] <= 2^31 - 1
 * 0 <= amount <= 10^4
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
    int coinChange1(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> memo(n, vector<int>(amount + 1, -1));
        auto dfs = [&](auto &dfs, int i, int remaining) -> int {
            if (i < 0) {
                return remaining == 0 ? 0 : INT_MAX / 2;
            }
            int &ans = memo[i][remaining];
            if (ans != -1) {
                return ans;
            }
            if (remaining < coins[i]) {
                return ans = dfs(dfs, i - 1, remaining);
            }
            return ans = min(dfs(dfs, i - 1, remaining),
                             dfs(dfs, i, remaining - coins[i]) + 1);
        };
        int ans = dfs(dfs, n - 1, amount);
        return ans == INT_MAX / 2 ? -1 : ans;
    }
    
    // DP递推
    int coinChange2(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> f(n + 1, vector<int>(amount + 1, INT_MAX / 2));
        f[0][0] = 0;
        for (int i = 0; i < n; i++) {
            int v = coins[i];
            for (int j = 0; j <= amount; j++) {
                if (j < v) {
                    f[i + 1][j] = f[i][j];
                } else {
                    f[i + 1][j] = min(f[i][j], f[i + 1][j - v] + 1);
                }
            }
        }
        int ans = f[n][amount];
        return ans < INT_MAX / 2 ? ans : -1;
    }

    // DP递推+空间优化
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> f(amount + 1, INT_MAX / 2);
        f[0] = 0;
        for (int i = 0; i < n; i++) {
            int v = coins[i];
            for (int j = v; j <= amount; j++) {
                f[j] = min(f[j], f[j - v] + 1);
            }
        }
        int ans = f[amount];
        return ans < INT_MAX / 2 ? ans : -1;
    }
};
// @lc code=end

