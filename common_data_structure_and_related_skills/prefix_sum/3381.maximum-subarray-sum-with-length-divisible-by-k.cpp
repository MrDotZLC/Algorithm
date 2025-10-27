/*
 * @lc app=leetcode id=3381 lang=cpp
 *
 * [3381] Maximum Subarray Sum With Length Divisible by K
 *
 * https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/description/
 *
 * algorithms
 * Medium (27.15%)
 * Likes:    180
 * Dislikes: 10
 * Total Accepted:    13.1K
 * Total Submissions: 47.5K
 * Testcase Example:  '[1,2]\n1'
 *
 * You are given an array of integers nums and an integer k.
 * 
 * Return the maximum sum of a subarray of nums, such that the size of the
 * subarray is divisible by k.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2], k = 1
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by
 * 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-1,-2,-3,-4,-5], k = 4
 * 
 * Output: -10
 * 
 * Explanation:
 * 
 * The maximum sum subarray is [-1, -2, -3, -4] which has length equal to 4
 * which is divisible by 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [-5,1,2,-3,4], k = 2
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The maximum sum subarray is [1, 2, -3, 4] which has length equal to 4 which
 * is divisible by 2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 2 * 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + nums[i];
        }

        long long ans = LLONG_MIN;
        vector<long long> min_s(k, LLONG_MAX / 2); // 防止下面减法溢出
        for (int j = 0; j < sum.size(); j++) {
            int i = j % k;
            ans = max(ans, sum[j] - min_s[i]);
            min_s[i] = min(min_s[i], sum[j]);
        }
        return ans;
    }
};
// @lc code=end

