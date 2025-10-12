/*
 * @lc app=leetcode id=394 lang=cpp
 *
 * [394] Decode String
 *
 * https://leetcode.com/problems/decode-string/description/
 *
 * algorithms
 * Medium (61.33%)
 * Likes:    13644
 * Dislikes: 680
 * Total Accepted:    1.1M
 * Total Submissions: 1.8M
 * Testcase Example:  '"3[a]2[bc]"'
 *
 * Given an encoded string, return its decoded string.
 * 
 * The encoding rule is: k[encoded_string], where the encoded_string inside the
 * square brackets is being repeated exactly k times. Note that k is guaranteed
 * to be a positive integer.
 * 
 * You may assume that the input string is always valid; there are no extra
 * white spaces, square brackets are well-formed, etc. Furthermore, you may
 * assume that the original data does not contain any digits and that digits
 * are only for those repeat numbers, k. For example, there will not be input
 * like 3a or 2[4].
 * 
 * The test cases are generated so that the length of the output will never
 * exceed 10^5.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "2[abc]3[cd]ef"
 * Output: "abcabccdcdcdef"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 30
 * s consists of lowercase English letters, digits, and square brackets
 * '[]'.
 * s is guaranteed to be a valid input.
 * All the integers in s are in the range [1, 300].
 * 
 * 
 */
#include <vector>
#include <string>
#include <cctype>
using namespace std;
// @lc code=start
class Solution {
public:
    string decodeString1(string s) {
        vector<string> s_stk;
        s_stk.push_back("");
        vector<int> n_stk;
        int k = 0;
        for (char c : s) {
            if (isdigit(c)) {
                k = k * 10 + c - 48;
            } else if (islower(c)) {
                s_stk.back() += c;
            } else if (c == '[') {
                n_stk.push_back(k);
                k = 0;
                s_stk.push_back("");
            } else if (c == ']') {
                string str = s_stk.back();
                s_stk.pop_back();
                repeat(str, n_stk.back());
                s_stk.back() += move(str);
                n_stk.pop_back();
            }
        }
        return s_stk.back();
    }

    string decodeString(string s) {
        vector<pair<string, int>> stk;
        string str;
        int k = 0;
        for (char c : s) {
            if (isdigit(c)) {
                k = k * 10 + c - 48;
            } else if (islower(c)) {
                str += c;
            } else if (c == '[') {
                stk.emplace_back(move(str), k);
                k = 0;
            } else if (c == ']') {
                auto &[pre_str, pre_k] = stk.back();
                repeat(str, pre_k);
                str = pre_str + move(str);
                stk.pop_back(); // 引用还在用，不能提前pop释放资源
            }
        }
        return str;
    }

    void repeat(string &s, int n) {
        int size = s.length();
        s.reserve(size * n);
        for (int i = 1; i < n; i *= 2) {
            if (i * 2 <= n)
                s += s;  // 扩大一倍
            else
                s += s.substr(0, (n - i) * size);
        }
    }
};
// @lc code=end

