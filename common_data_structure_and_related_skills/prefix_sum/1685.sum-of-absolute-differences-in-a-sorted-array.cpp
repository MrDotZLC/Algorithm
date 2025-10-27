/*
 * @lc app=leetcode id=1685 lang=cpp
 *
 * [1685] Sum of Absolute Differences in a Sorted Array
 *
 * https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/description/
 *
 * algorithms
 * Medium (68.11%)
 * Likes:    2162
 * Dislikes: 81
 * Total Accepted:    125.6K
 * Total Submissions: 184.3K
 * Testcase Example:  '[2,3,5]'
 *
 * You are given an integer array nums sorted in non-decreasing order.
 * 
 * Build and return an integer array result with the same length as nums such
 * that result[i] is equal to the summation of absolute differences between
 * nums[i] and all the other elements in the array.
 * 
 * In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j <
 * nums.length and j != i (0-indexed).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,5]
 * Output: [4,3,5]
 * Explanation: Assuming the arrays are 0-indexed, then
 * result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
 * result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
 * result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,4,6,8,10]
 * Output: [24,15,13,15,21]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 10^5
 * 1 <= nums[i] <= nums[i + 1] <= 10^4
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size(), total = reduce(nums.begin(), nums.end(), 0);
        vector<int> sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + nums[i]; 
            // nums[0] = i * nums[i] - sum  [i] + (total - sum[i]) - (n - i) * nums[i];
            nums[i] = total - 2 * sum[i] + (2 * i - n) * nums[i];
        }
        return nums;
    }
};
// @lc code=end

