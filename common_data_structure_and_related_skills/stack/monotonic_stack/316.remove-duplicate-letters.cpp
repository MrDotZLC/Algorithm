/*
 * @lc app=leetcode id=316 lang=cpp
 *
 * [316] Remove Duplicate Letters
 *
 * https://leetcode.com/problems/remove-duplicate-letters/description/
 *
 * algorithms
 * Medium (51.54%)
 * Likes:    9113
 * Dislikes: 688
 * Total Accepted:    408.1K
 * Total Submissions: 784.4K
 * Testcase Example:  '"bcabc"'
 *
 * Given a string s, remove duplicate letters so that every letter appears once
 * and only once. You must make sure your result is the smallest in
 * lexicographical order among all possible results.
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
 * 1 <= s.length <= 10^4
 * s consists of lowercase English letters.
 * 
 * 
 * 
 * Note: This question is the same as 1081:
 * https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
 * 
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    string removeDuplicateLetters(string s) {
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

