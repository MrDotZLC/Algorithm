/*
 * @lc app=leetcode id=2944 lang=cpp
 *
 * [2944] Minimum Number of Coins for Fruits
 *
 * https://leetcode.com/problems/minimum-number-of-coins-for-fruits/description/
 *
 * algorithms
 * Medium (47.16%)
 * Likes:    305
 * Dislikes: 79
 * Total Accepted:    22K
 * Total Submissions: 45.8K
 * Testcase Example:  '[3,1,2]'
 *
 * You are given an 0-indexed integer array prices where prices[i] denotes the
 * number of coins needed to purchase the (i + 1)^th fruit.
 * 
 * The fruit market has the following reward for each fruit:
 * 
 * 
 * If you purchase the (i + 1)^th fruit at prices[i] coins, you can get any
 * number of the next i fruits for free.
 * 
 * 
 * Note that even if you can take fruit j for free, you can still purchase it
 * for prices[j - 1] coins to receive its reward.
 * 
 * Return the minimum number of coins needed to acquire all the fruits.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [3,1,2]
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * 
 * Purchase the 1^st fruit with prices[0] = 3 coins, you are allowed to take
 * the 2^nd fruit for free.
 * Purchase the 2^nd fruit with prices[1] = 1 coin, you are allowed to take the
 * 3^rd fruit for free.
 * Take the 3^rd fruit for free.
 * 
 * 
 * Note that even though you could take the 2^nd fruit for free as a reward of
 * buying 1^st fruit, you purchase it to receive its reward, which is more
 * optimal.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [1,10,1,1]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * Purchase the 1^st fruit with prices[0] = 1 coin, you are allowed to take the
 * 2^nd fruit for free.
 * Take the 2^nd fruit for free.
 * Purchase the 3^rd fruit for prices[2] = 1 coin, you are allowed to take the
 * 4^th fruit for free.
 * Take the 4^t^h fruit for free.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: prices = [26,18,6,12,49,7,45,45]
 * 
 * Output: 39
 * 
 * Explanation:
 * 
 * 
 * Purchase the 1^st fruit with prices[0] = 26 coin, you are allowed to take
 * the 2^nd fruit for free.
 * Take the 2^nd fruit for free.
 * Purchase the 3^rd fruit for prices[2] = 6 coin, you are allowed to take the
 * 4^th, 5^th and 6^th (the next three) fruits for free.
 * Take the 4^t^h fruit for free.
 * Take the 5^t^h fruit for free.
 * Purchase the 6^th fruit with prices[5] = 7 coin, you are allowed to take the
 * 8^th and 9^th fruit for free.
 * Take the 7^t^h fruit for free.
 * Take the 8^t^h fruit for free.
 * 
 * 
 * Note that even though you could take the 6^th fruit for free as a reward of
 * buying 3^rd fruit, you purchase it to receive its reward, which is more
 * optimal.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= prices.length <= 1000
 * 1 <= prices[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    int minimumCoins1(vector<int>& prices) {
        int n = prices.size();
        vector<int> memo((n + 1) / 2, INT_MAX);
        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i >= (n + 1) / 2) {
                return prices[i + 1];
            }
            int &res = memo[i];
            if (res != INT_MAX) {
                return res;
            }
            for (int j = i + 1; j <= 2 * i + 1; j++) {
                res = min(res, dfs(j));
            }
            res += prices[i - 1];
            return res;
        };
        return dfs(1);
    }

    // DP
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        for (int i = (n + 1) / 2 - 1; i > 0; i--) {
            prices[i - 1] += *min_element(prices.begin() + i, prices.begin() + i * 2 + 1);
        }
        return prices[0];
    }
};
// @lc code=end

