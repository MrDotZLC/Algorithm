/*
 * @lc app=leetcode id=1493 lang=cpp
 *
 * [1493] Longest Subarray of 1's After Deleting One Element
 *
 * https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description/
 *
 * algorithms
 * Medium (69.35%)
 * Likes:    4281
 * Dislikes: 94
 * Total Accepted:    443.5K
 * Total Submissions: 639.4K
 * Testcase Example:  '[1,1,0,1]'
 *
 * Given a binary array nums, you should delete one element from it.
 * 
 * Return the size of the longest non-empty subarray containing only 1's in the
 * resulting array. Return 0 if there is no such subarray.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,0,1]
 * Output: 3
 * Explanation: After deleting the number in position 2, [1,1,1] contains 3
 * numbers with value of 1's.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,1,1,0,1,1,0,1]
 * Output: 5
 * Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1]
 * longest subarray with value of 1's is [1,1,1,1,1].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,1,1]
 * Output: 2
 * Explanation: You must delete one element.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums[i] is either 0 or 1.
 * 
 * 
 */
#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution {
    /**
     * 1. silding window (√)
     * 2. recurrence
     */
public:
    int longestSubarray(vector<int>& nums) {
        int res = 0, l = 0;
        bool has_zero = false;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[r] == 0) {
                while (has_zero) {
                    if (nums[l++] == 0) {
                        break;
                    }
                }
                has_zero = true;
            }
            res = max(res, r - l + 1);
        }
        return res - 1;
    }
};
// @lc code=end

