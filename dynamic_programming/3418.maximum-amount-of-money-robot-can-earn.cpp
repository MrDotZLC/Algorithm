/*
 * @lc app=leetcode id=3418 lang=cpp
 *
 * [3418] Maximum Amount of Money Robot Can Earn
 *
 * https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/description/
 *
 * algorithms
 * Medium (28.81%)
 * Likes:    128
 * Dislikes: 12
 * Total Accepted:    22.5K
 * Total Submissions: 77.3K
 * Testcase Example:  '[[0,1,-1],[1,-2,3],[2,-3,4]]'
 *
 * You are given an m x n grid. A robot starts at the top-left corner of the
 * grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1). The
 * robot can move either right or down at any point in time.
 * 
 * The grid contains a value coins[i][j] in each cell:
 * 
 * 
 * If coins[i][j] >= 0, the robot gains that many coins.
 * If coins[i][j] < 0, the robot encounters a robber, and the robber steals the
 * absolute value of coins[i][j] coins.
 * 
 * 
 * The robot has a special ability to neutralize robbers in at most 2 cells on
 * its path, preventing them from stealing coins in those cells.
 * 
 * Note: The robot's total coins can be negative.
 * 
 * Return the maximum profit the robot can gain on the route.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]
 * 
 * Output: 8
 * 
 * Explanation:
 * 
 * An optimal path for maximum coins is:
 * 
 * 
 * Start at (0, 0) with 0 coins (total coins = 0).
 * Move to (0, 1), gaining 1 coin (total coins = 0 + 1 = 1).
 * Move to (1, 1), where there's a robber stealing 2 coins. The robot uses one
 * neutralization here, avoiding the robbery (total coins = 1).
 * Move to (1, 2), gaining 3 coins (total coins = 1 + 3 = 4).
 * Move to (2, 2), gaining 4 coins (total coins = 4 + 4 = 8).
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: coins = [[10,10,10],[10,10,10]]
 * 
 * Output: 40
 * 
 * Explanation:
 * 
 * An optimal path for maximum coins is:
 * 
 * 
 * Start at (0, 0) with 10 coins (total coins = 10).
 * Move to (0, 1), gaining 10 coins (total coins = 10 + 10 = 20).
 * Move to (0, 2), gaining another 10 coins (total coins = 20 + 10 = 30).
 * Move to (1, 2), gaining the final 10 coins (total coins = 30 + 10 =
 * 40).
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == coins.length
 * n == coins[i].length
 * 1 <= m, n <= 500
 * -1000 <= coins[i][j] <= 1000
 * 
 * 
 */
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int maximumAmount1(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        vector memo(m, vector(n, array<int, 3>{INT_MIN, INT_MIN, INT_MIN}));
        auto dfs = [&](this auto &&dfs, int i, int j, int k) -> int {
            if (i < 0 || j < 0) {
                return INT_MIN;
            }
            int x = coins[i][j];
            if (i == 0 && j == 0) {
                return memo[i][j][k] == k ? max(x, 0) : x;
            }
            int &ans = memo[i][j][k];
            if (ans != INT_MIN) {
                return ans;
            }
            ans = max(dfs(i - 1, j, k), dfs(i, j - 1, k)) + x; // 选
            if (k && x < 0) { // 不选
                ans = max({ans, dfs(i - 1, j, k - 1), dfs(i, j - 1, k - 1)});
            }
            return ans;
        };
        return dfs(m - 1, n - 1, 2);
    }

    // DP递推
    int maximumAmount2(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        vector f(m + 1,
                 vector(n + 1, array<int, 3>{INT_MIN / 2, INT_MIN / 2,
                                             INT_MIN / 2}));
        f[0][1] = {0, 0, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int x = coins[i][j];
                f[i + 1][j + 1][0] =
                    max(f[i + 1][j][0], f[i][j + 1][0]) + x;
                f[i + 1][j + 1][1] =
                    max({f[i + 1][j][1] + x, f[i][j + 1][1] + x,
                         f[i + 1][j][0], f[i][j + 1][0]});
                f[i + 1][j + 1][2] = max({f[i + 1][j][2] + x, f[i][j + 1][2] + x,
                         f[i + 1][j][1], f[i][j + 1][1]});
            }
        }
        return f[m][n][2];
    }

    // DP递推+空间优化
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        vector f(n + 1, array<int, 3>{INT_MIN / 2, INT_MIN / 2,
                                      INT_MIN / 2});
        f[1] = {0, 0, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int x = coins[i][j];
                f[j + 1][2] = max({f[j][2] + x, f[j + 1][2] + x,
                                   f[j][1], f[j + 1][1]});
                f[j + 1][1] = max({f[j][1] + x, f[j + 1][1] + x,
                                   f[j][0], f[j + 1][0]});
                f[j + 1][0] = max(f[j][0], f[j + 1][0]) + x;
            }
        }
        return f[n][2];
    }
};
// @lc code=end

