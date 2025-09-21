/*
 * @lc app=leetcode id=93 lang=cpp
 *
 * [93] Restore IP Addresses
 *
 * https://leetcode.com/problems/restore-ip-addresses/description/
 *
 * algorithms
 * Medium (53.45%)
 * Likes:    5521
 * Dislikes: 813
 * Total Accepted:    567.8K
 * Total Submissions: 1.1M
 * Testcase Example:  '"25525511135"'
 *
 * A valid IP address consists of exactly four integers separated by single
 * dots. Each integer is between 0 and 255 (inclusive) and cannot have leading
 * zeros.
 * 
 * 
 * For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but
 * "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP
 * addresses.
 * 
 * 
 * Given a string s containing only digits, return all possible valid IP
 * addresses that can be formed by inserting dots into s. You are not allowed
 * to reorder or remove any digits in s. You may return the valid IP addresses
 * in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "25525511135"
 * Output: ["255.255.11.135","255.255.111.35"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "0000"
 * Output: ["0.0.0.0"]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "101023"
 * Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 20
 * s consists of digits only.
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.length();
        if (n < 4) {
            return {};
        }
        vector<string> ans;
        vector<int> path;
        auto dfs = [&](auto &dfs, int pos) -> void {
            if (pos == n) {
                if (path.size() == 4) {
                    string res = "";
                    for (int i : path) {
                        res += to_string(i) + ".";
                    }
                    res.pop_back();
                    ans.push_back(res);
                }
                return;
            }

            if (path.size() > 4) {
                return;
            }

            long long cur = 0;
            for (int i = pos; i < n; i++) {
                cur = cur * 10 + s[i] - '0';

                if (cur > 255 || (i > pos && s[pos] == '0')) {
                    break;
                }
                path.push_back(cur);
                dfs(dfs, i + 1);
                path.pop_back();
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

