/*
 * @lc app=leetcode id=2002 lang=cpp
 *
 * [2002] Maximum Product of the Length of Two Palindromic Subsequences
 *
 * https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/description/
 *
 * algorithms
 * Medium (61.50%)
 * Likes:    1001
 * Dislikes: 89
 * Total Accepted:    37.3K
 * Total Submissions: 60.4K
 * Testcase Example:  '"leetcodecom"'
 *
 * Given a string s, find two disjoint palindromic subsequences of s such that
 * the product of their lengths is maximized. The two subsequences are disjoint
 * if they do not both pick a character at the same index.
 * 
 * Return the maximum possible product of the lengths of the two palindromic
 * subsequences.
 * 
 * A subsequence is a string that can be derived from another string by
 * deleting some or no characters without changing the order of the remaining
 * characters. A string is palindromic if it reads the same forward and
 * backward.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetcodecom"
 * Output: 9
 * Explanation: An optimal solution is to choose "ete" for the 1^st subsequence
 * and "cdc" for the 2^nd subsequence.
 * The product of their lengths is: 3 * 3 = 9.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bb"
 * Output: 1
 * Explanation: An optimal solution is to choose "b" (the first character) for
 * the 1^st subsequence and "b" (the second character) for the 2^nd
 * subsequence.
 * The product of their lengths is: 1 * 1 = 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "accbcaxxcxx"
 * Output: 25
 * Explanation: An optimal solution is to choose "accca" for the 1^st
 * subsequence and "xxcxx" for the 2^nd subsequence.
 * The product of their lengths is: 5 * 5 = 25.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= s.length <= 12
 * s consists of lowercase English letters only.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // 回溯
    int maxProduct1(string s) {
        int ans = 0, n = s.length();
        
        string a, b;
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                if (a.size() * b.size() > ans && is_palindromic(a) && is_palindromic(b)) {
                    ans = a.size() * b.size();
                }
                return;
            }

            dfs(dfs, i + 1);

            a.push_back(s[i]);
            dfs(dfs, i + 1);
            a.pop_back();

            b.push_back(s[i]);
            dfs(dfs, i + 1);
            b.pop_back();
        };

        dfs(dfs, 0);
        return ans;
    }

    bool is_palindromic(string &s) {
        int n = s.length();
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    // 状压DP
    int maxProduct(string s) {
        int n = s.length(), m = 1 << n;
        vector<int> f(m, 0);
        for (int i = 0; i < n; i++) {
            f[1 << i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (s[i] == s[j]) {
                    for (int k = 0; k < 1 << (i - j - 1); k++) {
                        f[(k << (j + 1)) | (1 << j) | (1 << i)] =
                            f[k << (j + 1)] + 2;
                    }
                } else {
                    for (int k = 0; k < 1 << (i - j - 1); k++) {
                        f[(k << (j + 1)) | (1 << j) | (1 << i)] =
                            max(f[(k << (j + 1)) | (1 << j)],
                                f[(k << (j + 1)) | (1 << i)]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; i++) {
            ans = max(ans, f[i] * f[(m - 1) ^ i]);
        }
        return ans;
    }
};
// @lc code=end

