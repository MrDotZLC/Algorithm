/*
 * @lc app=leetcode id=1190 lang=cpp
 *
 * [1190] Reverse Substrings Between Each Pair of Parentheses
 *
 * https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/
 *
 * algorithms
 * Medium (71.75%)
 * Likes:    2919
 * Dislikes: 127
 * Total Accepted:    237.6K
 * Total Submissions: 330.7K
 * Testcase Example:  '"(abcd)"'
 *
 * You are given a string s that consists of lower case English letters and
 * brackets.
 * 
 * Reverse the strings in each pair of matching parentheses, starting from the
 * innermost one.
 * 
 * Your result should not contain any brackets.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "(abcd)"
 * Output: "dcba"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "(u(love)i)"
 * Output: "iloveu"
 * Explanation: The substring "love" is reversed first, then the whole string
 * is reversed.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "(ed(et(oc))el)"
 * Output: "leetcode"
 * Explanation: First, we reverse the substring "oc", then "etco", and finally,
 * the whole string.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2000
 * s only contains lower case English characters and parentheses.
 * It is guaranteed that all parentheses are balanced.
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
    string reverseParentheses1(string s) {
        vector<string> st;
        string str;
        for (char &c : s) {
            if (c == '(') {
                st.push_back(str);
                str = "";
            } else if (c == ')') {
                ranges::reverse(str);
                str = st.back() + str;
                st.pop_back();
            } else {
                str += c;
            }
        }
        return str;
    }

    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> st;
        vector<int> pair(n);
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '(') {
                st.push_back(i);
            } else if (c == ')') {
                int j = st.back();
                st.pop_back();
                pair[i] = j;
                pair[j] = i;
            }
        }

        string ans;
        int idx = 0, step = 1;
        while (idx < n) {
            if (s[idx] == '(' || s[idx] == ')') {
                idx = pair[idx];
                step = -step;
            } else {
                ans += s[idx];
            }
            idx += step;
        }
        return ans;
    }
};
// @lc code=end

