/*
 * @lc app=leetcode id=3439 lang=cpp
 *
 * [3439] Reschedule Meetings for Maximum Free Time I
 *
 * https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/description/
 *
 * algorithms
 * Medium (32.19%)
 * Likes:    589
 * Dislikes: 51
 * Total Accepted:    101.7K
 * Total Submissions: 188.9K
 * Testcase Example:  '5\n1\n[1,3]\n[2,5]'
 *
 * You are given an integer eventTime denoting the duration of an event, where
 * the event occurs from time t = 0 to time t = eventTime.
 * 
 * You are also given two integer arrays startTime and endTime, each of length
 * n. These represent the start and end time of n non-overlapping meetings,
 * where the i^th meeting occurs during the time [startTime[i], endTime[i]].
 * 
 * You can reschedule at most k meetings by moving their start time while
 * maintaining the same duration, to maximize the longest continuous period of
 * free time during the event.
 * 
 * The relative order of all the meetings should stay the same and they should
 * remain non-overlapping.
 * 
 * Return the maximum amount of free time possible after rearranging the
 * meetings.
 * 
 * Note that the meetings can not be rescheduled to a time outside the
 * event.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * 
 * Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the
 * time [0, 2].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * 
 * 
 * Reschedule the meeting at [2, 4] to [1, 3], leaving no meetings during the
 * time [3, 9].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * There is no time during the event not occupied by meetings.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= eventTime <= 10^9
 * n == startTime.length == endTime.length
 * 2 <= n <= 10^5
 * 1 <= k <= n
 * 0 <= startTime[i] < endTime[i] <= eventTime
 * endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

// @lc code=start
class Solution {
public:
    /**
     * The problem is equivalent to finding the sum of 
     * the k large consecutive idle time. 
     */
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<int> idle_time(startTime.size() + 1);
        int n = idle_time.size();
        int res = 0, sum = 0;
        k = k + 1;
        idle_time[0] = startTime[0];
        idle_time[n - 1] = eventTime - endTime[n - 2];
        // calculate idle time
        for (int i = 1; i < n - 1; i++) {
            idle_time[i] = startTime[i] - endTime[i - 1];
        }

        // sliding_window
        for (int i = 0; i < n; i++) {
            sum += idle_time[i];
            if (i < k - 1) { 
                continue; 
            }
            res = max(res, sum);
            sum -= idle_time[i - k + 1];
        }

        return res;
    }

    // optimized memory
    // Use a function to calculate idle time instead of storing it in vector.
    int maxFreeTime2(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int res = 0, sum = 0;
        int n = startTime.size() + 1;
        k = k + 1;

        auto get = [&](int i) -> int {
            if (i == 0) {
                return startTime[0];
            }
            if (i == n) {
                return eventTime - endTime[n - 2];
            }
            return startTime[i] - endTime[i - 1];
        };

        for (int i = 0; i < n; i++) {
            sum += get(i);
            if (i < k - 1) {
                continue;
            }
            res = max(res, sum);
            sum -= get(i - k + 1);
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector startTime{1, 3};
    vector endTime{2, 5};
    auto res = sol.maxFreeTime(5, 1, startTime, endTime);
    cout << "res is " << res << endl;
}