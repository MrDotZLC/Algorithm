/*
 * @lc app=leetcode id=862 lang=cpp
 *
 * [862] Shortest Subarray with Sum at Least K
 *
 * https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/
 *
 * algorithms
 * Hard (32.31%)
 * Likes:    5060
 * Dislikes: 140
 * Total Accepted:    192.6K
 * Total Submissions: 596.2K
 * Testcase Example:  '[1]\n1'
 *
 * Given an integer array nums and an integer k, return the length of the
 * shortest non-empty subarray of nums with a sum of at least k. If there is no
 * such subarray, return -1.
 * 
 * A subarray is a contiguous part of an array.
 * 
 * 
 * Example 1:
 * Input: nums = [1], k = 1
 * Output: 1
 * Example 2:
 * Input: nums = [1,2], k = 4
 * Output: -1
 * Example 3:
 * Input: nums = [2,-1,2], k = 3
 * Output: 3
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^5 <= nums[i] <= 10^5
 * 1 <= k <= 10^9
 * 
 * 
 */
#include <vector>
#include <deque>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size(), res = INT_MAX;
        vector<long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        deque<int> q;
        for (int i = 0; i < n + 1; i++) {
            long cur = prefix[i];
            while (!q.empty() && cur - prefix[q[0]] >= k) {
                res = min(res, i - q.front());
                q.pop_front();
            }
            while (!q.empty() && prefix[q.back()] > cur) {
                q.pop_back();
            }
            q.push_back(i);
        }
        return res == INT_MAX ? -1 : res;
    }
};
// @lc code=end

