/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 *
 * https://leetcode.com/problems/sort-colors/description/
 *
 * algorithms
 * Medium (67.85%)
 * Likes:    20428
 * Dislikes: 727
 * Total Accepted:    3.1M
 * Total Submissions: 4.6M
 * Testcase Example:  '[2,0,2,1,1,0]'
 *
 * Given an array nums with n objects colored red, white, or blue, sort them
 * in-place so that objects of the same color are adjacent, with the colors in
 * the order red, white, and blue.
 * 
 * We will use the integers 0, 1, and 2 to represent the color red, white, and
 * blue, respectively.
 * 
 * You must solve this problem without using the library's sort function.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,0,1]
 * Output: [0,1,2]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 1 <= n <= 300
 * nums[i] is either 0, 1, or 2.
 * 
 * 
 * 
 * Follow up: Could you come up with a one-pass algorithm using only constant
 * extra space?
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
    // insert sort(double pointer)
    void sortColors(vector<int>& nums) {
        int l0 = 0, l1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) {
                nums[l1++] = 1;
            }
            if (x == 0) {
                nums[l0++] = 0;
            }
        }
    }

    // triple pointer
    void sortColors2(vector<int>& nums) {
        int l0 = 0, l1 = 0, l2 = nums.size() - 1;
        while (l1 <= l2) {
            if (nums[l1] == 0) {
                swap(nums[l0], nums[l1]);
                l0++;
                l1++;
            } else if (nums[l1] == 1) {
                l1++;
            } else {
                swap(nums[l1], nums[l2]);
                l2--;
            }
        }
    }
};
// @lc code=end

