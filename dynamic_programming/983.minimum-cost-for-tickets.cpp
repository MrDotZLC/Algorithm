/*
 * @lc app=leetcode id=983 lang=cpp
 *
 * [983] Minimum Cost For Tickets
 *
 * https://leetcode.com/problems/minimum-cost-for-tickets/description/
 *
 * algorithms
 * Medium (67.43%)
 * Likes:    8718
 * Dislikes: 185
 * Total Accepted:    454.4K
 * Total Submissions: 674.3K
 * Testcase Example:  '[1,4,6,7,8,20]\n[2,7,15]'
 *
 * You have planned some train traveling one year in advance. The days of the
 * year in which you will travel are given as an integer array days. Each day
 * is an integer from 1 to 365.
 * 
 * Train tickets are sold in three different ways:
 * 
 * 
 * a 1-day pass is sold for costs[0] dollars,
 * a 7-day pass is sold for costs[1] dollars, and
 * a 30-day pass is sold for costs[2] dollars.
 * 
 * 
 * The passes allow that many days of consecutive travel.
 * 
 * 
 * For example, if we get a 7-day pass on day 2, then we can travel for 7 days:
 * 2, 3, 4, 5, 6, 7, and 8.
 * 
 * 
 * Return the minimum number of dollars you need to travel every day in the
 * given list of days.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: days = [1,4,6,7,8,20], costs = [2,7,15]
 * Output: 11
 * Explanation: For example, here is one way to buy passes that lets you travel
 * your travel plan:
 * On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
 * On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3,
 * 4, ..., 9.
 * On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
 * In total, you spent $11 and covered all the days of your travel.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
 * Output: 17
 * Explanation: For example, here is one way to buy passes that lets you travel
 * your travel plan:
 * On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1,
 * 2, ..., 30.
 * On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
 * In total, you spent $17 and covered all the days of your travel.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= days.length <= 365
 * 1 <= days[i] <= 365
 * days is in strictly increasing order.
 * costs.length == 3
 * 1 <= costs[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    int mincostTickets1(vector<int>& days, vector<int>& costs) {
        int last_day = days.back();
        unordered_set<int> day_set(days.begin(), days.end());
        vector<int> memo(last_day + 1);
        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i <= 0) {
                return 0;
            }
            int &res = memo[i];
            if (res) {
                return res;
            }
            if (!day_set.count(i)) {
                return res = dfs(i - 1);
            }
            return res = min({dfs(i - 1) + costs[0],
                             dfs(i - 7) + costs[1],
                             dfs(i - 30) + costs[2]});
        };
        return dfs(last_day);
    }

    // DP
    int mincostTickets2(vector<int>& days, vector<int>& costs) {
        int last_day = days.back();
        unordered_set<int> day_set(days.begin(), days.end());
        vector<int> f(last_day + 1);
        for (int i = 1; i <= last_day; i++) {
            if (!day_set.count(i)) {
                f[i] = f[i - 1];
            } else {
                f[i] = min({f[i - 1] + costs[0],
                            f[max(i - 7, 0)] + costs[1],
                            f[max(i - 30, 0)] + costs[2]});
            }
        }
        return f[last_day];
    }

    // DP + 三指针
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> f(n + 1);
        int j = 0, k = 0;
        for (int i = 0; i < n; i++) {
            int d = days[i];
            while (days[j] <= d - 7) {
                j++;
            }
            while (days[k] <= d - 30) {
                k++;
            }
            f[i + 1] = min(
                {f[i] + costs[0], f[j] + costs[1], f[k] + costs[2]});
        }
        return f[n];
    }
};
// @lc code=end

