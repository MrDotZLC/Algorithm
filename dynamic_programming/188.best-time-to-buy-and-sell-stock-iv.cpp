/*
 * @lc app=leetcode id=188 lang=cpp
 *
 * [188] Best Time to Buy and Sell Stock IV
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (47.58%)
 * Likes:    7895
 * Dislikes: 223
 * Total Accepted:    657.8K
 * Total Submissions: 1.4M
 * Testcase Example:  '2\n[2,4,1]'
 *
 * You are given an integer array prices where prices[i] is the price of a
 * given stock on the i^th day, and an integer k.
 * 
 * Find the maximum profit you can achieve. You may complete at most k
 * transactions: i.e. you may buy at most k times and sell at most k times.
 * 
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: k = 2, prices = [2,4,1]
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit
 * = 4-2 = 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: k = 2, prices = [3,2,6,5,0,3]
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit
 * = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3),
 * profit = 3-0 = 3.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= 100
 * 1 <= prices.length <= 1000
 * 0 <= prices[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化递归
    int maxProfit1(int k, vector<int>& prices) {
        int n = prices.size();
        vector memo(n, vector<array<int, 2>>(k + 1, {-1, -1}));
        auto dfs = [&](this auto &&dfs, int i, int chance, bool hold) -> int {
            if (chance < 0) {
                return INT_MIN / 2;
            }
            if (i < 0) {
                return hold ? INT_MIN / 2 : 0;
            }
            int &res = memo[i][chance][hold];
            if (res != -1) {
                return res;
            }
            if (hold) {
                return res = max(dfs(i - 1, chance, true), dfs(i - 1, chance - 1, false) - prices[i]);
            }
            return res = max(dfs(i - 1, chance, false), dfs(i - 1, chance, true) + prices[i]);
        };
        return dfs(n - 1, k, false);
    }

    // DP+空间优化
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<array<int, 2>> f(k + 2, {INT_MIN / 2, INT_MIN / 2});
        for (int j = 1; j <= k + 1; j++) {
            f[j][0] = 0;
        }
        for (int p : prices) {
            for (int j = k + 1; j > 0; j--) {
                f[j][0] = max(f[j][0], f[j][1] + p);
                f[j][1] = max(f[j][1], f[j - 1][0] - p);
            }
        }
        return f[k + 1][0];
    }
};
// @lc code=end

