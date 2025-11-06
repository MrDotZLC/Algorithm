/*
 * @lc app=leetcode id=139 lang=cpp
 *
 * [139] Word Break
 *
 * https://leetcode.com/problems/word-break/description/
 *
 * algorithms
 * Medium (48.39%)
 * Likes:    18369
 * Dislikes: 882
 * Total Accepted:    2.2M
 * Total Submissions: 4.5M
 * Testcase Example:  '"leetcode"\n["leet","code"]'
 *
 * Given a string s and a dictionary of strings wordDict, return true if s can
 * be segmented into a space-separated sequence of one or more dictionary
 * words.
 * 
 * Note that the same word in the dictionary may be reused multiple times in
 * the segmentation.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetcode", wordDict = ["leet","code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet
 * code".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "applepenapple", wordDict = ["apple","pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple
 * pen apple".
 * Note that you are allowed to reuse a dictionary word.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 300
 * 1 <= wordDict.length <= 1000
 * 1 <= wordDict[i].length <= 20
 * s and wordDict[i] consist of only lowercase English letters.
 * All the strings of wordDict are unique.
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool wordBreak1(string s, vector<string>& wordDict) {
        int mx_len = ranges::max(wordDict, {}, &string::length).length();
        unordered_set<string> words(wordDict.begin(), wordDict.end());

        int n = s.length();
        vector<int> memo(n + 1, -1); 
        auto dfs = [&](auto &dfs, int i) -> bool {
            if (i == 0) {
                return true;
            }
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            for (int j = i - 1; j >= max(i - mx_len, 0); j--) {
                if (words.contains(s.substr(j, i - j)) && dfs(dfs, j)) {
                    return res = true;
                }
            }
            return res = false;
        };
        return dfs(dfs, n);
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        int mx_len = ranges::max(wordDict, {}, &string::length).length();
        unordered_set<string> words(wordDict.begin(), wordDict.end());

        int n = s.length();
        vector<int> f(n + 1, 0);
        f[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = i -1; j >= max(i - mx_len, 0); j--) {
                if (words.contains(s.substr(j, i - j)) && f[j]) {
                    f[i] = true;
                    break;
                }
            }
        }
        return f[n];
    }
};
// @lc code=end

