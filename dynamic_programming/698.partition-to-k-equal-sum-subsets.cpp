/*
 * @lc app=leetcode id=698 lang=cpp
 *
 * [698] Partition to K Equal Sum Subsets
 *
 * https://leetcode.com/problems/partition-to-k-equal-sum-subsets/description/
 *
 * algorithms
 * Medium (38.15%)
 * Likes:    7459
 * Dislikes: 548
 * Total Accepted:    326.9K
 * Total Submissions: 853.6K
 * Testcase Example:  '[4,3,2,3,5,2,1]\n4'
 *
 * Given an integer array nums and an integer k, return true if it is possible
 * to divide this array into k non-empty subsets whose sums are all equal.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,3,2,3,5,2,1], k = 4
 * Output: true
 * Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3),
 * (2,3) with equal sums.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4], k = 3
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 16
 * 1 <= nums[i] <= 10^4
 * The frequency of each element is in the range [1, 4].
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 状压DP
 * 用一个整数的二进制位表示所有元素选或不选
 * 枚举所有选择方案
 * f(i)表示元素下标集合为i时是否能够划分
 * f(i)=f(i|1<<j), j∈[1,n]&&(i>>j)&1=0
 * 边界：i=(1<<n)-1, f=true
 * 入口：f(0)=0
 */
class Solution {
public:
    // 记忆化搜索
    bool canPartitionKSubsets1(vector<int>& nums, int k) {
        ranges::sort(nums);
        // 特殊判断
        int total = reduce(nums.begin(), nums.end(), 0);
        if (total % k) {
            return false;
        }
        int target = total / k;
        if (nums.back() > target) {
            return false;
        }

        int n = nums.size(), m = 1 << n;
        vector<int> memo(m, -1);
        auto dfs = [&](auto &dfs, int i, int sum) -> int {
            if (i == m - 1) {
                return true;
            }
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int j = 0; j < n; j++) {
                if (nums[j] + sum > target) {
                    break; // nums已升序，后面也会>target
                }
                if ((i & 1 << j) == 0) {
                    if (dfs(dfs, i | 1 << j, (nums[j] + sum) % target)) {
                        return res = 1;
                    }
                }
            }
            return res;
        };
        return dfs(dfs, 0, 0);
    }

    // 状压DP
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        ranges::sort(nums);
        // 特殊判断
        int total = reduce(nums.begin(), nums.end(), 0);
        if (total % k) {
            return false;
        }
        int target = total / k;
        if (nums.back() > target) {
            return false;
        }

        int n = nums.size(), m = 1 << n;
        vector<int> f(m, -1);
        f[0] = 0;
        for (int i = 0; i < m; i++) {
            if (f[i] == -1) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (nums[j] + f[i] % target > target) {
                    break;
                }
                if ((i & 1 << j) == 0 && f[i | 1 << j] == -1) {
                    f[i | 1 << j] = f[i] + nums[j];
                }
                if (f[m - 1] == total) {
                    return true;
                }
            }
        }
        return f[m - 1] == total;
    }
};
// @lc code=end

