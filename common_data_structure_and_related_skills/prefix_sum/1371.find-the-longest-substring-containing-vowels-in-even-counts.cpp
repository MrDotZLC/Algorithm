/*
 * @lc app=leetcode id=1371 lang=cpp
 *
 * [1371] Find the Longest Substring Containing Vowels in Even Counts
 *
 * https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/
 *
 * algorithms
 * Medium (75.73%)
 * Likes:    2528
 * Dislikes: 140
 * Total Accepted:    137.6K
 * Total Submissions: 181.7K
 * Testcase Example:  '"eleetminicoworoep"'
 *
 * Given the string s, return the size of the longest substring containing each
 * vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must
 * appear an even number of times.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "eleetminicoworoep"
 * Output: 13
 * Explanation: The longest substring is "leetminicowor" which contains two
 * each of the vowels: e, i and o and zero of the vowels: a and u.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "leetcodeisgreat"
 * Output: 5
 * Explanation: The longest substring is "leetc" which contains two e's.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "bcbcbc"
 * Output: 6
 * Explanation: In this case, the given string "bcbcbc" is the longest because
 * all vowels: a, e, i, o and u appear zero times.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 5 x 10^5
 * s contains only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int findTheLongestSubstring(string s) {
        const int MASK = (1 << 0) | (1 << 4) | (1 << 8) | (1 << 14) | (1 << 20);
        int ans = 0, n = s.length(), sum = 0;
        unordered_map<int, int> cnt;
        cnt[0] = -1;

        for (int i = 0; i < n; i++) {
            int bit = 1 << (s[i] -'a');
            if (bit & MASK) {
                sum ^= bit;
            }
            if (cnt.count(sum)) {
                ans = max(ans, i - cnt[sum]);
            } else {
                cnt[sum] = i;
            }
        }
        return ans;
    }
};
// @lc code=end

