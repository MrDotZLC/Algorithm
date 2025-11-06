/*
 * @lc app=leetcode id=1278 lang=cpp
 *
 * [1278] Palindrome Partitioning III
 *
 * https://leetcode.com/problems/palindrome-partitioning-iii/description/
 *
 * algorithms
 * Hard (61.70%)
 * Likes:    1198
 * Dislikes: 19
 * Total Accepted:    35.6K
 * Total Submissions: 57.5K
 * Testcase Example:  '"abc"\n2'
 *
 * You are given a string s containing lowercase letters and an integer k. You
 * need to :
 * 
 * 
 * First, change some characters of s to other lowercase English letters.
 * Then divide s into k non-empty disjoint substrings such that each substring
 * is a palindrome.
 * 
 * 
 * Return the minimal number of characters that you need to change to divide
 * the string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abc", k = 2
 * Output: 1
 * Explanation: You can split the string into "ab" and "c", and change 1
 * character in "ab" to make it palindrome.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aabbc", k = 3
 * Output: 0
 * Explanation: You can split the string into "aa", "bb" and "c", all of them
 * are palindrome.
 * 
 * Example 3:
 * 
 * 
 * Input: s = "leetcode", k = 8
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= s.length <= 100.
 * s only contains lowercase English letters.
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
    // DP
    int palindromePartition1(string s, int k) {
        int n = s.length();
        vector f(k + 1, vector<int>(n + 1, INT_MAX / 2));
        f[0][0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = i; j <= n - (k - i); j++) {
                for (int l = j - 1; l >= i - 1; l--) {
                    f[i][j] = min({f[i][j], f[i - 1][l] + 
                                   palindrome_edit(s, l, j)});
                }
            }
        }
        return f[k][n];
    }

    // DP+空间优化
    int palindromePartition2(string s, int k) {
        int n = s.length();
        vector<int> f(n + 1, INT_MAX / 2);
        f[0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = n - (k - i); j >= i; j--) { // 开区间，不包含r
                f[j] = INT_MAX / 2;
                for (int l = j - 1; l >= i - 1; l--) { // 闭区间，包含l
                    f[j] = min({f[j], f[l] + 
                                   palindrome_edit(s, l, j)});
                }
            }
        }
        return f[n];
    }

    // 使子串回文的操作数
    int palindrome_edit(const string &s, int l, int r) {
        int ans = 0;
        while (l < r - 1) {
            ans += (s[l++] != s[r-- - 1]);
        }
        return ans;
    }

    // DP+空间优化+双重记忆化
    int palindromePartition(string s, int k) {
        int n = s.length();
        vector min_change(n, vector<int>(n));
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                min_change[i][j] = min_change[i + 1][j - 1] + (s[i] != s[j]);
            }
        }

        // 此处k的含义与其他解法不同：
        // f[i][j]为前j个数还能切i刀，i==0表示[0:j]不拆分成子数组
        vector<int> f = move(min_change[0]);
        for (int i = 1; i < k; i++) {
            // 左端至少有i-1个数、右端至少有n-(k-i)-1个数
            // 不属于以j为右端点的子数组
            for (int j = n - (k - i); j >= i; j--) { 
                f[j] = INT_MAX / 2;
                for (int l = i; l <= j; l++) {
                    f[j] = min({f[j], f[l - 1] + 
                                   min_change[l][j]});
                }
            }
        }
        return f[n - 1];
    }
};
// @lc code=end

