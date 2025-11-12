/*
 * @lc app=leetcode id=2222 lang=cpp
 *
 * [2222] Number of Ways to Select Buildings
 *
 * https://leetcode.com/problems/number-of-ways-to-select-buildings/description/
 *
 * algorithms
 * Medium (50.53%)
 * Likes:    1048
 * Dislikes: 54
 * Total Accepted:    50.2K
 * Total Submissions: 99.3K
 * Testcase Example:  '"001101"'
 *
 * You are given a 0-indexed binary string s which represents the types of
 * buildings along a street where:
 * 
 * 
 * s[i] = '0' denotes that the i^th building is an office and
 * s[i] = '1' denotes that the i^th building is a restaurant.
 * 
 * 
 * As a city official, you would like to select 3 buildings for random
 * inspection. However, to ensure variety, no two consecutive buildings out of
 * the selected buildings can be of the same type.
 * 
 * 
 * For example, given s = "001101", we cannot select the 1^st, 3^rd, and 5^th
 * buildings as that would form "011" which is not allowed due to having two
 * consecutive buildings of the same type.
 * 
 * 
 * Return the number of valid ways to select 3 buildings.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "001101"
 * Output: 6
 * Explanation: 
 * The following sets of indices selected are valid:
 * - [0,2,4] from "001101" forms "010"
 * - [0,3,4] from "001101" forms "010"
 * - [1,2,4] from "001101" forms "010"
 * - [1,3,4] from "001101" forms "010"
 * - [2,4,5] from "001101" forms "101"
 * - [3,4,5] from "001101" forms "101"
 * No other selection is valid. Thus, there are 6 total ways.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "11100"
 * Output: 0
 * Explanation: It can be shown that there are no valid selections.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 10^5
 * s[i] is either '0' or '1'.
 * 
 * 
 */
#include <vector>
#include <array>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    long long numberOfWays1(string s) {
        int n = s.length();
        vector memo(3, vector<array<long long, 2>>(n, {-1, -1}));
        auto dfs = [&](this auto &&dfs, int i, int j, int k) -> long long {
            if (i < 0) {
                return 1;
            }
            if (j < 0) {
                return 0;
            }
            long long &res = memo[i][j][k];
            if (res != -1) {
                return res;
            }
            res = dfs(i, j - 1, k);
            if (k == s[j] - '0') {
                res += dfs(i - 1, j - 1, !k);
            }
            return res;
        };
        return dfs(2, n - 1, 0) + dfs(2, n - 1, 1);
    }

    // DP+空间优化
    long long numberOfWays2(string s) {
        int n = s.length();
        vector<array<long long, 2>> f(4);
        fill(f[0].begin(), f[0].end(), 1);
        for (char c : s) {
            for (int i = 1; i <= 3; i++) {
                if (c == '0') {
                    f[i][0] += f[i - 1][1];
                } else {
                    f[i][1] += f[i - 1][0];
                }
            }
        }
        return f[3][0] + f[3][1];
    }

    // 枚举
    long long numberOfWays(string s) {
        int n = s.length();
        long long ans = 0, c0 = 0, s0 = ranges::count(s, '0');
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                int c1 = i - c0;
                ans += c1 * (n - s0 - c1);
                c0++;
            } else {
                ans += c0 * (s0 - c0);
            }
        }
        return ans;
    }
};
// @lc code=end
