/*
 * @lc app=leetcode id=306 lang=cpp
 *
 * [306] Additive Number
 *
 * https://leetcode.com/problems/additive-number/description/
 *
 * algorithms
 * Medium (32.67%)
 * Likes:    1244
 * Dislikes: 821
 * Total Accepted:    109.6K
 * Total Submissions: 333K
 * Testcase Example:  '"112358"'
 *
 * An additive number is a string whose digits can form an additive sequence.
 * 
 * A valid additive sequence should contain at least three numbers. Except for
 * the first two numbers, each subsequent number in the sequence must be the
 * sum of the preceding two.
 * 
 * Given a string containing only digits, return true if it is an additive
 * number or false otherwise.
 * 
 * Note: Numbers in the additive sequence cannot have leading zeros, so
 * sequence 1, 2, 03 or 1, 02, 3 is invalid.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "112358"
 * Output: true
 * Explanation: 
 * The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
 * 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "199100199"
 * Output: true
 * Explanation: 
 * The additive sequence is: 1, 99, 100, 199. 
 * 1 + 99 = 100, 99 + 100 = 199
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= num.length <= 35
 * num consists only of digits.
 * 
 * 
 * 
 * Follow up: How would you handle overflow for very large input integers?
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.length();
        if (n < 3) {
            return false;
        }

        vector<long long> path;

        auto dfs = [&](auto &dfs, int pos) -> bool {
            if (pos == n) {
                return path.size() >= 3;
            }

            string cur;
            for (int i = pos; i < n; i++) {
                cur = num.substr(pos, i - pos + 1);
                int m = cur.size();
                if (m > 17 || m > 1 && cur[0] == '0') {
                    return false;
                }

                long long cur_ll = 0LL;
                for (char c : cur) {
                    cur_ll = cur_ll * 10 + (c - '0');
                }
                int k = path.size();
                if (k < 2 || path[k - 2] + path[k - 1] == cur_ll) {
                    path.push_back(cur_ll);
                    if (dfs(dfs, i + 1)) {
                        return true;
                    }
                    path.pop_back();
                }
            }
            return false;
        };
        return dfs(dfs, 0);
    }
};
// @lc code=end

