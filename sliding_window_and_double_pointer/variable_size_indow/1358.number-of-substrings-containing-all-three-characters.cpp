/*
 * @lc app=leetcode id=1358 lang=cpp
 *
 * [1358] Number of Substrings Containing All Three Characters
 *
 * https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
 *
 * algorithms
 * Medium (73.25%)
 * Likes:    4158
 * Dislikes: 74
 * Total Accepted:    358.1K
 * Total Submissions: 488.8K
 * Testcase Example:  '"abcabc"'
 *
 * Given a string s consisting only of characters a, b and c.
 * 
 * Return the number of substrings containing at least one occurrence of all
 * these characters a, b and c.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcabc"
 * Output: 10
 * Explanation: The substrings containing at least one occurrence of the
 * characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab",
 * "bcabc", "cab", "cabc" and "abc" (again). 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaacb"
 * Output: 3
 * Explanation: The substrings containing at least one occurrence of the
 * characters a, b and c are "aaacb", "aacb" and "acb". 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abc"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 5 x 10^4
 * s only consists of a, b or c characters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int numberOfSubstrings(string s) {
        int ans = 0, l = 0, n = s.length();
        unordered_map<char, int> freq;
        int empty = 3;
        for (int r = 0; r < n; r++) {
            if (++freq[s[r]] == 1) {
                --empty;
            }
            while (empty == 0) {
                if (--freq[s[l++]] == 0) {
                    ++empty;
                }
            }
            ans += l;
        }
        return ans;
    }
};
// @lc code=end

