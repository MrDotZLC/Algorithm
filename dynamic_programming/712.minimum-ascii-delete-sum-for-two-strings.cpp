/*
 * @lc app=leetcode id=712 lang=cpp
 *
 * [712] Minimum ASCII Delete Sum for Two Strings
 *
 * https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
 *
 * algorithms
 * Medium (65.82%)
 * Likes:    4113
 * Dislikes: 110
 * Total Accepted:    172.4K
 * Total Submissions: 260.9K
 * Testcase Example:  '"sea"\n"eat"'
 *
 * Given two strings s1 and s2, return the lowest ASCII sum of deleted
 * characters to make two strings equal.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s1 = "sea", s2 = "eat"
 * Output: 231
 * Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to
 * the sum.
 * Deleting "t" from "eat" adds 116 to the sum.
 * At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum
 * possible to achieve this.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s1 = "delete", s2 = "leet"
 * Output: 403
 * Explanation: Deleting "dee" from "delete" to turn the string into "let",
 * adds 100[d] + 101[e] + 101[e] to the sum.
 * Deleting "e" from "leet" adds 101[e] to the sum.
 * At the end, both strings are equal to "let", and the answer is
 * 100+101+101+101 = 403.
 * If instead we turned both strings into "lee" or "eet", we would get answers
 * of 433 or 417, which are higher.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s1.length, s2.length <= 1000
 * s1 and s2 consist of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<int> f(m + 1);
        int s = 0;
        for (int j = 0; j < m; j++) { // f(0, j) = s2[j;
            s += s2[j];
            f[j + 1] = s;
        }
        s = 0;
        for (char x : s1) {
            int pre = s;
            s += x; // f(i, 0) = i = f(i - 1, 0) + 1;
            f[0] = s;   
            for (int j = 0; j < m; j++) {
                int tmp = f[j + 1]; // 在下一行就是f[i, j]
                f[j + 1] = x == s2[j] ? pre : min(f[j] + s2[j], f[j + 1] + x);
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

