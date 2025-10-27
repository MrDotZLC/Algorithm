/*
 * @lc app=leetcode id=76 lang=cpp
 *
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (45.61%)
 * Likes:    19176
 * Dislikes: 798
 * Total Accepted:    1.8M
 * Total Submissions: 4M
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * Given two strings s and t of lengths m and n respectively, return the
 * minimum window substring of s such that every character in t (including
 * duplicates) is included in the window. If there is no such substring, return
 * the empty string "".
 * 
 * The testcases will be generated such that the answer is unique.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string s is the minimum window.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 10^5
 * s and t consist of uppercase and lowercase English letters.
 * 
 * 
 * 
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        int freq_s[128] = {};
        int freq_t[128] = {};
        int n = s.length(), m = t.length();

        for (char c : t) {
            ++freq_t[c];
        }

        int res_l = -1, res_r = n, l = 0;
        for (int r = 0; r < n; r++) {
            ++freq_s[s[r]];
            while (is_cover(freq_s, freq_t)) {
                if (res_r - res_l > r - l) {
                    res_r = r;
                    res_l = l;
                }
                --freq_s[s[l++]];
            }
        }
        return res_l < 0 ? "" : s.substr(res_l, res_r - res_l + 1);
    }

    string minWindow(string s, string t) {
        int freq_t[128] = {};
        int n = s.length(), m = t.length();
        int less = 0;

        for (char c : t) {
            if (freq_t[c] == 0) {
                ++less;
            }
            ++freq_t[c];
        }

        int res_l = -1, res_r = n, l = 0;
        for (int r = 0; r < n; r++) {
            char cur = s[r];
            --freq_t[cur];
            if (freq_t[cur] == 0) {
                --less;
            }

            while (less == 0) {
                if (res_r - res_l > r - l) {
                    res_r = r;
                    res_l = l;
                }
                char x = s[l];
                if (freq_t[l] == 0) {
                    ++less;
                }
                ++freq_t[x];
                ++l;
            }
        }
        return res_l < 0 ? "" : s.substr(res_l, res_r - res_l + 1);
    }

    bool is_cover(int freq_s[], int freq_t[]) {
        for (int i = 'A'; i <= 'Z'; i++) {
            if (freq_s[i] < freq_t[i]) {
                return false;
            }
        }
        for (int i = 'a'; i <= 'z'; i++) {
            if (freq_s[i] < freq_t[i]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

