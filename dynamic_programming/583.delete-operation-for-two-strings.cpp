/*
 * @lc app=leetcode id=583 lang=cpp
 *
 * [583] Delete Operation for Two Strings
 *
 * https://leetcode.com/problems/delete-operation-for-two-strings/description/
 *
 * algorithms
 * Medium (64.12%)
 * Likes:    6076
 * Dislikes: 92
 * Total Accepted:    356.6K
 * Total Submissions: 550.8K
 * Testcase Example:  '"sea"\n"eat"'
 *
 * Given two strings word1 and word2, return the minimum number of steps
 * required to make word1 and word2 the same.
 * 
 * In one step, you can delete exactly one character in either string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: word1 = "sea", word2 = "eat"
 * Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to
 * make "eat" to "ea".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: word1 = "leetcode", word2 = "etco"
 * Output: 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= word1.length, word2.length <= 500
 * word1 and word2 consist of only lowercase English letters.
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
    // DP递推+空间优化
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> f(m + 1);
        ranges::iota(f, 0); // f(0, j) = j
        for (char x : word1) {
            int pre = f[0];
            f[0]++; // f(i, 0) = i = f(i - 1, 0) + 1;
            for (int j = 0; j < m; j++) {
                int tmp = f[j + 1]; // 在下一行就是f[i, j]
                f[j + 1] = x == word2[j] ? pre : min(f[j], f[j + 1]) + 1;
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

