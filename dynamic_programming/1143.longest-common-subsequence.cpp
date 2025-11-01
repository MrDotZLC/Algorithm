/*
 * @lc app=leetcode id=1143 lang=cpp
 *
 * [1143] Longest Common Subsequence
 *
 * https://leetcode.com/problems/longest-common-subsequence/description/
 *
 * algorithms
 * Medium (58.35%)
 * Likes:    14727
 * Dislikes: 238
 * Total Accepted:    1.7M
 * Total Submissions: 2.8M
 * Testcase Example:  '"abcde"\n"ace"'
 *
 * Given two strings text1 and text2, return the length of their longest common
 * subsequence. If there is no common subsequence, return 0.
 * 
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 * 
 * 
 * For example, "ace" is a subsequence of "abcde".
 * 
 * 
 * A common subsequence of two strings is a subsequence that is common to both
 * strings.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: text1 = "abcde", text2 = "ace" 
 * Output: 3  
 * Explanation: The longest common subsequence is "ace" and its length is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: text1 = "abc", text2 = "abc"
 * Output: 3
 * Explanation: The longest common subsequence is "abc" and its length is 3.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: text1 = "abc", text2 = "def"
 * Output: 0
 * Explanation: There is no such common subsequence, so the result is 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= text1.length, text2.length <= 1000
 * text1 and text2 consist of only lowercase English characters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // f(i, j) = f(i-1, j-1) - 1;               (s[i] == t[j])
    //           max(f(i, j-1), f(i-1, j));     (s[i] != t[j])

    // DP递归
    int longestCommonSubsequence1(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            if (text1[i] == text2[j]) {
                return ans = dfs(dfs, i - 1, j - 1) + 1;
            }
            return ans = max(dfs(dfs, i - 1, j), dfs(dfs, i, j - 1));
        };
        return dfs(dfs, n - 1, m - 1);        
    }

    // DP递推
    int longestCommonSubsequence2(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (text1[i] == text2[j]) {
                    f[i + 1][j + 1] = f[i][j] + 1;
                } else {
                    f[i + 1][j + 1] = max(f[i][j + 1], f[i + 1][j]);
                }
            }
        }
        return f[n][m];
    }

    // DP递推+空间优化
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<int> f(m + 1);
        for (char x : text1) {
            for (int j = 0, pre = 0; j < m; j++) {
                int tmp = f[j + 1];
                f[j + 1] = x == text2[j] ? pre + 1 : max(f[j + 1], f[j]);
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

