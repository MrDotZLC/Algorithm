/*
 * @lc app=leetcode id=996 lang=cpp
 *
 * [996] Number of Squareful Arrays
 *
 * https://leetcode.com/problems/number-of-squareful-arrays/description/
 *
 * algorithms
 * Hard (50.54%)
 * Likes:    1029
 * Dislikes: 47
 * Total Accepted:    47.6K
 * Total Submissions: 93.6K
 * Testcase Example:  '[1,17,8]'
 *
 * An array is squareful if the sum of every pair of adjacent elements is a
 * perfect square.
 * 
 * Given an integer array nums, return the number of permutations of nums that
 * are squareful.
 * 
 * Two permutations perm1 and perm2 are different if there is some index i such
 * that perm1[i] != perm2[i].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,17,8]
 * Output: 2
 * Explanation: [1,8,17] and [17,8,1] are the valid permutations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,2,2]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 12
 * 0 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;
// @lc code=start
/**
 * 状压DP
 * 全排列 - 重复组合
 * f(i,j)表示选中的下标集合为i且上一个选中的下标为j的全排列数量
 * f(i|1<<k,k)=sum(f(i,j)), k∈[0,n-1] && j必须已被选 && k还未被选 && 满足取模条件
 * 边界：f({i},i)=1，每个数下标i作为最后一个数已被选且上一个被选的就是i，则是一个有效方案
 * 入口：f(U,j)，U∈[0,n-1]
 * 
 * 重复组合可通过计算重复倍率来去除
 * 
 */
class Solution {
public:
    bool check(int i) {
        int x = sqrt(i);
        return x * x == i;
    }

    // 状压DP
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size(), m = (1 << n), max_cnt = 0;
        unordered_map<int, int> cnt;
        for (int x : nums) {
            if (++cnt[x] > max_cnt) {
                max_cnt = cnt[x];
            }
        }
        vector<vector<long long>> f(m, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            f[1 << i][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (f[i][j] == 0) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    if ((i >> k & 1) == 0 && check(nums[j] + nums[k])) {
                        f[i | 1 << k][k] += f[i][j];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += f[m - 1][i];
        }

        vector<int> repetition_rate(max_cnt + 1);
        repetition_rate[1] = 1;
        for (int i = 2; i <= max_cnt; i++) {
            repetition_rate[i] = i * repetition_rate[i - 1];
        }

        for (auto &[x, c] : cnt) {
            ans /= repetition_rate[c];
        }

        return ans;
    }
};
// @lc code=end

