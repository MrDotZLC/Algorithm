/*
 * @lc app=leetcode id=856 lang=cpp
 *
 * [856] Score of Parentheses
 *
 * https://leetcode.com/problems/score-of-parentheses/description/
 *
 * algorithms
 * Medium (63.67%)
 * Likes:    5570
 * Dislikes: 232
 * Total Accepted:    212.3K
 * Total Submissions: 333.9K
 * Testcase Example:  '"()"'
 *
 * Given a balanced parentheses string s, return the score of the string.
 * 
 * The score of a balanced parentheses string is based on the following
 * rule:
 * 
 * 
 * "()" has score 1.
 * AB has score A + B, where A and B are balanced parentheses strings.
 * (A) has score 2 * A, where A is a balanced parentheses string.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "()"
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "(())"
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "()()"
 * Output: 2
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= s.length <= 50
 * s consists of only '(' and ')'.
 * s is a balanced parentheses string.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int scoreOfParentheses1(string s) {
        vector<int> cnt(s.length() + 2, 0);
        int level = 0;
        for (char c : s) {
            if (c == '(') {
                level++;
            } else if (c == ')') {
                level--;
                cnt[level] += (cnt[level + 1] ? 2 * cnt[level + 1] : 1);
                cnt[level + 1] = 0;
            }
        }
        return cnt[0];
    }

    int scoreOfParentheses(string s) {
        vector<int> st;
        st.push_back(0);
        for (char c : s) {
            if (c == '(') {
                st.push_back(0);
            } else {
                int v = st.back();
                st.pop_back();
                st.back() += max(2 * v, 1);
            }
        }
        return st.back();
    }
};
// @lc code=end

