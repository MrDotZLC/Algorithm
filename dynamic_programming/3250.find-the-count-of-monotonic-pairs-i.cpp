/*
 * @lc app=leetcode id=3250 lang=cpp
 *
 * [3250] Find the Count of Monotonic Pairs I
 *
 * https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/description/
 *
 * algorithms
 * Hard (46.67%)
 * Likes:    150
 * Dislikes: 12
 * Total Accepted:    19.9K
 * Total Submissions: 42.3K
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
 * 1 <= nums[i] <= 50
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
    // 记忆化递归
    int countOfPairs1(vector<int>& nums) {
        int n = nums.size(), mx = ranges::max(nums);
        vector<vector<long long>> memo(n + 1, vector<long long>(mx + 1));
        auto dfs = [&](auto &dfs, int i, int j) -> long long {
            if (i == 0) {
                return 1;
            }
            long long &res = memo[i][j];
            if (res) {
                return res;
            }
            // 0 <= k <= nums[i-1]
            // k <= j
            // nums[i-1]-k >= nums[i]-j
            // max_k=min{nums[i-1], j, nums[i-1]-nums[i]+j};
            int max_k = min({nums[i - 1], j, nums[i - 1] - nums[i] + j});
            for (int k = 0; k <= max_k; k++) {
                res += dfs(dfs, i - 1, k);
            }
            return res %= MOD;
        };
        long long ans = 0;
        for (int i = nums[n - 1]; i >= 0; i--) {
            ans += dfs(dfs, n - 1, i);
        }
        return (int) ans % MOD;
    }

    // DP+空间优化
    int countOfPairs(vector<int>& nums) {
        int ans = 0, n = nums.size(), mx = ranges::max(nums);
        vector<vector<long long>> f(2, vector<long long>(mx + 1));
        fill(f[0].begin(), f[0].begin() + nums[0] + 1, 1);
        for (int i = 1; i < n; i++) {
            // 清零当前行，防止残留旧值
            fill(f[i % 2].begin(), f[i % 2].end(), 0);
            for (int j = 0; j <= nums[i]; j++) {
                long long res = 0;
                int max_k = min({nums[i - 1], j, nums[i - 1] - nums[i] + j});
                for (int k = 0; k <= max_k; k++) {
                    res += f[(i - 1) % 2][k];
                }
                f[i % 2][j] = res % MOD;
            }
        }
        return (int) (reduce(f[(n - 1) % 2].begin(), f[(n - 1) % 2].end(), 0LL) % MOD);
    }
};
// @lc code=end

