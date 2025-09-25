/*
 * @lc app=leetcode id=967 lang=cpp
 *
 * [967] Numbers With Same Consecutive Differences
 *
 * https://leetcode.com/problems/numbers-with-same-consecutive-differences/description/
 *
 * algorithms
 * Medium (58.77%)
 * Likes:    2866
 * Dislikes: 200
 * Total Accepted:    150.2K
 * Total Submissions: 254.9K
 * Testcase Example:  '3\n7'
 *
 * Given two integers n and k, return an array of all the integers of length n
 * where the difference between every two consecutive digits is k. You may
 * return the answer in any order.
 * 
 * Note that the integers should not have leading zeros. Integers as 02 and 043
 * are not allowed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, k = 7
 * Output: [181,292,707,818,929]
 * Explanation: Note that 070 is not a valid number, because it has leading
 * zeroes.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, k = 1
 * Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 9
 * 0 <= k <= 9
 * 
 * 
 */
#include <vector>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> ans;
        int path = 0;
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }
            for (int j = 0; j < 10; j++) {
                if (i == 0 && j == 0 || i != 0 && abs(path % 10 - j) != k) {
                    continue;
                }
                path = path * 10 + j;
                dfs(dfs, i + 1);
                path = path / 10;
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

