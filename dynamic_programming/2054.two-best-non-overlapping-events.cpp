/*
 * @lc app=leetcode id=2054 lang=cpp
 *
 * [2054] Two Best Non-Overlapping Events
 *
 * https://leetcode.com/problems/two-best-non-overlapping-events/description/
 *
 * algorithms
 * Medium (60.84%)
 * Likes:    1549
 * Dislikes: 59
 * Total Accepted:    109.6K
 * Total Submissions: 180.2K
 * Testcase Example:  '[[1,3,2],[4,5,2],[2,4,3]]'
 *
 * You are given a 0-indexed 2D integer array of events where events[i] =
 * [startTimei, endTimei, valuei]. The i^th event starts at startTimei and ends
 * at endTimei, and if you attend this event, you will receive a value of
 * valuei. You can choose at most two non-overlapping events to attend such
 * that the sum of their values is maximized.
 * 
 * Return this maximum sum.
 * 
 * Note that the start time and end time is inclusive: that is, you cannot
 * attend two events where one of them starts and the other ends at the same
 * time. More specifically, if you attend an event with end time t, the next
 * event must start at or after t + 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: events = [[1,3,2],[4,5,2],[2,4,3]]
 * Output: 4
 * Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: events = [[1,3,2],[4,5,2],[1,5,5]]
 * Output: 5
 * Explanation: Choose event 2 for a sum of 5.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: events = [[1,5,3],[1,5,1],[6,6,5]]
 * Output: 8
 * Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= events.length <= 10^5
 * events[i].length == 3
 * 1 <= startTimei <= endTimei <= 10^9
 * 1 <= valuei <= 10^6
 * 
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    typedef pair<int, int> PII;
    int maxTwoEvents(vector<vector<int>>& events) {
        int ans = 0, pre_max = 0;
        ranges::sort(events);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        for (int i = 0; i < events.size(); i++) {
            int s = events[i][0], e = events[i][1], v = events[i][2];
            while (!pq.empty() && pq.top().first < s) {
                auto x = pq.top();
                pq.pop();
                pre_max = max(pre_max, x.second);
            }
            ans = max({ans, v, pre_max + v});
            pq.emplace(e, v);
        }
        return ans;
    }
};
// @lc code=end

