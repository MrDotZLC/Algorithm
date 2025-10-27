/*
 * @lc app=leetcode id=1446 lang=cpp
 *
 * [1446] Consecutive Characters
 *
 * https://leetcode.com/problems/consecutive-characters/description/
 *
 * algorithms
 * Easy (60.27%)
 * Likes:    1803
 * Dislikes: 35
 * Total Accepted:    207.1K
 * Total Submissions: 343.6K
 * Testcase Example:  '"leetcode"'
 *
 * The power of the string is the maximum length of a non-empty substring that
 * contains only one unique character.
 * 
 * Given a string s, return the power of s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetcode"
 * Output: 2
 * Explanation: The substring "ee" is of length 2 with the character 'e'
 * only.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abbcccddddeeeeedcba"
 * Output: 5
 * Explanation: The substring "eeeee" is of length 5 with the character 'e'
 * only.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 500
 * s consists of only lowercase English letters.
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
    int maxPower(string s) {
        int ans = 1, cnt = 1;
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == s[i - 1]) {
                ++cnt;
                ans = max(ans, cnt);
            } else {
                cnt = 1;
            }
        }
        return ans;
    }
};
// @lc code=end

