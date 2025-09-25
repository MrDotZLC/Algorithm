/*
 * @lc app=leetcode id=880 lang=cpp
 *
 * [880] Decoded String at Index
 *
 * https://leetcode.com/problems/decoded-string-at-index/description/
 *
 * algorithms
 * Medium (36.68%)
 * Likes:    2587
 * Dislikes: 364
 * Total Accepted:    104.1K
 * Total Submissions: 282.9K
 * Testcase Example:  '"leet2code3"\n10'
 *
 * You are given an encoded string s. To decode the string to a tape, the
 * encoded string is read one character at a time and the following steps are
 * taken:
 * 
 * 
 * If the character read is a letter, that letter is written onto the tape.
 * If the character read is a digit d, the entire current tape is repeatedly
 * written d - 1 more times in total.
 * 
 * 
 * Given an integer k, return the k^th letter (1-indexed) in the decoded
 * string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leet2code3", k = 10
 * Output: "o"
 * Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
 * The 10^th letter in the string is "o".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "ha22", k = 5
 * Output: "h"
 * Explanation: The decoded string is "hahahaha".
 * The 5^th letter is "h".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "a2345678999999999999999", k = 1
 * Output: "a"
 * Explanation: The decoded string is "a" repeated 8301530446056247680 times.
 * The 1^st letter is "a".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= s.length <= 100
 * s consists of lowercase English letters and digits 2 through 9.
 * s starts with a letter.
 * 1 <= k <= 10^9
 * It is guaranteed that k is less than or equal to the length of the decoded
 * string.
 * The decoded string is guaranteed to have less than 2^63 letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 逆向工程
    string decodeAtIndex1(string s, int k) {
        long len = 0;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            if (s[i] < 'a') {
                len *= s[i] - '0';
            } else {
                len++;
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            k %= len;

            if (s[i] >= 'a') {
                if (k == 0) {
                    return string(1, s[i]);
                }
                len--;
            } else {
                len /= s[i] - '0';
            }
        }
        return "";
    }

    //递归
    string decodeAtIndex(string s, int k) {
        int n = s.length();
        long len = 0L;
        
        for (int i = 0; i < n; i++) {
            if (s[i] >= 'a') {
                if (++len == k) {
                    return string(1, s[i]);
                }
            } else {
                long long total = len * (s[i] - '0');

                if (total >= k) {
                    // k 在重复展开的某一段里面，k % len在处理“k是len的n倍时”映射为0，实际应是len
                    // 将[1, n]映射到[0, n-1]，再加1
                    return decodeAtIndex(s.substr(0, i), (k - 1) % len + 1);
                }
                len = total; // 更新总长度
            }
        }
        return "";
    }
};
// @lc code=end

