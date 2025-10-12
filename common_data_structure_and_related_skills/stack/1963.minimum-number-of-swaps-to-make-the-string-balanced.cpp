/*
 * @lc app=leetcode id=1963 lang=cpp
 *
 * [1963] Minimum Number of Swaps to Make the String Balanced
 *
 * https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/
 *
 * algorithms
 * Medium (78.01%)
 * Likes:    2532
 * Dislikes: 149
 * Total Accepted:    235.6K
 * Total Submissions: 301.9K
 * Testcase Example:  '"][]["'
 *
 * You are given a 0-indexed string s of even length n. The string consists of
 * exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.
 * 
 * A string is called balanced if and only if:
 * 
 * 
 * It is the empty string, or
 * It can be written as AB, where both A and B are balanced strings, or
 * It can be written as [C], where C is a balanced string.
 * 
 * 
 * You may swap the brackets at any two indices any number of times.
 * 
 * Return the minimum number of swaps to make s balanced.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "][]["
 * Output: 1
 * Explanation: You can make the string balanced by swapping index 0 with index
 * 3.
 * The resulting string is "[[]]".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "]]][[["
 * Output: 2
 * Explanation: You can do the following to make the string balanced:
 * - Swap index 0 with index 4. s = "[]][][".
 * - Swap index 1 with index 5. s = "[[][]]".
 * The resulting string is "[[][]]".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "[]"
 * Output: 0
 * Explanation: The string is already balanced.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == s.length
 * 2 <= n <= 10^6
 * n is even.
 * s[i] is either '[' or ']'.
 * The number of opening brackets '[' equals n / 2, and the number of closing
 * brackets ']' equals n / 2.
 * 
 * 
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int minSwaps(string s) {
        int cnt = 0;
        for (char c : s) {
            if (c == '[') {
                cnt++;
            } else if (cnt) {
                cnt--;
            }
        }
        return (cnt + 1) / 2;
    }

    // cnt == 0 && c == ']'时，
    // 相当于把']'强制替换成'['，
    // 与之对应的'['则继续累加到cnt，结果等于cnt/2.
    // 例如 ]]][[[ 视为 [][[[[，遍历结束后cnt=4
    int minSwaps1(string s) { 
        int cnt = 0;
        for (char c : s) {
            if (c == '[' || cnt == 0) {
                cnt++;
            } else {
                cnt--;
            }
        }
        return cnt / 2;
    }
};
// @lc code=end

