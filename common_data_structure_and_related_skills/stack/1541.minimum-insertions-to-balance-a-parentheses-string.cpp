/*
 * @lc app=leetcode id=1541 lang=cpp
 *
 * [1541] Minimum Insertions to Balance a Parentheses String
 *
 * https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/description/
 *
 * algorithms
 * Medium (53.21%)
 * Likes:    1231
 * Dislikes: 289
 * Total Accepted:    78.7K
 * Total Submissions: 147.5K
 * Testcase Example:  '"(()))"'
 *
 * Given a parentheses string s containing only the characters '(' and ')'. A
 * parentheses string is balanced if:
 * 
 * 
 * Any left parenthesis '(' must have a corresponding two consecutive right
 * parenthesis '))'.
 * Left parenthesis '(' must go before the corresponding two consecutive right
 * parenthesis '))'.
 * 
 * 
 * In other words, we treat '(' as an opening parenthesis and '))' as a closing
 * parenthesis.
 * 
 * 
 * For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))"
 * and "(()))" are not balanced.
 * 
 * 
 * You can insert the characters '(' and ')' at any position of the string to
 * balance it if needed.
 * 
 * Return the minimum number of insertions needed to make s balanced.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "(()))"
 * Output: 1
 * Explanation: The second '(' has two matching '))', but the first '(' has
 * only ')' matching. We need to add one more ')' at the end of the string to
 * be "(())))" which is balanced.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "())"
 * Output: 0
 * Explanation: The string is already balanced.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "))())("
 * Output: 3
 * Explanation: Add '(' to match the first '))', Add '))' to match the last
 * '('.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of '(' and ')' only.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int minInsertions(string s) {
        int ans = 0, left = 0, n = s.length();
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '(') {
                left++;
            } else {
                if (i + 1 < n && s[i + 1] == ')') {
                    i++;
                } else {
                    ans++;
                }
                if (left > 0) {
                    left--;
                } else {
                    ans++;
                }
            }
        }
        ans += 2 * left;
        return ans;
    }
};
// @lc code=end

