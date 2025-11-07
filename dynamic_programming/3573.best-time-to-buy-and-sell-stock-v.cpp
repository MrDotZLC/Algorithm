/*
 * @lc app=leetcode id=3573 lang=cpp
 *
 * [3573] Best Time to Buy and Sell Stock V
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/description/
 *
 * algorithms
 * Medium (39.61%)
 * Likes:    103
 * Dislikes: 18
 * Total Accepted:    17.7K
 * Total Submissions: 42.8K
 * Testcase Example:  '[1,7,9,8,2]\n2'
 *
 * You are given an integer array prices where prices[i] is the price of a
 * stock in dollars on the i^th day, and an integer k.
 * 
 * You are allowed to make at most k transactions, where each transaction can
 * be either of the following:
 * 
 * 
 * 
 * Normal transaction: Buy on day i, then sell on a later day j where i < j.
 * You profit prices[j] - prices[i].
 * 
 * 
 * Short selling transaction: Sell on day i, then buy back on a later day j
 * where i < j. You profit prices[i] - prices[j].
 * 
 * 
 * 
 * Note that you must complete each transaction before starting another.
 * Additionally, you can't buy or sell on the same day you are selling or
 * buying back as part of a previous transaction.
 * 
 * Return the maximum total profit you can earn by making at most k
 * transactions.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [1,7,9,8,2], k = 2
 * 
 * Output: 14
 * 
 * Explanation:
 * We can make $14 of profit through 2 transactions:
 * 
 * 
 * A normal transaction: buy the stock on day 0 for $1 then sell it on day 2
 * for $9.
 * A short selling transaction: sell the stock on day 3 for $8 then buy back on
 * day 4 for $2.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
 * 
 * Output: 36
 * 
 * Explanation:
 * We can make $36 of profit through 3 transactions:
 * 
 * 
 * A normal transaction: buy the stock on day 0 for $12 then sell it on day 2
 * for $19.
 * A short selling transaction: sell the stock on day 3 for $19 then buy back
 * on day 4 for $8.
 * A normal transaction: buy the stock on day 5 for $1 then sell it on day 6
 * for $19.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= prices.length <= 10^3
 * 1 <= prices[i] <= 10^9
 * 1 <= k <= prices.length / 2
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
    long long maximumProfit1(vector<int>& prices, int k) {
        int n = prices.size();
        vector memo(n, vector<array<long long, 3>>(k + 1, {-1, -1, -1}));
        auto dfs = [&](this auto &&dfs, int i, int chance,
                       int state) -> long long {
            if (chance < 0) {
                return LLONG_MIN / 2;
            }
            if (i < 0) {
                return state != 0 ? LLONG_MIN / 2 : 0;
            }
            long long &res = memo[i][chance][state];
            if (res != -1) {
                return res;
            }

            if (state == 1) {
                return res =
                           max(dfs(i - 1, chance, 1),
                               dfs(i - 1, chance - 1, 0) - prices[i]);
            }
            if (state == 2) {
                return res =
                           max(dfs(i - 1, chance, 2),
                               dfs(i - 1, chance - 1, 0) + prices[i]);
            }
            return res = max({dfs(i - 1, chance, 0),
                              dfs(i - 1, chance, 1) + prices[i],
                              dfs(i - 1, chance, 2) - prices[i]});
        };
        return dfs(n - 1, k, 0);
    }

    // DP+空间优化
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        vector<array<long long, 3>> f(k + 2, {INT_MIN / 2, INT_MIN / 2, INT_MIN / 2});
        for (int j = 1; j <= k + 1; j++) {
            f[j][0] = 0;
        }
        for (int p : prices) {
            for (int j = k + 1; j > 0; j--) {
                f[j][0] = max({f[j][0], f[j][1] + p, f[j][2] - p});
                f[j][1] = max(f[j][1], f[j - 1][0] - p);
                f[j][2] = max(f[j][2], f[j - 1][0] + p);
            }
        }
        return f[k + 1][0];
    }
};
// @lc code=end

