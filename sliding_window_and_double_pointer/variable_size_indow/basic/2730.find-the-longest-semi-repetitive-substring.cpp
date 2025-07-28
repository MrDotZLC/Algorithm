/*
 * @lc app=leetcode id=2730 lang=cpp
 *
 * [2730] Find the Longest Semi-Repetitive Substring
 *
 * https://leetcode.com/problems/find-the-longest-semi-repetitive-substring/description/
 *
 * algorithms
 * Medium (37.40%)
 * Likes:    310
 * Dislikes: 88
 * Total Accepted:    29.6K
 * Total Submissions: 79.1K
 * Testcase Example:  '"52233"'
 *
 * You are given a digit string s that consists of digits from 0 to 9.
 * 
 * A string is called semi-repetitive if there is at most one adjacent pair of
 * the same digit. For example, "0010", "002020", "0123", "2002", and "54944"
 * are semi-repetitive while the following are not: "00101022" (adjacent same
 * digit pairs are 00 and 22), and "1101234883" (adjacent same digit pairs are
 * 11 and 88).
 * 
 * Return the length of the longest semi-repetitive substring of s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "52233"
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The longest semi-repetitive substring is "5223". Picking the whole string
 * "52233" has two adjacent same digit pairs 22 and 33, but at most one is
 * allowed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "5494"
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * s is a semi-repetitive string.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "1111111"
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * The longest semi-repetitive substring is "11". Picking the substring "111"
 * has two adjacent same digit pairs, but at most one is allowed.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 50
 * '0' <= s[i] <= '9'
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int ans = 1, l = 0, n = s.length(), repeat = 0;
        
        for (int r = 1; r < n; r++) {
            if (s[r - 1] == s[r]) {
                ++repeat;
            }
            while (repeat > 1 && l < r) {
                ++l;
                if (s[l - 1] == s[l]) {
                    --repeat;
                }
            }
            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};
// @lc code=end

