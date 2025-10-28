/*
 * @lc app=leetcode id=918 lang=cpp
 *
 * [918] Maximum Sum Circular Subarray
 *
 * https://leetcode.com/problems/maximum-sum-circular-subarray/description/
 *
 * algorithms
 * Medium (47.96%)
 * Likes:    7143
 * Dislikes: 335
 * Total Accepted:    372.9K
 * Total Submissions: 767.5K
 * Testcase Example:  '[1,-2,3,-2]'
 *
 * Given a circular integer array nums of length n, return the maximum possible
 * sum of a non-empty subarray of nums.
 * 
 * A circular array means the end of the array connects to the beginning of the
 * array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the
 * previous element of nums[i] is nums[(i - 1 + n) % n].
 * 
 * A subarray may only include each element of the fixed buffer nums at most
 * once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there
 * does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,-2,3,-2]
 * Output: 3
 * Explanation: Subarray [3] has maximum sum 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,-3,5]
 * Output: 10
 * Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [-3,-2,-3]
 * Output: -2
 * Explanation: Subarray [-2] has maximum sum -2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 1 <= n <= 3 * 10^4
 * -3 * 10^4 <= nums[i] <= 3 * 10^4
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int max_f = 0, max_s = INT_MIN; // 不可为空
        int min_f = 0, min_s = 0; // 减去最小和，就是夸边界的最大和，可为空
        int sum = 0;

        for (int x : nums) {
            max_f = max(max_f, 0) + x;
            max_s = max(max_s, max_f);
            min_f = min(min_f, 0) + x;
            min_s = min(min_s, min_f);
            sum += x;
        }
        return min_s == sum ? max_s : max(max_s, sum - min_s);
    }
};
// @lc code=end

