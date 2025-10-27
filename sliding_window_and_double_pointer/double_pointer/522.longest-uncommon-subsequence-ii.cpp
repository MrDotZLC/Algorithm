/*
 * @lc app=leetcode id=522 lang=cpp
 *
 * [522] Longest Uncommon Subsequence II
 *
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/description/
 *
 * algorithms
 * Medium (43.26%)
 * Likes:    538
 * Dislikes: 1355
 * Total Accepted:    61.4K
 * Total Submissions: 141.5K
 * Testcase Example:  '["aba","cdc","eae"]'
 *
 * Given an array of strings strs, return the length of the longest uncommon
 * subsequence between them. If the longest uncommon subsequence does not
 * exist, return -1.
 * 
 * An uncommon subsequence between an array of strings is a string that is a
 * subsequence of one string but not the others.
 * 
 * A subsequence of a string s is a string that can be obtained after deleting
 * any number of characters from s.
 * 
 * 
 * For example, "abc" is a subsequence of "aebdc" because you can delete the
 * underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc"
 * include "aebdc", "aeb", and "" (empty string).
 * 
 * 
 * 
 * Example 1:
 * Input: strs = ["aba","cdc","eae"]
 * Output: 3
 * Example 2:
 * Input: strs = ["aaa","aaa","aa"]
 * Output: -1
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= strs.length <= 50
 * 1 <= strs[i].length <= 10
 * strs[i] consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int ans = -1;
        for (int i = 0; i < strs.size(); i++) {
            bool flag = false;
            if ((int)strs[i].length() <= ans) {
                continue;
            }
            for (int j = 0; j < strs.size(); j++) {
                if (i != j && is_sub_seq(strs[i], strs[j])) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            ans = strs[i].length();
        }
        return ans;
    }

    bool is_sub_seq(string &s, string &t) {
        int i = 0;
        for (char c : t) {
            if (s[i] == c && ++i == s.length()) {
                return true;
            }
        }
        return false;
    }
};
// @lc code=end

