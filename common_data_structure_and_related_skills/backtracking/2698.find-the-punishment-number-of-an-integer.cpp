/*
 * @lc app=leetcode id=2698 lang=cpp
 *
 * [2698] Find the Punishment Number of an Integer
 *
 * https://leetcode.com/problems/find-the-punishment-number-of-an-integer/description/
 *
 * algorithms
 * Medium (81.82%)
 * Likes:    1168
 * Dislikes: 244
 * Total Accepted:    148.4K
 * Total Submissions: 181.4K
 * Testcase Example:  '10'
 *
 * Given a positive integer n, return the punishment number of n.
 * 
 * The punishment number of n is defined as the sum of the squares of all
 * integers i such that:
 * 
 * 
 * 1 <= i <= n
 * The decimal representation of i * i can be partitioned into contiguous
 * substrings such that the sum of the integer values of these substrings
 * equals i.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 10
 * Output: 182
 * Explanation: There are exactly 3 integers i in the range [1, 10] that
 * satisfy the conditions in the statement:
 * - 1 since 1 * 1 = 1
 * - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal
 * to 8 + 1 == 9.
 * - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum
 * equal to 10 + 0 == 10.
 * Hence, the punishment number of 10 is 1 + 81 + 100 = 182
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 37
 * Output: 1478
 * Explanation: There are exactly 4 integers i in the range [1, 37] that
 * satisfy the conditions in the statement:
 * - 1 since 1 * 1 = 1. 
 * - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 + 1. 
 * - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 + 0. 
 * - 36 since 36 * 36 = 1296 and 1296 can be partitioned into 1 + 29 + 6.
 * Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 1000
 * 
 * 
 */
#include <string>
#include <cmath>
using namespace std;
// @lc code=start
int PRE_SUM[1001];

int init = []() {
    for (int i = 1; i <= 1000; i++) {
        string s = to_string(i * i);
        int n = s.length();
        auto dfs = [&](auto &dfs, int l, int r, int x, int sum) -> bool {
            if (r == n) {
                return sum == i;
            }

            if (sum > i) {
                return false;
            }

            x = x * 10 + s[r] - '0';

            if (r < n - 1) {
                if (dfs(dfs, l, r + 1, x, sum)) {
                    return true;
                }
            }
            
            if (dfs(dfs, r + 1, r + 1, 0, sum + x)) {
                return true;
            }
            return false;
        };
        PRE_SUM[i] = PRE_SUM[i - 1] + (dfs(dfs, 0, 0, 0, 0) ? i * i : 0);
    }
    return 0;
}();

class Solution {
public:
    int punishmentNumber(int n) {
        return PRE_SUM[n];
    }
};
// @lc code=end

