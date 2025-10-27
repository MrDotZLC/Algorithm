/*
 * @lc app=leetcode id=1915 lang=cpp
 *
 * [1915] Number of Wonderful Substrings
 *
 * https://leetcode.com/problems/number-of-wonderful-substrings/description/
 *
 * algorithms
 * Medium (66.67%)
 * Likes:    1802
 * Dislikes: 283
 * Total Accepted:    88K
 * Total Submissions: 132K
 * Testcase Example:  '"aba"'
 *
 * A wonderful string is a string where at most one letter appears an odd
 * number of times.
 * 
 * 
 * For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
 * 
 * 
 * Given a string word that consists of the first ten lowercase English letters
 * ('a' through 'j'), return the number of wonderful non-empty substrings in
 * word. If the same substring appears multiple times in word, then count each
 * occurrence separately.
 * 
 * A substring is a contiguous sequence of characters in a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: word = "aba"
 * Output: 4
 * Explanation: The four wonderful substrings are underlined below:
 * - "aba" -> "a"
 * - "aba" -> "b"
 * - "aba" -> "a"
 * - "aba" -> "aba"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: word = "aabb"
 * Output: 9
 * Explanation: The nine wonderful substrings are underlined below:
 * - "aabb" -> "a"
 * - "aabb" -> "aa"
 * - "aabb" -> "aab"
 * - "aabb" -> "aabb"
 * - "aabb" -> "a"
 * - "aabb" -> "abb"
 * - "aabb" -> "b"
 * - "aabb" -> "bb"
 * - "aabb" -> "b"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: word = "he"
 * Output: 2
 * Explanation: The two wonderful substrings are underlined below:
 * - "he" -> "h"
 * - "he" -> "e"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= word.length <= 10^5
 * word consists of lowercase English letters from 'a' to 'j'.
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    long long wonderfulSubstrings(string word) {
        long long ans = 0;
        int n = word.length(), sum = 0;
        vector<int> cnt(1024, 0);
        cnt[0] = 1;
        for (int i = 0; i < n; i++) {
            int bit = 1 << (word[i] - 'a');
            sum ^= bit;
            ans += cnt[sum];
            for (int j = 1; j < 1024; j <<= 1) {
                ans += cnt[sum ^ j];
            }
            cnt[sum]++;
        }
        return ans;
    }
};
// @lc code=end

