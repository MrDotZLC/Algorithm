/*
 * @lc app=leetcode id=2414 lang=cpp
 *
 * [2414] Length of the Longest Alphabetical Continuous Substring
 *
 * https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/description/
 *
 * algorithms
 * Medium (59.43%)
 * Likes:    534
 * Dislikes: 35
 * Total Accepted:    56.6K
 * Total Submissions: 95.2K
 * Testcase Example:  '"abacaba"'
 *
 * An alphabetical continuous string is a string consisting of consecutive
 * letters in the alphabet. In other words, it is any substring of the string
 * "abcdefghijklmnopqrstuvwxyz".
 * 
 * 
 * For example, "abc" is an alphabetical continuous string, while "acb" and
 * "za" are not.
 * 
 * 
 * Given a string s consisting of lowercase letters only, return the length of
 * the longest alphabetical continuous substring.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abacaba"
 * Output: 2
 * Explanation: There are 4 distinct continuous substrings: "a", "b", "c" and
 * "ab".
 * "ab" is the longest continuous substring.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcde"
 * Output: 5
 * Explanation: "abcde" is the longest continuous substring.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of only English lowercase letters.
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
    int longestContinuousSubstring(string s) {
        int ans = 1, cnt = 1;
        for (int i = 1; i < s.length(); i++) {
            if (s[i - 1] + 1 == s[i]) {
                ans = max(ans, ++cnt);
            } else {
                cnt = 1;
            }
        }
        return ans;
    }
};
// @lc code=end

