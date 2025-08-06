/*
 * @lc app=leetcode id=1957 lang=cpp
 *
 * [1957] Delete Characters to Make Fancy String
 *
 * https://leetcode.com/problems/delete-characters-to-make-fancy-string/description/
 *
 * algorithms
 * Easy (74.37%)
 * Likes:    1157
 * Dislikes: 53
 * Total Accepted:    328.2K
 * Total Submissions: 441.7K
 * Testcase Example:  '"leeetcode"'
 *
 * A fancy string is a string where no three consecutive characters are equal.
 * 
 * Given a string s, delete the minimum possible number of characters from s to
 * make it fancy.
 * 
 * Return the final string after the deletion. It can be shown that the answer
 * will always be unique.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leeetcode"
 * Output: "leetcode"
 * Explanation:
 * Remove an 'e' from the first group of 'e's to create "leetcode".
 * No three consecutive characters are equal, so return "leetcode".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaabaaaa"
 * Output: "aabaa"
 * Explanation:
 * Remove an 'a' from the first group of 'a's to create "aabaaaa".
 * Remove two 'a's from the second group of 'a's to create "aabaa".
 * No three consecutive characters are equal, so return "aabaa".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "aab"
 * Output: "aab"
 * Explanation: No three consecutive characters are equal, so return "aab".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists only of lowercase English letters.
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
    string makeFancyString(string s) {
        string ans;
        int cnt = 0;
        for (int i = 0; i < s.length(); i++) {
            cnt++;
            if (cnt < 3) {
                ans += s[i];
            }
            if (i < s.length() - 1 && s[i] != s[i + 1]) {
                cnt = 0;
            }
        }
        return ans;
    }
};
// @lc code=end

