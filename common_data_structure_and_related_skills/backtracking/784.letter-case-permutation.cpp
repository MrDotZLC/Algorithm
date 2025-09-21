/*
 * @lc app=leetcode id=784 lang=cpp
 *
 * [784] Letter Case Permutation
 *
 * https://leetcode.com/problems/letter-case-permutation/description/
 *
 * algorithms
 * Medium (75.25%)
 * Likes:    4790
 * Dislikes: 158
 * Total Accepted:    351.9K
 * Total Submissions: 466.8K
 * Testcase Example:  '"a1b2"'
 *
 * Given a string s, you can transform every letter individually to be
 * lowercase or uppercase to create another string.
 * 
 * Return a list of all possible strings we could create. Return the output in
 * any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "a1b2"
 * Output: ["a1b2","a1B2","A1b2","A1B2"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "3z4"
 * Output: ["3z4","3Z4"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 12
 * s consists of lowercase English letters, uppercase English letters, and
 * digits.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        int n = s.length();

        auto change = [](char &c) {
            if (c < 'a') {
                c += 32;
            } else {
                c -= 32;
            }
        };

        vector<string> ans;
        auto dfs = [&](auto &dfs, int i) -> void {
            while (i < n && s[i] < 'A') {
                i++;
            }
            if (i == n) {
                ans.push_back(s);
                return;
            }
            dfs(dfs, i + 1);
            change(s[i]);
            dfs(dfs, i + 1);
            change(s[i]);
        };

        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

