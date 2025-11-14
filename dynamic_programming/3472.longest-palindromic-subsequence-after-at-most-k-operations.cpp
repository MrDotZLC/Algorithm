/*
 * @lc app=leetcode id=3472 lang=cpp
 *
 * [3472] Longest Palindromic Subsequence After at Most K Operations
 *
 * https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/description/
 *
 * algorithms
 * Medium (36.57%)
 * Likes:    114
 * Dislikes: 17
 * Total Accepted:    14.6K
 * Total Submissions: 39.5K
 * Testcase Example:  '"abced"\n2'
 *
 * You are given a string s and an integer k.
 * 
 * In one operation, you can replace the character at any position with the
 * next or previous letter in the alphabet (wrapping around so that 'a' is
 * after 'z'). For example, replacing 'a' with the next letter results in 'b',
 * and replacing 'a' with the previous letter results in 'z'. Similarly,
 * replacing 'z' with the next letter results in 'a', and replacing 'z' with
 * the previous letter results in 'y'.
 * 
 * Return the length of the longest palindromic subsequence of s that can be
 * obtained after performing at most k operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abced", k = 2
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * Replace s[1] with the next letter, and s becomes "acced".
 * Replace s[4] with the previous letter, and s becomes "accec".
 * 
 * 
 * The subsequence "ccc" forms a palindrome of length 3, which is the
 * maximum.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaazzz", k = 4
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * 
 * Replace s[0] with the previous letter, and s becomes "zaazzz".
 * Replace s[4] with the next letter, and s becomes "zaazaz".
 * Replace s[3] with the next letter, and s becomes "zaaaaz".
 * 
 * 
 * The entire string forms a palindrome of length 6.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 200
 * 1 <= k <= 200
 * s consists of only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * f(i,j,k)，表示下标[i, j]范围内k次操作后最长回文子序列的长度 
 * f(i,j,k)=f(i+1,j-1,k)+2，                                      当f[i]==f[j]
 *        max(f(i,j-1,k+1), f(i+1,j,k+1))，                       当f[i]！=f[j]且|s[i]-s[j]| > k
 *        max(f(i,j-1,k+1), f(i+1,j,k+1), f(i+1,j-1,op+d)+2)，    当f[i]！=f[j]且|s[i]-s[j]| <= k
 * 边界：
 *      f(i,j,k)=0，当i>j或k==K
 *      f(i,j,k)=1，当i==j
 */
class Solution {
public:
    // 记忆化递归
    int longestPalindromicSubsequence1(string s, int k) {
        int n = s.length();
        vector memo(n, vector(n, vector<int>(k + 1, -1)));
        auto dfs = [&](this auto &&dfs, int i, int j, int op) -> int {
            if (i > j || op > k) {
                return 0;
            }
            if (i == j) {
                return 1;
            }
            int &res = memo[i][j][op];
            if (res != -1) {
                return res;
            }
            if (s[i] == s[j]) {
                res = dfs(i + 1, j - 1, op) + 2;
            } else {
                res = max(dfs(i, j - 1, op), dfs(i + 1, j, op));
                int d = min((s[i] - s[j] + 26) % 26,
                            (s[j] - s[i] + 26) % 26);
                if (op + d <= k) {
                    res = max(res, dfs(i + 1, j - 1, op + d) + 2);
                }
            }
            return res;
        };
        return dfs(0, n - 1, 0);
    }

    // DP+空间优化
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.length();
        vector f(n, vector<int>(k + 1));
        
        for (int i = n - 1; i >= 0; i--) {
            vector g = f;
            fill(f[i].begin(), f[i].end(), 1); // 不初始化的话，j要从i开始枚举，并且做特判
            for (int j = i + 1; j < n; j++) {
                for (int op = k; op >= 0; op--) {
                    if (s[i] == s[j]) {
                        f[j][op] = g[j - 1][op] + 2;
                    } else {
                        f[j][op] = max(f[j - 1][op], g[j][op]);
                        int d = min((s[i] - s[j] + 26) % 26,
                                    (s[j] - s[i] + 26) % 26);
                        if (op + d <= k) {
                            f[j][op] =
                                max(f[j][op], g[j - 1][op + d] + 2);
                        }
                    }
                }
            }
        }
        return f[n - 1][0];
    }
};
// @lc code=end

