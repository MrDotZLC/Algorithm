/*
 * @lc app=leetcode id=467 lang=cpp
 *
 * [467] Unique Substrings in Wraparound String
 *
 * https://leetcode.com/problems/unique-substrings-in-wraparound-string/description/
 *
 * algorithms
 * Medium (41.37%)
 * Likes:    1517
 * Dislikes: 187
 * Total Accepted:    53.6K
 * Total Submissions: 127.5K
 * Testcase Example:  '"a"'
 *
 * We define the string base to be the infinite wraparound string of
 * "abcdefghijklmnopqrstuvwxyz", so base will look like this:
 * 
 * 
 * "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
 * 
 * 
 * Given a string s, return the number of unique non-empty substrings of s are
 * present in base.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "a"
 * Output: 1
 * Explanation: Only the substring "a" of s is in base.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "cac"
 * Output: 2
 * Explanation: There are two substrings ("a", "c") of s in base.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "zab"
 * Output: 6
 * Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab")
 * of s in base.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int findSubstringInWraproundString(string s) {
        vector<int> mx(26);
        mx[s[0] - 'a']++;
        for (int i = 1, sum = 1; i < s.length(); i++) {
            char c = s[i] - 'a', prev = s[i - 1] - 'a';
            if (c == prev + 1 || c == prev - 25) {
                sum++;
            } else {
                sum = 1;
            }
            mx[c] = max(mx[c], sum);
        }
        return reduce(mx.begin(), mx.end(), 0);
    }
};
// @lc code=end

