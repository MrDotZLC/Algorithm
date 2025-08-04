/*
 * @lc app=leetcode id=844 lang=cpp
 *
 * [844] Backspace String Compare
 *
 * https://leetcode.com/problems/backspace-string-compare/description/
 *
 * algorithms
 * Easy (49.51%)
 * Likes:    7764
 * Dislikes: 373
 * Total Accepted:    961.1K
 * Total Submissions: 1.9M
 * Testcase Example:  '"ab#c"\n"ad#c"'
 *
 * Given two strings s and t, return true if they are equal when both are typed
 * into empty text editors. '#' means a backspace character.
 * 
 * Note that after backspacing an empty text, the text will continue empty.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ab#c", t = "ad#c"
 * Output: true
 * Explanation: Both s and t become "ac".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "ab##", t = "c#d#"
 * Output: true
 * Explanation: Both s and t become "".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "a#c", t = "b"
 * Output: false
 * Explanation: s becomes "c" while t becomes "b".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length, t.length <= 200
 * s and t only contain lowercase letters and '#' characters.
 * 
 * 
 * 
 * Follow up: Can you solve it in O(n) time and O(1) space?
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
    bool backspaceCompare(string s, string t) {
        int m = s.length(), n = t.length();
        int i = m - 1, j = n - 1;
        int skip_i = 0, skip_j = 0;
        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (s[i] == '#') {
                    i--;
                    skip_i++;
                } else if (skip_i > 0) {
                    i--;
                    skip_i--;
                } else {
                    break;
                }
            }
            while (j >= 0) {
                if (t[j] == '#') {
                    j--;
                    skip_j++;
                } else if (skip_j > 0) {
                    j--;
                    skip_j--;
                } else {
                    break;
                }
            }
            if (i >= 0 && j >= 0) {
                if (s[i] != t[j]) {
                    return false;
                }
            } else {
                if (i >= 0 || j >= 0) {
                    return false;
                }
            }
            i--;
            j--;
        }
        return true;
    }
};
// @lc code=end

