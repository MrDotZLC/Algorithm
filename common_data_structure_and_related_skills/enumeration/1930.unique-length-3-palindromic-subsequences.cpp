/*
 * @lc app=leetcode id=1930 lang=cpp
 *
 * [1930] Unique Length-3 Palindromic Subsequences
 *
 * https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
 *
 * algorithms
 * Medium (70.94%)
 * Likes:    2555
 * Dislikes: 102
 * Total Accepted:    260.4K
 * Total Submissions: 366.9K
 * Testcase Example:  '"aabca"'
 *
 * Given a string s, return the number of unique palindromes of length three
 * that are a subsequence of s.
 * 
 * Note that even if there are multiple ways to obtain the same subsequence, it
 * is still only counted once.
 * 
 * A palindrome is a string that reads the same forwards and backwards.
 * 
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 * 
 * 
 * For example, "ace" is a subsequence of "abcde".
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aabca"
 * Output: 3
 * Explanation: The 3 palindromic subsequences of length 3 are:
 * - "aba" (subsequence of "aabca")
 * - "aaa" (subsequence of "aabca")
 * - "aca" (subsequence of "aabca")
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "adc"
 * Output: 0
 * Explanation: There are no palindromic subsequences of length 3 in "adc".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "bbcbaba"
 * Output: 4
 * Explanation: The 4 palindromic subsequences of length 3 are:
 * - "bbb" (subsequence of "bbcbaba")
 * - "bcb" (subsequence of "bbcbaba")
 * - "bab" (subsequence of "bbcbaba")
 * - "aba" (subsequence of "bbcbaba")
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int ans = 0,  n = s.length();
        int cnt_i[26], cnt_k[26];
        bool cnt_ans[26][26];
        cnt_i[s[0] - 'a']++;
        for (int k = 2; k < n; k++) {
            cnt_k[s[k] - 'a']++;
        }

        for (int j = 1; j < n - 1; j++) {
            int x = s[j] - 'a';
            for (int i = 0; i < 26; i++) {
                if (cnt_i[i] && cnt_k[i] && !cnt_ans[x][i]) {
                    ans++;
                    cnt_ans[x][i] = true;
                }
            }
            cnt_i[x]++;
            cnt_k[s[j + 1] - 'a']--;
        }
        return ans;
    }
};
// @lc code=end

