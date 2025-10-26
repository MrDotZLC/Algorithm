/*
 * @lc app=leetcode id=1353 lang=cpp
 *
 * [1353] Maximum Number of Events That Can Be Attended
 *
 * https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/description/
 *
 * algorithms
 * Medium (38.57%)
 * Likes:    3908
 * Dislikes: 608
 * Total Accepted:    212.4K
 * Total Submissions: 548.5K
 * Testcase Example:  '[[1,2],[2,3],[3,4]]'
 *
 * You are given an array of events where events[i] = [startDayi, endDayi].
 * Every event i starts at startDayi and ends at endDayi.
 * 
 * You can attend an event i at any day d where startDayi <= d <= endDayi. You
 * can only attend one event at any time d.
 * 
 * Return the maximum number of events you can attend.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: events = [[1,2],[2,3],[3,4]]
 * Output: 3
 * Explanation: You can attend all the three events.
 * One way to attend them all is as shown.
 * Attend the first event on day 1.
 * Attend the second event on day 2.
 * Attend the third event on day 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: events= [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= events.length <= 10^5
 * events[i].length == 2
 * 1 <= startDayi <= endDayi <= 10^5
 * 
 * 
 */
#include <vector>
#include <queue>
#include <numeric>
#include <functional>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 开始时间分组+最小堆
    int maxEvents1(vector<vector<int>>& events) {
        int mx = 0;
        for (auto& e : events) {
            mx = max(mx, e[1]);
        }
        // 开始时间分组排序
        vector<vector<int>> groups(mx + 1);
        for (auto& e : events) {
            groups[e[0]].push_back(e[1]);
        }

        int ans = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i <= mx; i++) {
            while (!pq.empty() && pq.top() < i) {
                pq.pop();
            }

            for (int end_day : groups[i]) {
                pq.push(end_day);
            }

            if (!pq.empty()) {
                ans++;
                pq.pop();
            }
        }
        return ans;
    }

    // 结束时间排序+并查集
    int maxEvents(vector<vector<int>>& events) {
        ranges::sort(events, {}, [](auto& e) {
            return e[1];
        });
        
        int mx = events.back()[1];
        vector<int> p(mx + 2);
        ranges::iota(p, 0);

        auto find = [&](auto &find, int x) -> int {
            return x == p[x] ? x : p[x] = find(find, p[x]);
        };

        int ans = 0;
        for (auto &e : events) {
            int x = find(find, e[0]);
            if (x <= e[1]) {
                ans++;
                p[x] = x + 1; // 标记x已被占用
            }
        }
        return ans;
    }
};
// @lc code=end

