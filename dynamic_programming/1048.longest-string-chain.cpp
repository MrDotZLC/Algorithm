/*
 * @lc app=leetcode id=1048 lang=cpp
 *
 * [1048] Longest String Chain
 *
 * https://leetcode.com/problems/longest-string-chain/description/
 *
 * algorithms
 * Medium (62.19%)
 * Likes:    7716
 * Dislikes: 268
 * Total Accepted:    500.3K
 * Total Submissions: 799.7K
 * Testcase Example:  '["a","b","ba","bca","bda","bdca"]'
 *
 * You are given an array of words where each word consists of lowercase
 * English letters.
 * 
 * wordA is a predecessor of wordB if and only if we can insert exactly one
 * letter anywhere in wordA without changing the order of the other characters
 * to make it equal to wordB.
 * 
 * 
 * For example, "abc" is a predecessor of "abac", while "cba" is not a
 * predecessor of "bcad".
 * 
 * 
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1,
 * where word1 is a predecessor of word2, word2 is a predecessor of word3, and
 * so on. A single word is trivially a word chain with k == 1.
 * 
 * Return the length of the longest possible word chain with words chosen from
 * the given list of words.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["a","b","ba","bca","bda","bdca"]
 * Output: 4
 * Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
 * Output: 5
 * Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc",
 * "pcxbc", "pcxbcf"].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: words = ["abcd","dbqca"]
 * Output: 1
 * Explanation: The trivial word chain ["abcd"] is one of the longest word
 * chains.
 * ["abcd","dbqca"] is not a valid word chain because the ordering of the
 * letters is changed.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 1000
 * 1 <= words[i].length <= 16
 * words[i] only consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化递归
    int longestStrChain1(vector<string>& words) {
        unordered_map<string, int> ws;
        for (auto &s : words) {
            ws[s] = 0;
        }
        auto dfs = [&](this auto &&dfs, const string& s) -> int {
            int &res = ws[s];
            if (res) {
                return res;
            }
            for (int i = 0; i < s.length(); i++) {
                string t = s.substr(0, i) + s.substr(i + 1);
                if (ws.count(t)) {
                    res = max(res, dfs(t));
                }
            }
            return ++res;
        };
        int ans = 0;
        for (auto &[s, _] : ws) {
            ans = max(ans, dfs(s));
        }
        return ans;
    }

    // DP
    int longestStrChain(vector<string>& words) {
        ranges::sort(words, {}, &string::length);
        unordered_map<string, int> f;
        int ans = 0;
        for (auto &s : words) {
            int res = 0;
            for (int i = 0; i < s.length(); i++) {
                auto it = f.find(s.substr(0, i) + s.substr(i + 1));
                if (it != f.end()) {
                    res = max(res, it->second);
                }
            }
            f[s] = res + 1;
            ans = max(ans, f[s]);
        }
        return ans;
    }
};
// @lc code=end

