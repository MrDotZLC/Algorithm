/*
 * @lc app=leetcode id=64 lang=cpp
 *
 * [64] Minimum Path Sum
 *
 * https://leetcode.com/problems/minimum-path-sum/description/
 *
 * algorithms
 * Medium (66.73%)
 * Likes:    13384
 * Dislikes: 189
 * Total Accepted:    1.7M
 * Total Submissions: 2.5M
 * Testcase Example:  '[[1,3,1],[1,5,1],[4,2,1]]'
 *
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right, which minimizes the sum of all numbers along its
 * path.
 * 
 * Note: You can only move either down or right at any point in time.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
 * Output: 7
 * Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,2,3],[4,5,6]]
 * Output: 12
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 200
 * 0 <= grid[i][j] <= 200
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归 ETL
    int minPathSum1(vector<vector<int>>& grid) {
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return INT_MAX;
            }
            if (i == 0 && j == 0) {
                return grid[0][0];
            }
            return min(dfs(i - 1, j), dfs(i, j - 1)) + grid[i][j];
        };
        return dfs(grid.size() - 1, grid[0].size() - 1);
    }

    // DP递归+记忆化搜索
    int minPathSum2(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return INT_MAX;
            }
            if (i == 0 && j == 0) {
                return grid[0][0];
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            return ans = min(dfs(i - 1, j), dfs(i, j - 1)) + grid[i][j];
        };
        return dfs(grid.size() - 1, grid[0].size() - 1);
    }

    // DP递推
    int minPathSum3(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, INT_MAX));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    f[1][1] = grid[i][j];
                } else {
                    f[i + 1][j + 1] = min(f[i][j + 1], f[i + 1][j]) + grid[i][j];
                }
            }
        }
        return f[n][m];
    }

    // DP递推 + 空间优化(一维状态矩阵)
    int minPathSum4(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> f(m + 1, INT_MAX);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    f[1] = grid[i][j];
                } else {
                    f[j + 1] = min(f[j], f[j + 1]) + grid[i][j];
                }
            }
        }
        return f[m];
    }

    // DP递推 + 空间优化(原地修改)
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        auto &f = grid[0];
        for (int j = 1; j < m; j++) {
            f[j] += f[j - 1];
        }
        for (int i = 1; i < n; i++) {
            f[0] += grid[i][0];
            for (int j = 1; j < m; j++) {
                f[j] = min(f[j - 1], f[j]) + grid[i][j];
            }
        }
        return f[m - 1];
    }
};
// @lc code=end

