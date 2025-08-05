/*
 * @lc app=leetcode id=2486 lang=cpp
 *
 * [2486] Append Characters to String to Make Subsequence
 *
 * https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description/
 *
 * algorithms
 * Medium (72.96%)
 * Likes:    1153
 * Dislikes: 90
 * Total Accepted:    207.9K
 * Total Submissions: 284.8K
 * Testcase Example:  '"coaching"\n"coding"'
 *
 * You are given two strings s and t consisting of only lowercase English
 * letters.
 * 
 * Return the minimum number of characters that need to be appended to the end
 * of s so that t becomes a subsequence of s.
 * 
 * A subsequence is a string that can be derived from another string by
 * deleting some or no characters without changing the order of the remaining
 * characters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "coaching", t = "coding"
 * Output: 4
 * Explanation: Append the characters "ding" to the end of s so that s =
 * "coachingding".
 * Now, t is a subsequence of s ("coachingding").
 * It can be shown that appending any 3 characters to the end of s will never
 * make t a subsequence.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcde", t = "a"
 * Output: 0
 * Explanation: t is already a subsequence of s ("abcde").
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "z", t = "abcde"
 * Output: 5
 * Explanation: Append the characters "abcde" to the end of s so that s =
 * "zabcde".
 * Now, t is a subsequence of s ("zabcde").
 * It can be shown that appending any 4 characters to the end of s will never
 * make t a subsequence.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length, t.length <= 10^5
 * s and t consist only of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int appendCharacters(string s, string t) {
        int i=0,j=0,n=s.size(),m=t.size();
        while(i<n and j<m) {
            if(s[i]==t[j])j++;
            i++;
        }
        return m-j;
    }
};
// @lc code=end

