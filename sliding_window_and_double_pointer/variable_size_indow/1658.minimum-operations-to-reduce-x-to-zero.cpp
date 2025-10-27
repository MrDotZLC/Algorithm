/*
 * @lc app=leetcode id=1658 lang=cpp
 *
 * [1658] Minimum Operations to Reduce X to Zero
 *
 * https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/description/
 *
 * algorithms
 * Medium (40.11%)
 * Likes:    5622
 * Dislikes: 125
 * Total Accepted:    215.1K
 * Total Submissions: 536.2K
 * Testcase Example:  '[1,1,4,2,3]\n5'
 *
 * You are given an integer array nums and an integer x. In one operation, you
 * can either remove the leftmost or the rightmost element from the array nums
 * and subtract its value from x. Note that this modifies the array for future
 * operations.
 * 
 * Return the minimum number of operations to reduce x to exactly 0 if it is
 * possible, otherwise, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,4,2,3], x = 5
 * Output: 2
 * Explanation: The optimal solution is to remove the last two elements to
 * reduce x to zero.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,6,7,8,9], x = 4
 * Output: -1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [3,2,20,1,1,3], x = 10
 * Output: 5
 * Explanation: The optimal solution is to remove the last three elements and
 * the first two elements (5 operations in total) to reduce x to zero.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 * 1 <= x <= 10^9
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <numeric>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = accumulate(nums.begin(), nums.end(), 0) - x;
        int res = INT_MAX, l = 0;
        for (int r = 0; r < nums.size(); r++) {
            sum -= nums[r];
            while (sum < 0 && l <= r) {
                sum += nums[l++];
            }
            if (!sum) {
                res = min<size_t>(res, nums.size() - (r - l + 1));
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};
// @lc code=end

