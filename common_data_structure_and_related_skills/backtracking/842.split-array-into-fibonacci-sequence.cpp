/*
 * @lc app=leetcode id=842 lang=cpp
 *
 * [842] Split Array into Fibonacci Sequence
 *
 * https://leetcode.com/problems/split-array-into-fibonacci-sequence/description/
 *
 * algorithms
 * Medium (39.71%)
 * Likes:    1171
 * Dislikes: 308
 * Total Accepted:    44.9K
 * Total Submissions: 112.5K
 * Testcase Example:  '"1101111"'
 *
 * You are given a string of digits num, such as "123456579". We can split it
 * into a Fibonacci-like sequence [123, 456, 579].
 * 
 * Formally, a Fibonacci-like sequence is a list f of non-negative integers
 * such that:
 * 
 * 
 * 0 <= f[i] < 2^31, (that is, each integer fits in a 32-bit signed integer
 * type),
 * f.length >= 3, and
 * f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
 * 
 * 
 * Note that when splitting the string into pieces, each piece must not have
 * extra leading zeroes, except if the piece is the number 0 itself.
 * 
 * Return any Fibonacci-like sequence split from num, or return [] if it cannot
 * be done.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: num = "1101111"
 * Output: [11,0,11,11]
 * Explanation: The output [110, 1, 111] would also be accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: num = "112358130"
 * Output: []
 * Explanation: The task is impossible.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: num = "0123"
 * Output: []
 * Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not
 * valid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= num.length <= 200
 * num contains only digits.
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        int n = num.length();
        if (n < 3) {
            return {};
        }

        vector<int> ans;
        auto dfs = [&](auto &dfs, int pos) -> bool {
            if (pos == n) {
                return ans.size() >= 3;
            }

            long long cur = 0LL;
            for (int j = pos; j < n; j++) {
                if (j > pos && num[pos] == '0') {
                    break;
                }
                cur = cur * 10 + num[j] - '0';
                if (cur > INT_MAX) {
                    break;
                }
                int m = ans.size();
                if (m >= 2) {
                    if (cur < (long long)ans[m - 1] + ans[m - 2]) {
                        continue;
                    } else if (cur > (long long)ans[m - 1] + ans[m - 2]) {
                        break;
                    }
                }

                ans.push_back(cur);
                if(dfs(dfs, j + 1)) {
                    return true;
                }
                ans.pop_back();
            }
            return false;   
        };
        if (!dfs(dfs, 0)) {
            ans = {};
        }
        return ans;
    }
};
// @lc code=end

