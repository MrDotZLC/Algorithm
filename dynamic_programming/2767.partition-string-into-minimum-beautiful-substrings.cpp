/*
 * @lc app=leetcode id=2767 lang=cpp
 *
 * [2767] Partition String Into Minimum Beautiful Substrings
 *
 * https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/description/
 *
 * algorithms
 * Medium (52.90%)
 * Likes:    380
 * Dislikes: 19
 * Total Accepted:    21K
 * Total Submissions: 39.2K
 * Testcase Example:  '"1011"'
 *
 * Given a binary string s, partition the string into one or more substrings
 * such that each substring is beautiful.
 * 
 * A string is beautiful if:
 * 
 * 
 * It doesn't contain leading zeros.
 * It's the binary representation of a number that is a power of 5.
 * 
 * 
 * Return the minimum number of substrings in such partition. If it is
 * impossible to partition the string s into beautiful substrings, return -1.
 * 
 * A substring is a contiguous sequence of characters in a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "1011"
 * Output: 2
 * Explanation: We can paritition the given string into ["101", "1"].
 * - The string "101" does not contain leading zeros and is the binary
 * representation of integer 5^1 = 5.
 * - The string "1" does not contain leading zeros and is the binary
 * representation of integer 5^0 = 1.
 * It can be shown that 2 is the minimum number of beautiful substrings that s
 * can be partitioned into.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "111"
 * Output: 3
 * Explanation: We can paritition the given string into ["1", "1", "1"].
 * - The string "1" does not contain leading zeros and is the binary
 * representation of integer 5^0 = 1.
 * It can be shown that 3 is the minimum number of beautiful substrings that s
 * can be partitioned into.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "0"
 * Output: -1
 * Explanation: We can not partition the given string into beautiful
 * substrings.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 15
 * s[i] is either '0' or '1'.
 * 
 * 
 */
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <bitset>
using namespace std;
// @lc code=start
vector<string> pow5;
int init = []() {
    for (int i = 1; i <= (int)pow(2, 15); i *= 5) {
        string bin = bitset<32>(i).to_string();
        bin.erase(0, bin.find_first_not_of('0')); // 大于0不必判空
        pow5.push_back(bin);
    }
    return 0;
}();

class Solution {
public:
    int minimumBeautifulSubstrings1(string s) {
        int n = s.length();
        vector<int> memo(n, INT_MAX / 2);
        function<int(int)> dfs = [&](int i) -> int {
            if (i == n) {
                return 0;
            }
            if (s[i] == '0') {
                return INT_MAX / 2;
            }
            int &res = memo[i];
            if (res != INT_MAX / 2) {
                return res;
            }
            for (auto &t : pow5) {
                int len = t.length();
                if (i + len > n) {
                    break;
                }
                if (s.compare(i, len, t) == 0) {
                    res = min(res, dfs(i + len) + 1);
                }
            }
            return res;
        };

        int ans = dfs(0);
        return ans >= (INT_MAX / 2) ? -1 : ans;
    }

    int minimumBeautifulSubstrings(string s) {
        int n = s.length();
        vector<int> f(n + 1, INT_MAX / 2);
        f[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                continue;
            }
            for (auto &t : pow5) {
                int len = t.length();
                if (i + len > n) {
                    break;
                }
                if (s.compare(i, len, t) == 0) {
                    f[i] = min(f[i], f[i + len] + 1);
                }
            }
        }
        return f[0] >= (INT_MAX / 2) ? -1 : f[0];
    }
};
// @lc code=end

