/*
 * @lc app=leetcode id=940 lang=cpp
 *
 * [940] Distinct Subsequences II
 *
 * https://leetcode.com/problems/distinct-subsequences-ii/description/
 *
 * algorithms
 * Hard (43.61%)
 * Likes:    1810
 * Dislikes: 39
 * Total Accepted:    49.2K
 * Total Submissions: 112.2K
 * Testcase Example:  '"abc"'
 *
 * Given a string s, return the number of distinct non-empty subsequences of s.
 * Since the answer may be very large, return it modulo 10^9 + 7.
 * A subsequence of a string is a new string that is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (i.e., "ace" is a
 * subsequence of "abcde" while "aec" is not.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abc"
 * Output: 7
 * Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac",
 * "bc", and "abc".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aba"
 * Output: 6
 * Explanation: The 6 distinct subsequences are "a", "b", "ab", "aa", "ba", and
 * "aba".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "aaa"
 * Output: 3
 * Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2000
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9+7;
    // DP
    int distinctSubseqII1(string s) {
        int n = s.length();
        vector<array<int, 26>> f(n + 1);
        for (int i = 0; i < n; i++) {
            f[i + 1] = f[i];
            f[i + 1][s[i] - 'a'] = reduce(f[i].begin(), f[i].end(), 1LL) % MOD;
        }
        return reduce(f[n].begin(), f[n].end(), 0LL) % MOD;
    }

    // DP + 空间优化
    int distinctSubseqII2(string s) {
        int n = s.length();
        array<int, 26> f;
        for (int i = 0; i < n; i++) {
            f[s[i] - 'a'] = reduce(f.begin(), f.end(), 1LL) % MOD;
        }
        return reduce(f.begin(), f.end(), 0LL) % MOD;
    }

    // DP + 空间优化 + 计算优化
    int distinctSubseqII(string s) {
        int n = s.length(), total = 0;
        array<int, 26> f;
        for (char c : s) {
            c -= 'a';
            int others = (total - f[c] + MOD) % MOD;
            f[c] = 1 + total;
            total = (f[c] + others) % MOD;
        }
        return total;
    }
};
// @lc code=end

