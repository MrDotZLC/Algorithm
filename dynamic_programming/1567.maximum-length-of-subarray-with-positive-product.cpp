/*
 * @lc app=leetcode id=1567 lang=cpp
 *
 * [1567] Maximum Length of Subarray With Positive Product
 *
 * https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/description/
 *
 * algorithms
 * Medium (44.44%)
 * Likes:    2478
 * Dislikes: 78
 * Total Accepted:    108.3K
 * Total Submissions: 243.1K
 * Testcase Example:  '[1,-2,-3,4]'
 *
 * Given an array of integers nums, find the maximum length of a subarray where
 * the product of all its elements is positive.
 * 
 * A subarray of an array is a consecutive sequence of zero or more values
 * taken out of that array.
 * 
 * Return the maximum length of a subarray with positive product.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,-2,-3,4]
 * Output: 4
 * Explanation: The array nums already has a positive product of 24.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,-2,-3,-4]
 * Output: 3
 * Explanation: The longest subarray with positive product is [1,-2,-3] which
 * has a product of 6.
 * Notice that we cannot include 0 in the subarray since that'll make the
 * product 0 which is not positive.
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [-1,-2,-3,0,1]
 * Output: 2
 * Explanation: The longest subarray with positive product is [-1,-2] or
 * [-2,-3].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP+空间优化
    int getMaxLen(vector<int>& nums) {
        int n = nums.size(), f0 = nums[0] < 0, f1 = nums[0] > 0, ans = f1;
        for (int i = 1; i < n; i++) {
            if (nums[i] > 0) {
                f1++;
                f0 = f0 ? f0 + 1 : 0;
            } else if (nums[i] < 0) {
                int new_f0 = f1 + 1;
                f1 = f0 ? f0 + 1 : 0;
                f0 = new_f0;
            } else {
                f0 = f1 = 0;
            }
            ans = max({ans, f1});
        }
        return ans;
    }
};
// @lc code=end

