/*
 * @lc app=leetcode id=1297 lang=cpp
 *
 * [1297] Maximum Number of Occurrences of a Substring
 *
 * https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/description/
 *
 * algorithms
 * Medium (53.53%)
 * Likes:    1177
 * Dislikes: 420
 * Total Accepted:    72.9K
 * Total Submissions: 136.1K
 * Testcase Example:  '"aababcaab"\n2\n3\n4'
 *
 * Given a string s, return the maximum number of occurrences of any substring
 * under the following rules:
 * 
 * 
 * The number of unique characters in the substring must be less than or equal
 * to maxLetters.
 * The substring size must be between minSize and maxSize inclusive.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
 * Output: 2
 * Explanation: Substring "aab" has 2 occurrences in the original string.
 * It satisfies the conditions, 2 unique letters and size 3 (between minSize
 * and maxSize).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
 * Output: 2
 * Explanation: Substring "aaa" occur 2 times in the string. It can
 * overlap.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * 1 <= maxLetters <= 26
 * 1 <= minSize <= maxSize <= min(26, s.length)
 * s consists of only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int res = 0;
        unordered_map<char, int> freq_l;
        unordered_map<string, int> freq_s;
        string ss;
        for (int i = 0; i < s.length(); i++) {
            ss += s[i];
            freq_l[s[i]]++;
            if (i < minSize - 1) {
                continue;
            }
            if (freq_l.size() <= maxLetters) {
                res = max(res, ++freq_s[ss]);
            }
            if (--freq_l[ss[0]] == 0) {
                freq_l.erase(ss[0]);
            }
            ss.erase(0, 1);
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution sol;

    auto res = sol.maxFreq("bbacbadadc", 2, 1, 1);

    cout << res << endl;
}