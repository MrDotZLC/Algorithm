/*
 * @lc app=leetcode id=140 lang=cpp
 *
 * [140] Word Break II
 *
 * https://leetcode.com/problems/word-break-ii/description/
 *
 * algorithms
 * Hard (53.84%)
 * Likes:    7458
 * Dislikes: 544
 * Total Accepted:    770.6K
 * Total Submissions: 1.4M
 * Testcase Example:  '"catsanddog"\n["cat","cats","and","sand","dog"]'
 *
 * Given a string s and a dictionary of strings wordDict, add spaces in s to
 * construct a sentence where each word is a valid dictionary word. Return all
 * such possible sentences in any order.
 * 
 * Note that the same word in the dictionary may be reused multiple times in
 * the segmentation.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "pineapplepenapple", wordDict =
 * ["apple","pen","applepen","pine","pineapple"]
 * Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
 * Explanation: Note that you are allowed to reuse a dictionary word.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 20
 * 1 <= wordDict.length <= 1000
 * 1 <= wordDict[i].length <= 10
 * s and wordDict[i] consist of only lowercase English letters.
 * All the strings of wordDict are unique.
 * Input is generated in a way that the length of the answer doesn't exceed
 * 10^5.
 * 
 * 
 */
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        unordered_set<string> set(wordDict.begin(), wordDict.end());
        
        vector<string> ans;
        auto dfs = [&](auto &dfs, int pos, string res) -> void {
            if (pos == n) {
                ans.push_back(res.substr(1));
                return;
            }

            for (int i = pos; i < n; i++) {
                string sub = s.substr(pos, i - pos + 1);
                if (set.count(sub)) {
                    dfs(dfs, i + 1, res + " " + sub);
                }
            }
        };
        dfs(dfs, 0, "");
        return ans;
    }
};
// @lc code=end

