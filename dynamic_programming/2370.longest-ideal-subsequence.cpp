/*
 * @lc app=leetcode id=2370 lang=cpp
 *
 * [2370] Longest Ideal Subsequence
 *
 * https://leetcode.com/problems/longest-ideal-subsequence/description/
 *
 * algorithms
 * Medium (46.79%)
 * Likes:    1519
 * Dislikes: 82
 * Total Accepted:    122.5K
 * Total Submissions: 262.3K
 * Testcase Example:  '"acfgbd"\n2'
 *
 * You are given a string s consisting of lowercase letters and an integer k.
 * We call a string t ideal if the following conditions are satisfied:
 * 
 * 
 * t is a subsequence of the string s.
 * The absolute difference in the alphabet order of every two adjacent letters
 * in t is less than or equal to k.
 * 
 * 
 * Return the length of the longest ideal string.
 * 
 * A subsequence is a string that can be derived from another string by
 * deleting some or no characters without changing the order of the remaining
 * characters.
 * 
 * Note that the alphabet order is not cyclic. For example, the absolute
 * difference in the alphabet order of 'a' and 'z' is 25, not 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "acfgbd", k = 2
 * Output: 4
 * Explanation: The longest ideal string is "acbd". The length of this string
 * is 4, so 4 is returned.
 * Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3
 * in alphabet order.
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcd", k = 3
 * Output: 4
 * Explanation: The longest ideal string is "abcd". The length of this string
 * is 4, so 4 is returned.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * 0 <= k <= 25
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化递归
    int longestIdealString1(string s, int k) {
        int ans = 0, n = s.length();
        vector<vector<int>> memo(n, vector<int>(26, -1));
        auto dfs = [&](this auto &&dfs, int i, char c) -> int {
            if (i >= n) {
                return 0; 
            }
            int &res = memo[i][c - 'a'];
            if (res != -1) {
                return res;
            }
            if (abs(s[i] - c) <= k) {
                res = max(1 + dfs(i + 1, s[i]), dfs(i + 1, c));
            } else {
                res = dfs(i + 1, c);
            }
            return res;
        };
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(i, s[i]));
        }
        return ans;
    }

    // DP + 空间优化
    int longestIdealString(string s, int k) {
        vector<int> f(26);
        for (char c : s) {
            c -= 'a';
            f[c] = 1 + *max_element(f.begin() + max(c - k, 0),
                                    f.begin() + min(c + k + 1, 26));
        }
        return ranges::max(f);
    }
};
// @lc code=end

