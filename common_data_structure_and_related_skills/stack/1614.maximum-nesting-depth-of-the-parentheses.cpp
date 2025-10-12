/*
 * @lc app=leetcode id=1614 lang=cpp
 *
 * [1614] Maximum Nesting Depth of the Parentheses
 *
 * https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/description/
 *
 * algorithms
 * Easy (84.40%)
 * Likes:    2721
 * Dislikes: 521
 * Total Accepted:    495.9K
 * Total Submissions: 586.6K
 * Testcase Example:  '"(1+(2*3)+((8)/4))+1"'
 *
 * Given a valid parentheses string s, return the nesting depth of s. The
 * nesting depth is the maximum number of nested parentheses.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "(1+(2*3)+((8)/4))+1"
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * Digit 8 is inside of 3 nested parentheses in the string.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "(1)+((2))+(((3)))"
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * Digit 3 is inside of 3 nested parentheses in the string.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "()(())((()()))"
 * 
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 100
 * s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and
 * ')'.
 * It is guaranteed that parentheses expression s is a VPS.
 * 
 * 
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxDepth(string s) {
        int ans = 0, size = 0;
        for (char ch : s) {
            if (ch == '(') {
                ++size;
                ans = max(ans, size);
            } else if (ch == ')') {
                --size;
            }
        }
        return ans;
    }
};
// @lc code=end

