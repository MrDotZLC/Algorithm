/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (37.06%)
 * Likes:    42541
 * Dislikes: 2069
 * Total Accepted:    7.8M
 * Total Submissions: 21M
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string s, find the length of the longest substring without duplicate
 * characters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Notice that the answer must be a substring, "pwke" is a subsequence and not
 * a substring.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= s.length <= 5 * 10^4
 * s consists of English letters, digits, symbols and spaces.
 * 
 * 
 */
#include <string>
#include <iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, r = 0;
        string cur = "";
        while (r < s.length()) {
            while (cur.find(s[r]) != string::npos) {
                cur.erase(0, 1);
            }
            cur.push_back(s[r]);
            res = max<size_t>(res, cur.length());
            ++r;
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution sol;
    string s = "bbbbb";
    auto res = sol.lengthOfLongestSubstring(s);
    cout << res << endl;
}