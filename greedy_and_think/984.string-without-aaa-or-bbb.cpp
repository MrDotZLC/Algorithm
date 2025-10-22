/*
 * @lc app=leetcode id=984 lang=cpp
 *
 * [984] String Without AAA or BBB
 *
 * https://leetcode.com/problems/string-without-aaa-or-bbb/description/
 *
 * algorithms
 * Medium (44.59%)
 * Likes:    860
 * Dislikes: 376
 * Total Accepted:    57.9K
 * Total Submissions: 129.4K
 * Testcase Example:  '1\n2'
 *
 * Given two integers a and b, return any string s such that:
 * 
 * 
 * s has length a + b and contains exactly a 'a' letters, and exactly b 'b'
 * letters,
 * The substring 'aaa' does not occur in s, and
 * The substring 'bbb' does not occur in s.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: a = 1, b = 2
 * Output: "abb"
 * Explanation: "abb", "bab" and "bba" are all correct answers.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: a = 4, b = 1
 * Output: "aabaa"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= a, b <= 100
 * It is guaranteed such an s exists for the given a and b.
 * 
 * 
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string ans;
        int cnta = 0, cntb = 0;
        while (a > 0 || b > 0) {
            if (a > b) {
                if (cnta < 2) {
                    ans += 'a';
                    cnta++;
                    a--;
                    cntb = 0;
                } else {
                    ans += 'b';
                    cntb++;
                    b--;
                    cnta = 0;
                }
            } else {
                if (cntb < 2) {
                    ans += 'b';
                    cntb++;
                    b--;
                    cnta = 0;
                } else {
                    ans += 'a';
                    cnta++;
                    a--;
                    cntb = 0;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

