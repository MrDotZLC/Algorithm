/*
 * @lc app=leetcode id=1081 lang=cpp
 *
 * [1081] Smallest Subsequence of Distinct Characters
 *
 * https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/description/
 *
 * algorithms
 * Medium (62.16%)
 * Likes:    2714
 * Dislikes: 199
 * Total Accepted:    88.4K
 * Total Submissions: 141.3K
 * Testcase Example:  '"bcabc"'
 *
 * Given a string s, return the lexicographically smallest subsequence of s
 * that contains all the distinct characters of s exactly once.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "bcabc"
 * Output: "abc"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "cbacdcbc"
 * Output: "acdb"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s consists of lowercase English letters.
 * 
 * 
 * 
 * Note: This question is the same as 316:
 * https://leetcode.com/problems/remove-duplicate-letters/
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    string smallestSubsequence(string s) {
        int left[26]{}, in_ans[26]{};
        for (char c : s) {
            left[c - 'a']++;
        }

        string ans;
        for (char c : s) {
            left[c - 'a']--;
            if (in_ans[c - 'a']) {
                continue;
            }
            while (!ans.empty() && ans.back() > c && left[ans.back() - 'a']) {
                in_ans[ans.back() - 'a'] = 0;
                ans.pop_back();
            }
            in_ans[c - 'a'] = 1;
            ans += c;
        }

        return ans;
    }
};
// @lc code=end

