/*
 * @lc app=leetcode id=1745 lang=cpp
 *
 * [1745] Palindrome Partitioning IV
 *
 * https://leetcode.com/problems/palindrome-partitioning-iv/description/
 *
 * algorithms
 * Hard (44.84%)
 * Likes:    956
 * Dislikes: 31
 * Total Accepted:    31.3K
 * Total Submissions: 69.5K
 * Testcase Example:  '"abcbdd"'
 *
 * Given a string s, return true if it is possible to split the string s into
 * three non-empty palindromic substrings. Otherwise, return false.​​​​​
 * 
 * A string is said to be palindrome if it the same string when reversed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcbdd"
 * Output: true
 * Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are
 * palindromes.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bcbddxy"
 * Output: false
 * Explanation: s cannot be split into 3 palindromes.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 2000
 * s​​​​​​ consists only of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP+记忆化+预处理+k代表切分次数
    bool checkPartitioning1(string s) {
        int n = s.length();
        vector palindrome_check(n, vector<bool>(n, true));
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                palindrome_check[i][j] =
                    (palindrome_check[i + 1][j - 1]) &&
                    (s[i] == s[j]);
            }
        }

        vector<bool> f = move(palindrome_check[0]);
        for (int i = 1; i < 3; i++) {
            for (int j = n - (3 - i); j >= i; j--) {
                f[j] = false;
                for (int l = i; l <= j; l++) {
                    f[j] = f[j] || f[l - 1] && palindrome_check[l][j];
                }
            }
        }
        return f[n - 1];
    }
};
// @lc code=end

