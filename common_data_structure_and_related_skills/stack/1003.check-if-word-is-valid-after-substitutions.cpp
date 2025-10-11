/*
 * @lc app=leetcode id=1003 lang=cpp
 *
 * [1003] Check If Word Is Valid After Substitutions
 *
 * https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/description/
 *
 * algorithms
 * Medium (60.31%)
 * Likes:    1066
 * Dislikes: 472
 * Total Accepted:    80.2K
 * Total Submissions: 132.2K
 * Testcase Example:  '"aabcbc"'
 *
 * Given a string s, determine if it is valid.
 * 
 * A string s is valid if, starting with an empty string t = "", you can
 * transform t into s after performing the following operation any number of
 * times:
 * 
 * 
 * Insert string "abc" into any position in t. More formally, t becomes tleft +
 * "abc" + tright, where t == tleft + tright. Note that tleft and tright may be
 * empty.
 * 
 * 
 * Return true if s is a valid string, otherwise, return false.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aabcbc"
 * Output: true
 * Explanation:
 * "" -> "abc" -> "aabcbc"
 * Thus, "aabcbc" is valid.
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcabcababcc"
 * Output: true
 * Explanation:
 * "" -> "abc" -> "abcabc" -> "abcabcabc" -> "abcabcababcc"
 * Thus, "abcabcababcc" is valid.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abccba"
 * Output: false
 * Explanation: It is impossible to get "abccba" using the operation.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2 * 10^4
 * s consists of letters 'a', 'b', and 'c'
 * 
 * 
 */
#include <stack>
#include <string>
#include <string_view>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isValid1(string s) {
        string st;
        for (char c: s) {
            st.push_back(c);
            if (st.size() >= 3 &&
                string_view(st.data() + st.size() - 3, 3) == "abc") {
                st.pop_back();
                st.pop_back();
                st.pop_back();
            }
        }
        return st.size() == 0;
    }

    bool isValid(string s) { // s 同时作为栈
        int i = 0; // i-1为栈顶下标，i=0表示栈为空
        for (char c: s) {
            if (c > 'a' && (i == 0 || c - s[--i] != 1)) {
                return false;
            }
            if (c < 'c') {
                s[i++] = c;
            }
        }
        return i == 0;
    }
};
// @lc code=end

