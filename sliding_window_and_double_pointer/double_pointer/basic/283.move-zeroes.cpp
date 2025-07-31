/*
 * @lc app=leetcode id=283 lang=cpp
 *
 * [283] Move Zeroes
 *
 * https://leetcode.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (62.90%)
 * Likes:    18190
 * Dislikes: 537
 * Total Accepted:    4.2M
 * Total Submissions: 6.8M
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * Given an integer array nums, move all 0's to the end of it while maintaining
 * the relative order of the non-zero elements.
 * 
 * Note that you must do this in-place without making a copy of the array.
 * 
 * 
 * Example 1:
 * Input: nums = [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 * Example 2:
 * Input: nums = [0]
 * Output: [0]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^4
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 * 
 * Follow up: Could you minimize the total number of operations done?
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int stack_size = 0;
        for (int x : nums) {
            if (x) {
                nums[stack_size++] = x; // 把 x 入栈
            }
        }
        fill(nums.begin() + stack_size, nums.end(), 0);
    }
    
    void moveZeroes2(vector<int>& nums) {
        int l = 0;
        for (int &r: nums) {
            if (r != 0) {
                swap(r, nums[l++]);
            }
        }
    }
};
// @lc code=end

