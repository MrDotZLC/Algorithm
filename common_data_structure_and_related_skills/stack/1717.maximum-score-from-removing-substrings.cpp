/*
 * @lc app=leetcode id=1717 lang=cpp
 *
 * [1717] Maximum Score From Removing Substrings
 *
 * https://leetcode.com/problems/maximum-score-from-removing-substrings/description/
 *
 * algorithms
 * Medium (62.84%)
 * Likes:    1903
 * Dislikes: 136
 * Total Accepted:    239.1K
 * Total Submissions: 359.4K
 * Testcase Example:  '"cdbcbbaaabab"\n4\n5'
 *
 * You are given a string s and two integers x and y. You can perform two types
 * of operations any number of times.
 * 
 * 
 * Remove substring "ab" and gain x points.
 * 
 * 
 * For example, when removing "ab" from "cabxbae" it becomes
 * "cxbae".
 * 
 * 
 * Remove substring "ba" and gain y points.
 * 
 * For example, when removing "ba" from "cabxbae" it becomes
 * "cabxe".
 * 
 * 
 * 
 * 
 * Return the maximum points you can gain after applying the above operations
 * on s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "cdbcbbaaabab", x = 4, y = 5
 * Output: 19
 * Explanation:
 * - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5
 * points are added to the score.
 * - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4
 * points are added to the score.
 * - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points
 * are added to the score.
 * - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are
 * added to the score.
 * Total score = 5 + 4 + 5 + 5 = 19.
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aabbaaxybbaabb", x = 5, y = 4
 * Output: 20
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * 1 <= x, y <= 10^4
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int ans = 0;
        char t0 = 'a', t1 = 'b';
        if (x < y) {
            swap(t0, t1);
            swap(x, y);
        }
        string st;
        for (int i = 0; i < s.length(); i++) {
            if (st.empty() || !(st.back() == t0 && s[i] == t1)) {
                st.push_back(s[i]);
            } else {
                st.pop_back();
                ans += x;
            }
        }
        s.clear();
        for (int i = 0; i < st.size(); i++) {
            if (s.empty() || !(s.back() == t1 && st[i] == t0)) {
                s.push_back(st[i]);
            } else {
                s.pop_back();
                ans += y;
            }
        }
        return ans;
    }
};
// @lc code=end

