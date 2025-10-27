/*
 * @lc app=leetcode id=540 lang=cpp
 *
 * [540] Single Element in a Sorted Array
 *
 * https://leetcode.com/problems/single-element-in-a-sorted-array/description/
 *
 * algorithms
 * Medium (59.20%)
 * Likes:    12361
 * Dislikes: 227
 * Total Accepted:    1M
 * Total Submissions: 1.7M
 * Testcase Example:  '[1,1,2,3,3,4,4,8,8]'
 *
 * You are given a sorted array consisting of only integers where every element
 * appears exactly twice, except for one element which appears exactly once.
 * 
 * Return the single element that appears only once.
 * 
 * Your solution must run in O(log n) time and O(1) space.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,2,3,3,4,4,8,8]
 * Output: 2
 * Example 2:
 * Input: nums = [3,3,7,7,10,11,11]
 * Output: 10
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^5
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int k = 2, n = nums.size();
        int L = -1, R = n / k;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (nums[mid * k] != nums[mid * k + k - 1] ? R : L) = mid;
        }
        return nums[R * k];
    }
};
// @lc code=end

