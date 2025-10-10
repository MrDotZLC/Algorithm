/*
 * @lc app=leetcode id=56 lang=cpp
 *
 * [56] Merge Intervals
 *
 * https://leetcode.com/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (49.59%)
 * Likes:    23955
 * Dislikes: 876
 * Total Accepted:    3.5M
 * Total Submissions: 7M
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all
 * overlapping intervals, and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into
 * [1,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: intervals = [[4,7],[1,4]]
 * Output: [[1,7]]
 * Explanation: Intervals [1,4] and [4,7] are considered overlapping.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= intervals.length <= 10^4
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 10^4
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 排序+遍历
    vector<vector<int>> merge1(vector<vector<int>>& intervals) {
        ranges::sort(intervals); // 按照左端点从小到大排序
        vector<vector<int>> ans;
        for (auto& p : intervals) {
            if (!ans.empty() && p[0] <= ans.back()[1]) { // 可以合并
                ans.back()[1] = max(ans.back()[1], p[1]); // 更新右端点最大值
            } else { // 不相交，无法合并
                ans.emplace_back(p); // 新的合并区间
            }
        }
        return ans;
    }

    // 差分
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int max_end = (*max_element(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1];
        }))[1];
        vector<int> diff(max_end * 2 + 2);
        for (auto& p : intervals) {
           diff[p[0] * 2]++;
           diff[p[1] * 2 + 1]--;
        }
        vector<vector<int>> ans;
        int start = -1, sum = 0;
        for (int i = 0; i < diff.size(); i++) {
            sum += diff[i];
            if (sum > 0) {
                if (start == -1) {
                    start = i;
                }
            } else {
                if (start != -1) {
                    ans.push_back({start / 2, i / 2});
                    start = -1;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

