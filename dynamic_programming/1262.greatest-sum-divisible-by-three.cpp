/*
 * @lc app=leetcode id=1262 lang=cpp
 *
 * [1262] Greatest Sum Divisible by Three
 *
 * https://leetcode.com/problems/greatest-sum-divisible-by-three/description/
 *
 * algorithms
 * Medium (51.02%)
 * Likes:    1897
 * Dislikes: 46
 * Total Accepted:    69K
 * Total Submissions: 135K
 * Testcase Example:  '[3,6,5,1,8]'
 *
 * Given an integer array nums, return the maximum possible sum of elements of
 * the array such that it is divisible by three.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,6,5,1,8]
 * Output: 18
 * Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum
 * divisible by 3).
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4]
 * Output: 0
 * Explanation: Since 4 is not divisible by 3, do not pick any number.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3,4,4]
 * Output: 12
 * Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum
 * divisible by 3).
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 4 * 10^4
 * 1 <= nums[i] <= 10^4
 * 
 * 
 */
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    int maxSumDivThree1(vector<int>& nums) {
        int n = nums.size();
        vector<array<int, 3>> memo(n, {-1, -1, -1});
        // 前i个元素中，已选元素和mod3为j的情况
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0) {
                return j ? INT_MIN : 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            int new_j = (j + nums[i]) % 3;
            return res = max(dfs(dfs, i - 1, j), dfs(dfs, i - 1, new_j) + nums[i]);
        };
        return dfs(dfs, n - 1, 0);
    }

    // DP+空间优化
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<array<int, 3>> f(2, {0, 0, 0});
        f[0][1] = INT_MIN, f[0][2] = INT_MIN;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = 0; j < 3; j++) {
                f[(i + 1) % 2][j] = max(f[i % 2][j], f[i % 2][(j + x) % 3] + x); 
            }
        }
        return f[n % 2][0];
    }
};
// @lc code=end

