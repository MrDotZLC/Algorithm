/*
 * @lc app=leetcode id=673 lang=cpp
 *
 * [673] Number of Longest Increasing Subsequence
 *
 * https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
 *
 * algorithms
 * Medium (50.21%)
 * Likes:    7201
 * Dislikes: 284
 * Total Accepted:    310.8K
 * Total Submissions: 611.8K
 * Testcase Example:  '[1,3,5,4,7]'
 *
 * Given an integer array nums, return the number of longest increasing
 * subsequences.
 * 
 * Notice that the sequence has to be strictly increasing.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and
 * [1, 3, 5, 7].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,2,2,2,2]
 * Output: 5
 * Explanation: The length of the longest increasing subsequence is 1, and
 * there are 5 increasing subsequences of length 1, so output 5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2000
 * -10^6 <= nums[i] <= 10^6
 * The answer is guaranteed to fit inside a 32-bit integer.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 0, mx = 0;
        vector<int> f(n, 1), cnt(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (f[j] + 1 > f[i]) {
                        f[i] = f[j] + 1;
                        cnt[i] = cnt[j];
                    } else if (f[j] + 1 == f[i]) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            mx = max(mx, f[i]);
        }
        for (int i = 0; i < n; i++) {
            if (f[i] == mx) {
                ans += cnt[i];
            }
        }
        return ans;
    }
};
// @lc code=end

