/*
 * @lc app=leetcode id=1888 lang=cpp
 *
 * [1888] Minimum Number of Flips to Make the Binary String Alternating
 *
 * https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/description/
 *
 * algorithms
 * Medium (40.58%)
 * Likes:    1270
 * Dislikes: 81
 * Total Accepted:    33.9K
 * Total Submissions: 83.4K
 * Testcase Example:  '"111000"'
 *
 * You are given a binary string s. You are allowed to perform two types of
 * operations on the string in any sequence:
 * 
 * 
 * Type-1: Remove the character at the start of the string s and append it to
 * the end of the string.
 * Type-2: Pick any character in s and flip its value, i.e., if its value is
 * '0' it becomes '1' and vice-versa.
 * 
 * 
 * Return the minimum number of type-2 operations you need to perform such that
 * s becomes alternating.
 * 
 * The string is called alternating if no two adjacent characters are
 * equal.
 * 
 * 
 * For example, the strings "010" and "1010" are alternating, while the string
 * "0100" is not.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "111000"
 * Output: 2
 * Explanation: Use the first operation two times to make s = "100011".
 * Then, use the second operation on the third and sixth elements to make s =
 * "101010".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "010"
 * Output: 0
 * Explanation: The string is already alternating.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "1110"
 * Output: 1
 * Explanation: Use the second operation on the second element to make s =
 * "1010".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s[i] is either '0' or '1'.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // Prefix and suffix matching
    int minFlips(string s) {
        int res = INT_MAX;
        int n = s.length();
        vector<vector<int>> pre(n ,vector<int>(2));

        auto match = [&](char c, int x) -> int {
            return c - '0' == x;
        };

        // prefix ~ [0, i - 1] + 0/1
        for (int i = 0; i < n; i++) {
            pre[i][0] = (i == 0 ? 0 : pre[i - 1][1]) + match(s[i], 1);
            pre[i][1] = (i == 0 ? 0 : pre[i - 1][0]) + match(s[i], 0);
        }

        res = min(pre[n - 1][0], pre[n - 1][1]);

        // n == odd, suffix ~ 0/1 + [i + 1, n - 1]
        if (n % 2 == 1) {
            vector<vector<int>> suf(n ,vector<int>(2));
            for (int i = n - 1; i >= 0; i--) {
                suf[i][0] = (i == n - 1 ? 0 : suf[i + 1][1]) + match(s[i], 1);
                suf[i][1] = (i == n - 1 ? 0 : suf[i + 1][0]) + match(s[i], 0);
            }

            for (int i = 0; i + 1 < n; i++) {
                res = min(res, pre[i][0] + suf[i + 1][0]);
                res = min(res, pre[i][1] + suf[i + 1][1]);
            }
        }

        return res;
    }

    // sliding window: 
    // calculate the number of operations for all substrings
    int minFlips2(string s) {
        int n = s.length();
        int res = 0, cnt = 0;
        for (int i = 0; i < 2 * n - 1; i++) {
            if (s[i % n] % 2 != i % 2) {
                cnt++;
            }
            int left = i - n + 1;
            if (left < 0) {
                continue;
            }
            res = min({res, cnt, n - cnt});
            if (s[left % n] % 2 != left % 2) {
                cnt--;
            }
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution sol;

    auto res = sol.minFlips("111000");
    cout << res << endl;
}