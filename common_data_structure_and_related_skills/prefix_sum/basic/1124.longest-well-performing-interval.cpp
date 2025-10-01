/*
 * @lc app=leetcode id=1124 lang=cpp
 *
 * [1124] Longest Well-Performing Interval
 *
 * https://leetcode.com/problems/longest-well-performing-interval/description/
 *
 * algorithms
 * Medium (36.07%)
 * Likes:    1507
 * Dislikes: 122
 * Total Accepted:    41.6K
 * Total Submissions: 114.5K
 * Testcase Example:  '[9,9,6,0,6,6,9]'
 *
 * We are given hours, a list of the number of hours worked per day for a given
 * employee.
 * 
 * A day is considered to be a tiring day if and only if the number of hours
 * worked is (strictly) greater than 8.
 * 
 * A well-performing interval is an interval of days for which the number of
 * tiring days is strictly larger than the number of non-tiring days.
 * 
 * Return the length of the longest well-performing interval.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: hours = [9,9,6,0,6,6,9]
 * Output: 3
 * Explanation: The longest well-performing interval is [9,9,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: hours = [6,6,6]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= hours.length <= 10^4
 * 0 <= hours[i] <= 16
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size(), ans = 0, sum = 0;
        vector<int> pos(n + 2); // 记录前缀和首次出现的位置
        for (int i = 1; i <= n; ++i) {
            hours[i - 1] > 8 ? --sum : ++sum; // 所有和前缀和相关的都取反
            if (sum < 0) {
                ans = i;
            } else {
                if (pos[sum + 1]) {
                    ans = max(ans, i - pos[sum + 1]);
                }
                if (pos[sum] == 0) {
                    pos[sum] = i;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

