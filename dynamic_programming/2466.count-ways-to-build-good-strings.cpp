/*
 * @lc app=leetcode id=2466 lang=cpp
 *
 * [2466] Count Ways To Build Good Strings
 *
 * https://leetcode.com/problems/count-ways-to-build-good-strings/description/
 *
 * algorithms
 * Medium (59.20%)
 * Likes:    2202
 * Dislikes: 210
 * Total Accepted:    176K
 * Total Submissions: 297.9K
 * Testcase Example:  '3\n3\n1\n1'
 *
 * Given the integers zero, one, low, and high, we can construct a string by
 * starting with an empty string, and then at each step perform either of the
 * following:
 * 
 * 
 * Append the character '0' zero times.
 * Append the character '1' one times.
 * 
 * 
 * This can be performed any number of times.
 * 
 * A good string is a string constructed by the above process having a length
 * between low and high (inclusive).
 * 
 * Return the number of different good strings that can be constructed
 * satisfying these properties. Since the answer can be large, return it modulo
 * 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: low = 3, high = 3, zero = 1, one = 1
 * Output: 8
 * Explanation: 
 * One possible valid good string is "011". 
 * It can be constructed as follows: "" -> "0" -> "01" -> "011". 
 * All binary strings from "000" to "111" are good strings in this example.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: low = 2, high = 3, zero = 1, one = 2
 * Output: 5
 * Explanation: The good strings are "00", "11", "000", "110", and "011".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= low <= high <= 10^5
 * 1 <= zero, one <= low
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int countGoodStrings1(int low, int high, int zero, int one) {
        int MOD = 1e9 + 7;
        vector<long long> memo(high + 1, -1);

        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i == 0) {
                return 1;
            }
            long long &ans = memo[i];
            if (ans != -1) {
                return ans % MOD;
            }
            ans = 0;
            if (zero <= i) {
                ans += dfs(i - zero);
            }
            if (one <= i) {
                ans += dfs(i - one);
            }
            return ans % MOD;
        };
        int ans = 0;
        for (int i = low; i <= high; i++) {
            ans = (ans + dfs(i)) % MOD;
        }
        return ans;
    }

    int countGoodStrings(int low, int high, int zero, int one) {
        int MOD = 1e9 + 7;
        vector<long long> f(high + 1);
        f[0] = 1;
        int ans = 0;
        for (int i = 1; i <= high; i++) {
            f[i] = ((long long) (i >= zero ? f[i - zero] : 0) +
                    (i >= one ? f[i - one] : 0)) %
                   MOD;
            if (i >= low) {
                ans = (ans + f[i]) % MOD;
            }
        }
        return ans;
    }
};
// @lc code=end

