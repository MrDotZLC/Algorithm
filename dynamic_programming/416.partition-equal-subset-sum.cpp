/*
 * @lc app=leetcode id=416 lang=cpp
 *
 * [416] Partition Equal Subset Sum
 *
 * https://leetcode.com/problems/partition-equal-subset-sum/description/
 *
 * algorithms
 * Medium (48.59%)
 * Likes:    13559
 * Dislikes: 292
 * Total Accepted:    1.4M
 * Total Submissions: 2.8M
 * Testcase Example:  '[1,5,11,5]'
 *
 * Given an integer array nums, return true if you can partition the array into
 * two subsets such that the sum of the elements in both subsets is equal or
 * false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,5,11,5]
 * Output: true
 * Explanation: The array can be partitioned as [1, 5, 5] and [11].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,5]
 * Output: false
 * Explanation: The array cannot be partitioned into equal sum subsets.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 200
 * 1 <= nums[i] <= 100
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    bool canPartition1(vector<int>& nums) {
        int sum = reduce(nums.begin(), nums.end());
        if (sum % 2) {
            return false;
        }
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(sum / 2 + 1, -1));
        auto dfs = [&](auto &dfs, int i, int t) -> bool {
            if (i < 0) {
                return t == 0;
            }
            int &ans = memo[i][t];
            if (ans != -1) {
                return ans;
            }
            if (t < nums[i]) {
                return ans = dfs(dfs, i - 1, t);
            }
            return ans = (dfs(dfs, i - 1, t) || dfs(dfs, i - 1, t - nums[i]));
        };
        return dfs(dfs, nums.size() - 1, sum / 2);
    }

    // DP递推
    bool canPartition2(vector<int>& nums) {
        int sum = reduce(nums.begin(), nums.end());
        if (sum % 2) {
            return false;
        }
        sum /= 2;
        int n = nums.size();
        vector<vector<int>> f(n + 1, vector<int>(sum + 1));
        f[0][0] = 1;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = 0; j <= sum; j++) {
                f[i + 1][j] = (j >= x && f[i][j - x]) || f[i][j];
            }
        }
        return f[n][sum];
    }

    // DP递推+空间优化
    bool canPartition3(vector<int>& nums) {
        int sum = reduce(nums.begin(), nums.end());
        if (sum % 2) {
            return false;
        }
        sum /= 2;
        int n = nums.size();
        vector<int> f(sum + 1);
        f[0] = 1;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = sum; j >= 0; j--) {
                f[j] |= (j >= x && f[j - x]);
            }
        }

        return f[sum];
    }

    // DP递推+空间优化_剪枝
    bool canPartition(vector<int>& nums) {
        int sum = reduce(nums.begin(), nums.end());
        if (sum % 2) {
            return false;
        }
        sum /= 2;
        int n = nums.size();
        vector<int> f(sum + 1);
        f[0] = 1;
        int s0 = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            s0 = min(s0 + x, sum);
            for (int j = s0; j >= x; j--) {
                f[j] |= f[j - x];
            }
            if (f[sum]) {
                return true;
            }
        }

        return false;
    }
};
// @lc code=end

