/*
 * @lc app=leetcode id=473 lang=cpp
 *
 * [473] Matchsticks to Square
 *
 * https://leetcode.com/problems/matchsticks-to-square/description/
 *
 * algorithms
 * Medium (41.01%)
 * Likes:    3960
 * Dislikes: 310
 * Total Accepted:    199.2K
 * Total Submissions: 483.4K
 * Testcase Example:  '[1,1,2,2,2]'
 *
 * You are given an integer array matchsticks where matchsticks[i] is the
 * length of the i^th matchstick. You want to use all the matchsticks to make
 * one square. You should not break any stick, but you can link them up, and
 * each matchstick must be used exactly one time.
 * 
 * Return true if you can make this square and false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: matchsticks = [1,1,2,2,2]
 * Output: true
 * Explanation: You can form a square with length 2, one side of the square
 * came two sticks with length 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: matchsticks = [3,3,3,3,4]
 * Output: false
 * Explanation: You cannot find a way to form a square with all the
 * matchsticks.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= matchsticks.length <= 15
 * 1 <= matchsticks[i] <= 10^8
 * 
 * 
 */
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        int total = reduce(matchsticks.begin(), matchsticks.end(), 0, plus());
        int r= total / 4;
        if (4 * r != total) {
            return false;
        }

        ranges::sort(matchsticks, greater<>());

        int n = matchsticks.size(), vis = 0;
        unordered_map<int, bool> memo;
        auto dfs = [&](auto &dfs, int sum) -> bool {
            if (sum == total) {
                return true;
            }

            if (memo.count(vis)) {
                return memo[vis];
            }

            for (int j = 0; j < n; j++) {
                if (((vis >> j) & 1) || (r - sum % r) < matchsticks[j]) {
                    continue;
                }

                vis ^= 1 << j;
                if (dfs(dfs, sum + matchsticks[j])) {
                    return true;
                }
                vis ^= 1 << j;
                if ((sum % r) == 0) break; // 剪枝1：新边添加失败，后面的长度也都会失败
                while (j + 1 < n && matchsticks[j] == matchsticks[j + 1]) { // 剪枝2：跳过失败相同的长度
                    j++;
                }
            }
            memo[vis] = false;
            return false;
        };
        return dfs(dfs, 0);
    }
};
// @lc code=end

