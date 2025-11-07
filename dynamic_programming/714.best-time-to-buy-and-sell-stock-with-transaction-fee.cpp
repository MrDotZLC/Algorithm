/*
 * @lc app=leetcode id=714 lang=cpp
 *
 * [714] Best Time to Buy and Sell Stock with Transaction Fee
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
 *
 * algorithms
 * Medium (70.78%)
 * Likes:    7538
 * Dislikes: 231
 * Total Accepted:    533.2K
 * Total Submissions: 747.7K
 * Testcase Example:  '[1,3,2,8,4,9]\n2'
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the i^th day, and an integer fee representing a transaction fee.
 * 
 * Find the maximum profit you can achieve. You may complete as many
 * transactions as you like, but you need to pay the transaction fee for each
 * transaction.
 * 
 * Note:
 * 
 * 
 * You may not engage in multiple transactions simultaneously (i.e., you must
 * sell the stock before you buy again).
 * The transaction fee is only charged once for each stock purchase and
 * sale.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [1,3,2,8,4,9], fee = 2
 * Output: 8
 * Explanation: The maximum profit can be achieved by:
 * - Buying at prices[0] = 1
 * - Selling at prices[3] = 8
 * - Buying at prices[4] = 4
 * - Selling at prices[5] = 9
 * The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [1,3,7,5,10,3], fee = 3
 * Output: 6
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= prices.length <= 5 * 10^4
 * 1 <= prices[i] < 5 * 10^4
 * 0 <= fee < 5 * 10^4
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
    int maxProfit1(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<array<int, 2>> memo(n, {-1, -1});
        auto dfs = [&](this auto &&dfs, int i, bool hold) -> int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            int &res = memo[i][hold];
            if (res != -1) {
                return res;
            } 
            if (hold) {
                return res = max(dfs(i - 1, true), dfs(i - 1, false) - prices[i] - fee);
            }
            return res = max(dfs(i - 1, false), dfs(i - 1, true) + prices[i]);
        };
        return dfs(n - 1, false);
    }

    // DP+空间优化
    // 记忆化递归
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size(), f0 = 0, f1 = INT_MIN;
        for (int p : prices) {
            int new_f0 = max(f0, f1 + p);
            f1 = max(f1, f0 - p - fee);
            f0 = new_f0;
        }
        return f0;
    }
};
// @lc code=end

