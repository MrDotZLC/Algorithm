/*
 * @lc app=leetcode id=91 lang=cpp
 *
 * [91] Decode Ways
 *
 * https://leetcode.com/problems/decode-ways/description/
 *
 * algorithms
 * Medium (36.70%)
 * Likes:    12653
 * Dislikes: 4601
 * Total Accepted:    1.6M
 * Total Submissions: 4.2M
 * Testcase Example:  '"12"'
 *
 * You have intercepted a secret message encoded as a string of numbers. The
 * message is decoded via the following mapping:
 * 
 * "1" -> 'A'
 * "2" -> 'B'
 * ...
 * "25" -> 'Y'
 * "26" -> 'Z'
 * 
 * However, while decoding the message, you realize that there are many
 * different ways you can decode the message because some codes are contained
 * in other codes ("2" and "5" vs "25").
 * 
 * For example, "11106" can be decoded into:
 * 
 * 
 * "AAJF" with the grouping (1, 1, 10, 6)
 * "KJF" with the grouping (11, 10, 6)
 * The grouping (1, 11, 06) is invalid because "06" is not a valid code (only
 * "6" is valid).
 * 
 * 
 * Note: there may be strings that are impossible to decode.
 * 
 * Given a string s containing only digits, return the number of ways to decode
 * it. If the entire string cannot be decoded in any valid way, return 0.
 * 
 * The test cases are generated so that the answer fits in a 32-bit integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "12"
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * "12" could be decoded as "AB" (1 2) or "L" (12).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "226"
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "06"
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * "06" cannot be mapped to "F" because of the leading zero ("6" is different
 * from "06"). In this case, the string is not a valid encoding, so return
 * 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 100
 * s contains only digits and may contain leading zero(s).
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // 递归+记忆化
    int numDecodings1(string s) {
        int n = s.length();
        vector<int> memo(n, -1);
        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i <= 0) {
                return s[0] != '0';
            }
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            res = s[i] != '0' ? dfs(i - 1) : 0;
            if (s[i - 1] == '0' || s[i - 1] > '2' || (s[i - 1] == '2' && s[i] > '6')) {
                return res;
            }
            res += dfs(i - 2);
            return res;
        };
        return dfs(n - 1);
    }

    // DP递推
    int numDecodings(string s) {
        int n = s.length();
        int f0 = s[0] != '0', f1 = f0;
        for (int i = 1; i < n; i++) {
            int cnt = 0;
            if (s[i] != '0') {
                cnt += f1;
            }
            if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
                cnt += f0;
            }
            f0 = f1;
            f1 = cnt;
        }
        return f1;
    }
};
// @lc code=end

