/*
 * @lc app=leetcode id=795 lang=cpp
 *
 * [795] Number of Subarrays with Bounded Maximum
 *
 * https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/description/
 *
 * algorithms
 * Medium (54.09%)
 * Likes:    2389
 * Dislikes: 131
 * Total Accepted:    82K
 * Total Submissions: 151.5K
 * Testcase Example:  '[2,1,4,3]\n2\n3'
 *
 * Given an integer array nums and two integers left and right, return the
 * number of contiguous non-empty subarrays such that the value of the maximum
 * array element in that subarray is in the range [left, right].
 * 
 * The test cases are generated so that the answer will fit in a 32-bit
 * integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,1,4,3], left = 2, right = 3
 * Output: 3
 * Explanation: There are three subarrays that meet the requirements: [2], [2,
 * 1], [3].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,9,2,5,6], left = 2, right = 8
 * Output: 7
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 0 <= left <= right <= 10^9
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int ans = 0, i0 = -1, i1 = -1;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[r] > right) {
                i0 = r;
            } else if (nums[r] >= left) {
                i1 = r;
            }
            if (i0 < i1) {
                ans += i1 - i0;
            }
        }
        return ans;
    }
};
// @lc code=end

