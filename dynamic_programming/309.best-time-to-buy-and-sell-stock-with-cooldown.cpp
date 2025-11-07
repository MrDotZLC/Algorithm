/*
 * @lc app=leetcode id=309 lang=cpp
 *
 * [309] Best Time to Buy and Sell Stock with Cooldown
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
 *
 * algorithms
 * Medium (60.67%)
 * Likes:    9917
 * Dislikes: 347
 * Total Accepted:    708.5K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,2,3,0,2]'
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the i^th day.
 * 
 * Find the maximum profit you can achieve. You may complete as many
 * transactions as you like (i.e., buy one and sell one share of the stock
 * multiple times) with the following restrictions:
 * 
 * 
 * After you sell your stock, you cannot buy stock on the next day (i.e.,
 * cooldown one day).
 * 
 * 
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [1,2,3,0,2]
 * Output: 3
 * Explanation: transactions = [buy, sell, cooldown, buy, sell]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [1]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= prices.length <= 5000
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
    // 记忆化递归(方法一：增加冷冻期状态)
    int maxProfit1(vector<int>& prices) {
        int n = prices.size();
        vector<array<int, 3>> memo(n, {-1, -1, -1});
        auto dfs = [&](this auto &&dfs, int i, int hold) -> int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            int &res = memo[i][hold];
            if (res != -1) {
                return res;
            } 
            if (hold == 1) {
                return res = max(dfs(i - 1, 1), dfs(i - 1, 0) - prices[i]);
            }
            if (hold == 2) {
                return res = dfs(i - 1, 1) + prices[i];
            }
            return res = max(dfs(i - 1, 0), dfs(i - 1, 2));
        };
        return max(dfs(n - 1, 0), dfs(n - 1, 2));
    }

    // DP(方法一：增加冷冻期状态)
    int maxProfit2(vector<int>& prices) {
        int n = prices.size(), f0 = 0, f1 = INT_MIN, f2 = f1;
        for (int p : prices) {
            int tmp_2 = f1 + p;
            int tmp_1 = max(f1, f0 - p);
            f0 = max(f0, f2);
            f1 = tmp_1;
            f2 = tmp_2;
        }
        return max(f0, f2);
    }

    // 记忆化递归(方法二：买入时，从f_i-2_0取值)
    int maxProfit3(vector<int>& prices) {
        int n = prices.size();
        vector<array<int, 2>> memo(n, {-1, -1});
        auto dfs = [&](this auto &&dfs, int i, int hold) -> int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            int &res = memo[i][hold];
            if (res != -1) {
                return res;
            } 
            if (hold == 1) {
                return res = max(dfs(i - 1, 1), dfs(i - 2, 0) - prices[i]);
            }
            return res = max(dfs(i - 1, 0), dfs(i - 1, 1) + prices[i]);
        };
        return dfs(n - 1, 0);
    }

    // DP(方法二：买入时，从f_i-2_0取值)
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), f0 = 0, f1 = INT_MIN / 2, prev = 0;
        for (int p : prices) {
            int tmp = f0;
            f0 = max(f0, f1 + p);
            f1 = max(f1, prev - p);
            prev = tmp;
        }
        return f0;
    }
};
// @lc code=end

