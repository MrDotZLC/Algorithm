/*
 * @lc app=leetcode id=1771 lang=cpp
 *
 * [1771] Maximize Palindrome Length From Subsequences
 *
 * https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/description/
 *
 * algorithms
 * Hard (37.35%)
 * Likes:    564
 * Dislikes: 17
 * Total Accepted:    13.8K
 * Total Submissions: 36.6K
 * Testcase Example:  '"cacb"\n"cbba"'
 *
 * You are given two strings, word1 and word2. You want to construct a string
 * in the following manner:
 * 
 * 
 * Choose some non-empty subsequence subsequence1 from word1.
 * Choose some non-empty subsequence subsequence2 from word2.
 * Concatenate the subsequences: subsequence1 + subsequence2, to make the
 * string.
 * 
 * 
 * Return the length of the longest palindrome that can be constructed in the
 * described manner. If no palindromes can be constructed, return 0.
 * 
 * A subsequence of a string s is a string that can be made by deleting some
 * (possibly none) characters from s without changing the order of the
 * remaining characters.
 * 
 * A palindrome is a string that reads the same forward as well as backward.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: word1 = "cacb", word2 = "cbba"
 * Output: 5
 * Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba",
 * which is a palindrome.
 * 
 * Example 2:
 * 
 * 
 * Input: word1 = "ab", word2 = "ab"
 * Output: 3
 * Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which
 * is a palindrome.
 * 
 * Example 3:
 * 
 * 
 * Input: word1 = "aa", word2 = "bb"
 * Output: 0
 * Explanation: You cannot construct a palindrome from the described method, so
 * return 0.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= word1.length, word2.length <= 1000
 * word1 and word2 consist of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
/**
 * 将word1和word2拼接，就变成了需要特判子序列是否来自同一字符串的最长回文序列长度
 * s[i]==s[j]且i<len1 && j>= len1时，更新答案。
 * 回文最外侧的一对字符一定是相等的，此时更新的就是最大长度，无需在不相等时更新答案。
 */
class Solution {
public:
    int longestPalindrome(string word1, string word2) {
        string s = word1 + word2;
        int ans = 0, n1 = word1.length(), n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--) { // f[i]从f[i+1]来，所以倒着枚举
            f[i] = 1;
            int pre = 0; // 存放f[i+1][j-1]，初始值为f[i+1][i]
            for (int j = i + 1; j < n; j++) { // f[i][j]从f[i][j-1]来，所以正着枚举
                int tmp = f[j];
                if (s[i] == s[j]) {
                    f[j] = pre + 2;
                    if (i < n1 && j >= n1) {
                        ans = max(ans, f[j]);
                    }
                } else {
                    f[j] = max(f[j - 1], f[j]);
                }
                pre = tmp;
            }
        }
        return ans;
    }
};
// @lc code=end

