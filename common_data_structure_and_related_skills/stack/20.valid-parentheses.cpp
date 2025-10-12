/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (42.50%)
 * Likes:    26740
 * Dislikes: 1946
 * Total Accepted:    6.7M
 * Total Submissions: 15.5M
 * Testcase Example:  '"()"'
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 * 
 * An input string is valid if:
 * 
 * 
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "()"
 * 
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "()[]{}"
 * 
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "(]"
 * 
 * Output: false
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: s = "([])"
 * 
 * Output: true
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: s = "([)]"
 * 
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^4
 * s consists of parentheses only '()[]{}'.
 * 
 * 
 */
#include <stack>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
    unordered_map<char, char> mp = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
public:
    bool isValid(string s) {
        if (s.length() % 2) { // s 长度必须是偶数
            return false;
        }
        stack<char> st;
        for (char c : s) {
            if (mp.contains(c)) { // c 是左括号
                st.push(mp[c]); // 入栈对应的右括号
            } else { // c 是右括号
                if (st.empty() || st.top() != c) {
                    return false; // 没有左括号，或者左括号类型不对
                }
                st.pop(); // 出栈
            }
        }
        return st.empty(); // 所有左括号必须匹配完毕
    }
};
// @lc code=end

