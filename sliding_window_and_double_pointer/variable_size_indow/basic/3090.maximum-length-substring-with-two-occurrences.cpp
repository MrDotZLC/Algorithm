/*
 * @lc app=leetcode id=3090 lang=cpp
 *
 * [3090] Maximum Length Substring With Two Occurrences
 *
 * https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/description/
 *
 * algorithms
 * Easy (63.85%)
 * Likes:    221
 * Dislikes: 19
 * Total Accepted:    53.7K
 * Total Submissions: 84K
 * Testcase Example:  '"bcbbbcba"'
 *
 * Given a string s, return the maximum length of a substring such that it
 * contains at most two occurrences of each character.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "bcbbbcba"
 * 
 * Output: 4
 * 
 * Explanation:
 * The following substring has a length of 4 and contains at most two
 * occurrences of each character: "bcbbbcba".
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaaa"
 * 
 * Output: 2
 * 
 * Explanation:
 * The following substring has a length of 2 and contains at most two
 * occurrences of each character: "aaaa".
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= s.length <= 100
 * s consists only of lowercase English letters.
 * 
 * 
 */

#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumLengthSubstring(string s) {
        int res = 0, l = 0;
        unordered_map<char, int> freq(s.length());
        for (int i = 0; i < s.length(); i++) {
            ++freq[s[i]];
            while (freq[s[i]] > 2) {
                --freq[s[l++]];
            };
            res = max(res, i - l + 1);
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution sol;
    string s = "bcbbbcba";
    auto res = sol.maximumLengthSubstring(s);
    cout << res << endl;
}