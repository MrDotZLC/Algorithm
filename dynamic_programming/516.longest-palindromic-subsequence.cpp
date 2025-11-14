/*
 * @lc app=leetcode id=516 lang=cpp
 *
 * [516] Longest Palindromic Subsequence
 *
 * https://leetcode.com/problems/longest-palindromic-subsequence/description/
 *
 * algorithms
 * Medium (64.33%)
 * Likes:    10210
 * Dislikes: 340
 * Total Accepted:    699.6K
 * Total Submissions: 1.1M
 * Testcase Example:  '"bbbab"'
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * 
 * A subsequence is a sequence that can be derived from another sequence by
 * deleting some or no elements without changing the order of the remaining
 * elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "bbbab"
 * Output: 4
 * Explanation: One possible longest palindromic subsequence is "bbbb".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "cbbd"
 * Output: 2
 * Explanation: One possible longest palindromic subsequence is "bb".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s consists only of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
/**
 * f(i,j)，表示下标[i, j]范围内最长会问子序列的长度 
 * f(i,j)=f(i+1,j-1)+2，              当f[i]==f[j]
 *        max(f(i,j-1), f(i+1,j))，   当f[i]！=f[j]
 * 边界：f(i,j)=1，当i==j
 *       f(i,j)=0，当i>j
 */
class Solution {
public:
    // 记忆化递归
    int longestPalindromeSubseq1(string s) {
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i > j) {
                return 0;
            }
            if (i == j) {
                return 1;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            if (s[i] == s[j]) {
                res = dfs(i + 1, j - 1) + 2;
            } else {
                res = max(dfs(i, j - 1), dfs(i + 1, j));
            }
            return res;
        };
        return dfs(0, n - 1);
    }

    // DP
    int longestPalindromeSubseq2(string s) {
        int n = s.length();
        vector<vector<int>> f(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) { // f[i]从f[i+1]来，所以倒着枚举
            f[i][i] = 1;
            for (int j = i + 1; j < n; j++) { // f[i][j]从f[i][j-1]来，所以正着枚举
                if (s[i] == s[j]) {
                    f[i][j] = f[i + 1][j - 1] + 2;
                } else {
                    f[i][j] = max(f[i][j - 1], f[i + 1][j]);
                }
            }
        }
        return f[0][n - 1];
    }

    // DP+空间优化
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--) { // f[i]从f[i+1]来，所以倒着枚举
            f[i] = 1;
            int pre = 0; // 存放f[i+1][j-1]，初始值为f[i+1][i]
            for (int j = i + 1; j < n; j++) { // f[i][j]从f[i][j-1]来，所以正着枚举
                int tmp = f[j];
                if (s[i] == s[j]) {
                    f[j] = pre + 2;
                } else {
                    f[j] = max(f[j - 1], f[j]);
                }
                pre = tmp;
            }
        }
        return f[n - 1];
    }
};
// @lc code=end

