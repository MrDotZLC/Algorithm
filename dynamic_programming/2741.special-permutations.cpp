/*
 * @lc app=leetcode id=2741 lang=cpp
 *
 * [2741] Special Permutations
 *
 * https://leetcode.com/problems/special-permutations/description/
 *
 * algorithms
 * Medium (28.68%)
 * Likes:    587
 * Dislikes: 66
 * Total Accepted:    17.1K
 * Total Submissions: 58.8K
 * Testcase Example:  '[2,3,6]'
 *
 * You are given a 0-indexed integer array nums containing n distinct positive
 * integers. A permutation of nums is called special if:
 * 
 * 
 * For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1]
 * % nums[i] == 0.
 * 
 * 
 * Return the total number of special permutations. As the answer could be
 * large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,6]
 * Output: 2
 * Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,4,3]
 * Output: 2
 * Explanation: [3,1,4] and [4,1,3] are the two special permutations of
 * nums.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 14
 * 1 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 状压DP
 * f(i,j)表示未选中的下标集合为i且上一个选中的下标为j的全排列数量
 * f(i)=sum(f(i^1<<k)), k∈[0,n-1] && k未被选中 && 满足取模条件
 * 边界：f(∅,j)=0
 * 入口：f(U\{i},j)，U∈[0,n-1]
 */
class Solution {
public:
    const int MOD = 1e9+7;
    // 记忆化搜索
    int specialPerm1(vector<int>& nums) {
        int n = nums.size(), m = (1 << n) - 1;
        vector<vector<long long>> memo(m, vector<long long>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> long long {
            if (i == 0) {
                return 1;
            }
            long long &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int k = 0; k < n; k++) {
                if (i >> k & 1 && (nums[j] % nums[k] == 0 ||
                                   nums[k] % nums[j] == 0)) {
                    res += dfs(i ^ 1 << k, k) % MOD;
                }
            }
            return res;
        };
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dfs(m ^ 1 << i, i)) % MOD;
        }
        return ans;
    }

    // 状压DP
    int specialPerm(vector<int>& nums) {
        int n = nums.size(), m = (1 << n) - 1;
        vector<vector<long long>> f(m, vector<long long>(n));
        fill(f[0].begin(), f[0].end(), 1);
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    if ((i >> k & 1) && (nums[j] % nums[k] == 0 ||
                                   nums[k] % nums[j] == 0)) {
                        f[i][j] += f[i ^ 1 << k][k];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + f[m ^ 1 << i][i]) % MOD;
        }
        return ans;
    }
};
// @lc code=end

