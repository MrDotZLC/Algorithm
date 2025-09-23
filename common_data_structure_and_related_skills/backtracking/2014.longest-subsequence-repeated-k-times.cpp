/*
 * @lc app=leetcode id=2014 lang=cpp
 *
 * [2014] Longest Subsequence Repeated k Times
 *
 * https://leetcode.com/problems/longest-subsequence-repeated-k-times/description/
 *
 * algorithms
 * Hard (71.60%)
 * Likes:    815
 * Dislikes: 115
 * Total Accepted:    71.7K
 * Total Submissions: 100.4K
 * Testcase Example:  '"letsleetcode"\n2'
 *
 * You are given a string s of length n, and an integer k. You are tasked to
 * find the longest subsequence repeated k times in string s.
 * 
 * A subsequence is a string that can be derived from another string by
 * deleting some or no characters without changing the order of the remaining
 * characters.
 * 
 * A subsequence seq is repeated k times in the string s if seq * k is a
 * subsequence of s, where seq * k represents a string constructed by
 * concatenating seq k times.
 * 
 * 
 * For example, "bba" is repeated 2 times in the string "bababcba", because the
 * string "bbabba", constructed by concatenating "bba" 2 times, is a
 * subsequence of the string "bababcba".
 * 
 * 
 * Return the longest subsequence repeated k times in string s. If multiple
 * such subsequences are found, return the lexicographically largest one. If
 * there is no such subsequence, return an empty string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "letsleetcode", k = 2
 * Output: "let"
 * Explanation: There are two longest subsequences repeated 2 times: "let" and
 * "ete".
 * "let" is the lexicographically largest one.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bb", k = 2
 * Output: "b"
 * Explanation: The longest subsequence repeated 2 times is "b".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "ab", k = 2
 * Output: ""
 * Explanation: There is no subsequence repeated 2 times. Empty string is
 * returned.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == s.length
 * 2 <= k <= 2000
 * 2 <= n < min(2001, k * 8)
 * s consists of lowercase English letters.
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
    string longestSubsequenceRepeatedK(string s, int k) {
        int cnt[26];
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string a;
        for (int i = 25; i >= 0; i--) {
            a.insert(a.end(), cnt[i] / k, 'a' + i);
        }

        string ans;
        permute_func(a, [&](const string &seq) -> bool {
            if (!is_sub_sequence(s, seq, k)) {
                return false;
            }
            if (seq.length() > ans.length() || seq.length() == ans.length() && seq > ans) {
                ans = seq;
            }
            return true;
        });
        return ans;
    }

    void permute_func(const string &s, auto &&f) {
        int n = s.length();
        string path;
        vector<int> on_path(n);
        auto dfs = [&](auto &dfs) -> void {
            if (!path.empty() && !f(path)) { // 剪枝
                return;
            }
            if (path.length() == n) {
                return;
            }

            for (int j = 0; j < n; j++) {
                if (on_path[j] || j > 0 && s[j] == s[j - 1] && !on_path[j - 1]) {
                    continue;
                }
                path += s[j];
                on_path[j] = 1;
                dfs(dfs);
                on_path[j] = 0;
                path.pop_back();
            }
        };
        dfs(dfs);
    }

    bool is_sub_sequence(const string &s, const string &seq, int k) {
        int n = seq.length();
        int i = 0;
        for (char c : s) {
            if (seq[i % n] == c) {
                i++;
                if (i == n * k) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end

