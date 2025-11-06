/*
 * @lc app=leetcode id=813 lang=cpp
 *
 * [813] Largest Sum of Averages
 *
 * https://leetcode.com/problems/largest-sum-of-averages/description/
 *
 * algorithms
 * Medium (54.17%)
 * Likes:    2182
 * Dislikes: 104
 * Total Accepted:    63.8K
 * Total Submissions: 116.9K
 * Testcase Example:  '[9,1,2,3,9]\n3'
 *
 * You are given an integer array nums and an integer k. You can partition the
 * array into at most k non-empty adjacent subarrays. The score of a partition
 * is the sum of the averages of each subarray.
 * 
 * Note that the partition must use every integer in nums, and that the score
 * is not necessarily an integer.
 * 
 * Return the maximum score you can achieve of all the possible partitions.
 * Answers within 10^-6 of the actual answer will be accepted.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [9,1,2,3,9], k = 3
 * Output: 20.00000
 * Explanation: 
 * The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is
 * 9 + (1 + 2 + 3) / 3 + 9 = 20.
 * We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
 * That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4,5,6,7], k = 4
 * Output: 20.50000
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 递归+前缀和
    double largestSumOfAverages1(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre_sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pre_sum[i + 1] = pre_sum[i] + nums[i];
        }
        // 递归右端点r和划分子数组的次数i
        vector<vector<double>> memo(n, vector<double>(k, -1));
        auto dfs = [&](this auto &&dfs, int r, int i) -> int {
            if (r == 0) {
                return nums[0];
            }
            if (i == 0) {
                return 1.0 * pre_sum[r + 1] / (r + 1);
            }
            double &res = memo[r][i];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int l = r; l > 0; l--) {
                double score = 1.0 * (pre_sum[r + 1] - pre_sum[l]) / (r - l + 1);
                res = max(res, dfs(r - 1, i - 1) + score);
            }
            return res;
        };
        return dfs(n - 1, k - 1);
    }

    // DP+前缀和
    double largestSumOfAverages2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre_sum(n + 1, 0);
        vector<vector<double>> f(n, vector<double>(k, 0));
        f[0][0] = nums[0];
        for (int r = 0; r < n; r++) {
            pre_sum[r + 1] = pre_sum[r] + nums[r];
            f[r][0] = 1.0 * pre_sum[r + 1] / (r + 1);
            for (int i = 1; i < k; i++) {
                for (int l = r; l >= 1; l--) {
                    double score = 1.0 * (pre_sum[r + 1] - pre_sum[l]) / (r - l + 1);
                    f[r][i] = max(f[r][i], f[l - 1][i - 1] + score);
                }
            }
        }
        return f[n - 1][k - 1];
    }

    // DP+前缀和+空间优化
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> pre_sum(n + 1, 0), f(n + 1, 0.0);
        for (int r = 0; r < n; r++) {
            pre_sum[r + 1] = pre_sum[r] + nums[r];
            f[r + 1] = 1.0 * pre_sum[r + 1] / (r + 1);
        }
        for (int j = 2; j <= k; j++) {
            for (int r = n; r >= j; r--) {
                for (int l = j - 1; l < r; l++) {
                    double score = 1.0 * (pre_sum[r] - pre_sum[l]) / (r - l);
                    f[r] = max(f[r], f[l] + score);
                }
            }
        }
        return f[n];
    }
    
};
// @lc code=end

