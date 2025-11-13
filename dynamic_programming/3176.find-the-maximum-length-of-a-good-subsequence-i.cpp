/*
 * @lc app=leetcode id=3176 lang=cpp
 *
 * [3176] Find the Maximum Length of a Good Subsequence I
 *
 * https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/description/
 *
 * algorithms
 * Medium (31.72%)
 * Likes:    160
 * Dislikes: 92
 * Total Accepted:    22.3K
 * Total Submissions: 69.4K
 * Testcase Example:  '[1,2,1,1,3]\n2'
 *
 * You are given an integer array nums and a non-negative integer k. A sequence
 * of integers seq is called good if there are at most k indices i in the range
 * [0, seq.length - 2] such that seq[i] != seq[i + 1].
 * 
 * Return the maximum possible length of a good subsequence of nums.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,1,1,3], k = 2
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The maximum length subsequence is [1,2,1,1,3].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4,5,1], k = 0
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * The maximum length subsequence is [1,2,3,4,5,1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 500
 * 1 <= nums[i] <= 10^9
 * 0 <= k <= min(nums.length, 25)
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP+空间优化
    int maximumLength(vector<int>& nums, int k) {
        int ans = 1, n = nums.size();
        vector<vector<int>> f(k + 1, vector<int>(n));
        fill(f[0].begin(), f[0].end(), 1);
        for (int d = 0; d <= k; d++) {
            for (int i = 1; i < n; i++) {
                int x = nums[i];
                for (int j = 0; j < i; j++) {
                    if (x == nums[j]) {
                        f[d % 2][i] = max(f[d % 2][i], f[d % 2][j] + 1);
                    } else if (d > 0) {
                        f[d % 2][i] = max(f[d % 2][i], f[(d - 1) % 2][j] + 1);
                    }
                }
                ans = max(ans, f[d % 2][i]);
            }
        }
        return ans;
    }
};
// @lc code=end

