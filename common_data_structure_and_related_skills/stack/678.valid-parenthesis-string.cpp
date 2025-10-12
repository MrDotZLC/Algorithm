/*
 * @lc app=leetcode id=678 lang=cpp
 *
 * [678] Valid Parenthesis String
 *
 * https://leetcode.com/problems/valid-parenthesis-string/description/
 *
 * algorithms
 * Medium (39.06%)
 * Likes:    6786
 * Dislikes: 215
 * Total Accepted:    531.5K
 * Total Submissions: 1.3M
 * Testcase Example:  '"()"'
 *
 * Given a string s containing only three types of characters: '(', ')' and
 * '*', return true if s is valid.
 * 
 * The following rules define a valid string:
 * 
 * 
 * Any left parenthesis '(' must have a corresponding right parenthesis
 * ')'.
 * Any right parenthesis ')' must have a corresponding left parenthesis
 * '('.
 * Left parenthesis '(' must go before the corresponding right parenthesis
 * ')'.
 * '*' could be treated as a single right parenthesis ')' or a single left
 * parenthesis '(' or an empty string "".
 * 
 * 
 * 
 * Example 1:
 * Input: s = "()"
 * Output: true
 * Example 2:
 * Input: s = "(*)"
 * Output: true
 * Example 3:
 * Input: s = "(*))"
 * Output: true
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 100
 * s[i] is '(', ')' or '*'.
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
    bool checkValidString(string s) {
        vector<int> l, star;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '(') {
                l.push_back(i);
            } else if (c == ')') {
                if (l.empty() && star.empty()) {
                    return false;
                }
                if (!l.empty()) {
                    l.pop_back();
                } else {
                    star.pop_back();
                }
            } else {
                star.push_back(i);
            }
        }

        for (int left : l) {
            auto it = ranges::upper_bound(star, left);
            if (it == star.end()) {
                return false;
            } else {
                star.erase(it);
            }
        }

        return true;
    }
};
// @lc code=end

