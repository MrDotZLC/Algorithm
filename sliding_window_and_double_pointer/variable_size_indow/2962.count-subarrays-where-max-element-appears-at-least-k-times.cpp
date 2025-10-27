/*
 * @lc app=leetcode id=2962 lang=cpp
 *
 * [2962] Count Subarrays Where Max Element Appears at Least K Times
 *
 * https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/description/
 *
 * algorithms
 * Medium (62.50%)
 * Likes:    1646
 * Dislikes: 80
 * Total Accepted:    246.9K
 * Total Submissions: 395K
 * Testcase Example:  '[1,3,2,3,3]\n2'
 *
 * You are given an integer array nums and a positive integer k.
 * 
 * Return the number of subarrays where the maximum element of nums appears at
 * least k times in that subarray.
 * 
 * A subarray is a contiguous sequence of elements within an array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,2,3,3], k = 2
 * Output: 6
 * Explanation: The subarrays that contain the element 3 at least 2 times are:
 * [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,4,2,1], k = 3
 * Output: 0
 * Explanation: No subarray contains the element 4 at least 3 times.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^6
 * 1 <= k <= 10^5
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int max = *max_element(nums.begin(), nums.end());
        int count = 0, l = 0;
        long long ans = 0;
        for (int r = 0; r < nums.size(); r++)
        {
            count += nums[r] == max;
            while (count == k) {
                count -= nums[l++] == max;
            }
            ans += l;
        }
        return ans;
    }
};
// @lc code=end

