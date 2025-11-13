/*
 * @lc app=leetcode id=3251 lang=cpp
 *
 * [3251] Find the Count of Monotonic Pairs II
 *
 * https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/description/
 *
 * algorithms
 * Hard (23.11%)
 * Likes:    101
 * Dislikes: 6
 * Total Accepted:    7.6K
 * Total Submissions: 32K
 * Testcase Example:  '[2,3,2]'
 *
 * You are given an array of positive integers nums of length n.
 * 
 * We call a pair of non-negative integer arrays (arr1, arr2) monotonic
 * if:
 * 
 * 
 * The lengths of both arrays are n.
 * arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <=
 * ... <= arr1[n - 1].
 * arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >=
 * ... >= arr2[n - 1].
 * arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
 * 
 * 
 * Return the count of monotonic pairs.
 * 
 * Since the answer may be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,2]
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The good pairs are:
 * 
 * 
 * ([0, 1, 1], [2, 2, 1])
 * ([0, 1, 2], [2, 2, 0])
 * ([0, 2, 2], [2, 1, 0])
 * ([1, 2, 2], [1, 1, 0])
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,5,5,5]
 * 
 * Output: 126
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n == nums.length <= 2000
 * 1 <= nums[i] <= 1000
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
    const int MOD = 1e9+7;
    // DP+前缀和
    int countOfPairs1(vector<int>& nums) {
        int ans = 0, n = nums.size(), mx = ranges::max(nums);
        vector<vector<long long>> f(2, vector<long long>(mx + 1));
        fill(f[0].begin(), f[0].begin() + nums[0] + 1, 1);
        vector<long long> pre_sum(mx + 1);
        for (int i = 1; i < n; i++) {
            // 清零当前行，防止残留旧值
            pre_sum[0] = f[(i - 1) % 2][0];
            for (int idx = 1; idx <= mx; idx++) {
                pre_sum[idx] = pre_sum[idx - 1] + f[(i - 1) % 2][idx];
            }
            fill(f[i % 2].begin(), f[i % 2].end(), 0);
            for (int j = 0; j <= nums[i]; j++) {
                int max_k =
                    min({nums[i - 1], j, nums[i - 1] - nums[i] + j});
                f[i % 2][j] = max_k >= 0 ? pre_sum[max_k] % MOD : 0;
            }
        }
        return (int) (reduce(f[(n - 1) % 2].begin(),
                             f[(n - 1) % 2].begin() + nums[n - 1] + 1,
                             0LL) %
                      MOD);
    }

    // DP+前缀和+空间优化
    int countOfPairs(vector<int>& nums) {
        int ans = 0, n = nums.size(), m = nums.back();
        vector<int> f(m + 1); // 只用考虑j<=nums[i-1]
        fill(f.begin(), f.begin() + min(nums[0], m) + 1, 1);
        for (int i = 1; i < n; i++) {
            // 前缀和
            for (int j = 1; j <= m; j++) {
                f[j] = (f[j] + f[j - 1]) % MOD;
            }
            // max_k>=0 ==> j + min(nums[i-1]-nums[i],0) >= 0
            // j >= max(nums[i]-nums[i-1], 0)
            int j0 = max(nums[i]-nums[i-1], 0);
            for (int j = min(nums[i], m); j >= j0; j--) {
                f[j] = f[j - j0];
            }
            fill(f.begin(), f.begin() + min(j0, m + 1), 0); // 清空无效数据
        }
        return reduce(f.begin(), f.end(), 0LL) % MOD;
    }
};
// @lc code=end

