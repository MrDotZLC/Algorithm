/*
 * @lc app=leetcode id=1942 lang=cpp
 *
 * [1942] The Number of the Smallest Unoccupied Chair
 *
 * https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/description/
 *
 * algorithms
 * Medium (60.40%)
 * Likes:    1427
 * Dislikes: 77
 * Total Accepted:    125.8K
 * Total Submissions: 208.4K
 * Testcase Example:  '[[1,4],[2,3],[4,6]]\n1'
 *
 * There is a party where n friends numbered from 0 to n - 1 are attending.
 * There is an infinite number of chairs in this party that are numbered from 0
 * to infinity. When a friend arrives at the party, they sit on the unoccupied
 * chair with the smallest number.
 * 
 * 
 * For example, if chairs 0, 1, and 5 are occupied when a friend comes, they
 * will sit on chair number 2.
 * 
 * 
 * When a friend leaves the party, their chair becomes unoccupied at the moment
 * they leave. If another friend arrives at that same moment, they can sit in
 * that chair.
 * 
 * You are given a 0-indexed 2D integer array times where times[i] = [arrivali,
 * leavingi], indicating the arrival and leaving times of the i^th friend
 * respectively, and an integer targetFriend. All arrival times are distinct.
 * 
 * Return the chair number that the friend numbered targetFriend will sit
 * on.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
 * Output: 1
 * Explanation: 
 * - Friend 0 arrives at time 1 and sits on chair 0.
 * - Friend 1 arrives at time 2 and sits on chair 1.
 * - Friend 1 leaves at time 3 and chair 1 becomes empty.
 * - Friend 0 leaves at time 4 and chair 0 becomes empty.
 * - Friend 2 arrives at time 4 and sits on chair 0.
 * Since friend 1 sat on chair 1, we return 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
 * Output: 2
 * Explanation: 
 * - Friend 1 arrives at time 1 and sits on chair 0.
 * - Friend 2 arrives at time 2 and sits on chair 1.
 * - Friend 0 arrives at time 3 and sits on chair 2.
 * - Friend 1 leaves at time 5 and chair 0 becomes empty.
 * - Friend 2 leaves at time 6 and chair 1 becomes empty.
 * - Friend 0 leaves at time 10 and chair 2 becomes empty.
 * Since friend 0 sat on chair 2, we return 2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == times.length
 * 2 <= n <= 10^4
 * times[i].length == 2
 * 1 <= arrivali < leavingi <= 10^5
 * 0 <= targetFriend <= n - 1
 * Each arrivali time is distinct.
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
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size(), next = 0;
        vector<tuple<int, int, int>> actions;
        int upper = times[targetFriend][0];
        for (int i = 0; i < n; i++) {
            int a = times[i][0], l = times[i][1];
            if (a <= upper) {
                actions.emplace_back(a, 1, i);
            }
            if (l <= upper) {
                actions.emplace_back(l, 0, i);
            }
        }
        ranges::sort(actions);
        priority_queue<int, vector<int>, greater<>> pq;
        vector<int> seats(n, -1); // 可用哈希表，更节省空间
        for (auto &a : actions) {
            int type = get<1>(a), id = get<2>(a);
            if (type == 1) {
                int seat = 0;
                if (pq.empty()) {
                    seat = next++;
                } else {
                    seat = pq.top();
                    pq.pop();
                }
                seats[id] = seat;
                if (id == targetFriend) {
                    break;
                }
            } else {
                pq.push(seats[id]);
            }
        }
        return seats[targetFriend];
    }
};
// @lc code=end

