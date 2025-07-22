/*
 * @lc app=leetcode id=1208 lang=cpp
 *
 * [1208] Get Equal Substrings Within Budget
 *
 * https://leetcode.com/problems/get-equal-substrings-within-budget/description/
 *
 * algorithms
 * Medium (59.05%)
 * Likes:    1874
 * Dislikes: 148
 * Total Accepted:    184.1K
 * Total Submissions: 311.8K
 * Testcase Example:  '"abcd"\n"bcdf"\n3'
 *
 * You are given two strings s and t of the same length and an integer
 * maxCost.
 * 
 * You want to change s to t. Changing the i^th character of s to i^th
 * character of t costs |s[i] - t[i]| (i.e., the absolute difference between
 * the ASCII values of the characters).
 * 
 * Return the maximum length of a substring of s that can be changed to be the
 * same as the corresponding substring of t with a cost less than or equal to
 * maxCost. If there is no substring from s that can be changed to its
 * corresponding substring from t, return 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcd", t = "bcdf", maxCost = 3
 * Output: 3
 * Explanation: "abc" of s can change to "bcd".
 * That costs 3, so the maximum length is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcd", t = "cdef", maxCost = 3
 * Output: 1
 * Explanation: Each character in s costs 2 to change to character in t,  so
 * the maximum length is 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abcd", t = "acde", maxCost = 0
 * Output: 1
 * Explanation: You cannot make any change, so the maximum length is 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * t.length == s.length
 * 0 <= maxCost <= 10^6
 * s and t consist of only lowercase English letters.
 * 
 * 
 */
#include <string>
#include <iostream>
using namespace std;
// @lc code=start
class Solution {
    /**
     * 1. sliding window (√)
     * 2. sliding window: optimize memory (√)
     * 3. the sum of prefix and reverse (√)
     */
public:
    int equalSubstring(string s, string t, int maxCost) {
        int res = 0, cost = 0, l = 0;
        for (int r = 0; r < s.length(); r++) {
            cost += abs(s[r] - t[r]);
            while (cost > maxCost) {
                cost -= abs(s[l] - t[l++]);
            }
            res = max(res, r - l + 1);
        }
        return res;
    }

    int equalSubstring2(string s, string t, int maxCost) {
        int cost = 0, l = 0;
        for (int r = 0; r < s.length(); r++) {
            cost += abs(s[r] - t[r]);
            // Always maintain the maximum length window,
            // even if it results in cost overflow.
            if (cost > maxCost) {
                cost -= abs(s[l] - t[l++]);
            }
        }
        return s.size() - l;
    }
};
// @lc code=end

int main() {
    Solution sol;

    string s = "abcdeaaabcd", t = "abczeaaazcd";
    auto res = sol.equalSubstring2(s, t, 3);
    cout << res << endl;
}