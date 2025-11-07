/*
 * @lc app=leetcode id=123 lang=cpp
 *
 * [123] Best Time to Buy and Sell Stock III
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (51.54%)
 * Likes:    10414
 * Dislikes: 218
 * Total Accepted:    877.2K
 * Total Submissions: 1.7M
 * Testcase Example:  '[3,3,5,0,0,3,1,4]'
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the i^th day.
 * 
 * Find the maximum profit you can achieve. You may complete at most two
 * transactions.
 * 
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit
 * = 3-0 = 3.
 * Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 =
 * 3.
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit
 * = 5-1 = 4.
 * Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
 * are engaging multiple transactions at the same time. You must sell before
 * buying again.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= prices.length <= 10^5
 * 0 <= prices[i] <= 10^5
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
    int maxProfit1(vector<int>& prices) {
        int n = prices.size();
        vector memo(n, vector<array<int, 2>>(3, {-1, -1}));
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
        return dfs(n - 1, 2, false);
    }

    // DP+空间优化
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<array<int, 2>> f(4, {INT_MIN / 2, INT_MIN / 2});
        for (int j = 1; j <= 3; j++) {
            f[j][0] = 0;
        }
        for (int p : prices) {
            for (int j = 3; j > 0; j--) {
                f[j][0] = max(f[j][0], f[j][1] + p);
                f[j][1] = max(f[j][1], f[j - 1][0] - p);
            }
        }
        return f[3][0];
    }
};
// @lc code=end

