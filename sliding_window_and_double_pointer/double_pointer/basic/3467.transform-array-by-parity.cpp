/*
 * @lc app=leetcode id=3467 lang=cpp
 *
 * [3467] Transform Array by Parity
 *
 * https://leetcode.com/problems/transform-array-by-parity/description/
 *
 * algorithms
 * Easy (89.54%)
 * Likes:    61
 * Dislikes: 4
 * Total Accepted:    60.7K
 * Total Submissions: 67.7K
 * Testcase Example:  '[4,3,2,1]'
 *
 * You are given an integer array nums. Transform nums by performing the
 * following operations in the exact order specified:
 * 
 * 
 * Replace each even number with 0.
 * Replace each odd numbers with 1.
 * Sort the modified array in non-decreasing order.
 * 
 * 
 * Return the resulting array after performing these operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,3,2,1]
 * 
 * Output: [0,0,1,1]
 * 
 * Explanation:
 * 
 * 
 * Replace the even numbers (4 and 2) with 0 and the odd numbers (3 and 1) with
 * 1. Now, nums = [0, 1, 0, 1].
 * After sorting nums in non-descending order, nums = [0, 0, 1, 1].
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,5,1,4,2]
 * 
 * Output: [0,0,1,1,1]
 * 
 * Explanation:
 * 
 * 
 * Replace the even numbers (4 and 2) with 0 and the odd numbers (1, 5 and 1)
 * with 1. Now, nums = [1, 1, 1, 0, 0].
 * After sorting nums in non-descending order, nums = [0, 0, 1, 1, 1].
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 1000
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
    vector<int> transformArray(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            if (nums[l] % 2 == 1) {
                nums[l] = 1;
                swap(nums[l], nums[r]);
                r--;
            } else {
                nums[l] = 0;
                l++;
            }
        } 
        return nums;
    }

    vector<int> transformArray2(vector<int>& nums) {
        int e = 0, o = nums.size() - 1;
        while (e <= o) {
            if (nums[e] % 2 == 0) {
                nums[e] = 0;
                e++;
            } else if (nums[o] % 2 == 1) {
                nums[o] = 1;
                o--;
            } else {
                swap(nums[e], nums[o]);
                nums[e] = 0;
                nums[o] = 1;
                e++;
                o--;
            }
        } 
        return nums;
    }
};
// @lc code=end

