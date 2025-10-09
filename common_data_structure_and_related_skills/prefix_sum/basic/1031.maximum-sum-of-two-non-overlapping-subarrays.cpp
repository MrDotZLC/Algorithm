/*
 * @lc app=leetcode id=1031 lang=cpp
 *
 * [1031] Maximum Sum of Two Non-Overlapping Subarrays
 *
 * https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/description/
 *
 * algorithms
 * Medium (60.33%)
 * Likes:    2641
 * Dislikes: 86
 * Total Accepted:    81.4K
 * Total Submissions: 134.4K
 * Testcase Example:  '[0,6,5,2,2,5,1,9,4]\n1\n2'
 *
 * Given an integer array nums and two integers firstLen and secondLen, return
 * the maximum sum of elements in two non-overlapping subarrays with lengths
 * firstLen and secondLen.
 * 
 * The array with length firstLen could occur before or after the array with
 * length secondLen, but they have to be non-overlapping.
 * 
 * A subarray is a contiguous part of an array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
 * Output: 20
 * Explanation: One choice of subarrays is [9] with length 1, and [6,5] with
 * length 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
 * Output: 29
 * Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9]
 * with length 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
 * Output: 31
 * Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [0,3,8]
 * with length 3.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= firstLen, secondLen <= 1000
 * 2 <= firstLen + secondLen <= 1000
 * firstLen + secondLen <= nums.length <= 1000
 * 0 <= nums[i] <= 1000
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<int> presum(n + 1);

        for (int i = 0; i < n; i++) {
            presum[i + 1] = presum[i] + nums[i];
        }
        
        // i的左边维护最大值，枚举右边
        int ans = 0, max_sum_a = 0, max_sum_b = 0;
        for (int i = firstLen + secondLen; i <= n; i++) {
            max_sum_a =
                max(max_sum_a, presum[i - secondLen] -
                                   presum[i - firstLen - secondLen]);
            max_sum_b =
                max(max_sum_b, presum[i - firstLen] -
                                   presum[i - firstLen - secondLen]);
            ans = max(
                ans,
                max(max_sum_a + presum[i] - presum[i - secondLen],
                    max_sum_b + presum[i] - presum[i - firstLen]));
        }
        return ans;
    }
};
// @lc code=end

