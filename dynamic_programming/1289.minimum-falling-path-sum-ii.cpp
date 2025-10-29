/*
 * @lc app=leetcode id=1289 lang=cpp
 *
 * [1289] Minimum Falling Path Sum II
 *
 * https://leetcode.com/problems/minimum-falling-path-sum-ii/description/
 *
 * algorithms
 * Hard (63.71%)
 * Likes:    2347
 * Dislikes: 123
 * Total Accepted:    159.5K
 * Total Submissions: 251.4K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given an n x n integer matrix grid, return the minimum sum of a falling path
 * with non-zero shifts.
 * 
 * A falling path with non-zero shifts is a choice of exactly one element from
 * each row of grid such that no two elements chosen in adjacent rows are in
 * the same column.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: 13
 * Explanation: 
 * The possible falling paths are:
 * [1,5,9], [1,5,7], [1,6,7], [1,6,8],
 * [2,4,8], [2,4,9], [2,6,7], [2,6,8],
 * [3,4,8], [3,4,9], [3,5,7], [3,5,9]
 * The falling path with the smallest sum is [1,5,7], so the answer is 13.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[7]]
 * Output: 7
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == grid.length == grid[i].length
 * 1 <= n <= 200
 * -99 <= grid[i][j] <= 99
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int minFallingPathSum1(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, INT_MAX));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (j < 0 || j >= n) {
                return INT_MAX;
            }
            if (i == m - 1) {
                return grid[i][j];
            }
            int &ans = memo[i][j];
            if (ans != INT_MAX) {
                return ans;
            }
            for (int k = 0; k < n; k++) {
                if (j == k) {
                    continue;
                }
                ans = min(ans, dfs(i + 1, k) + grid[i][j]);
            }
            return ans; 
        };

        int ans = INT_MAX;
        for (int j = 0; j < n; j++) {
            ans = min(ans, dfs(0, j));
        }
        return ans;
    }

    // DP递推
    int minFallingPathSum2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> f(m, vector<int>(n));
        for (int j = 0; j < n; j++) {
            f[m - 1][j] = grid[m - 1][j];
        }
        for (int i = m - 2; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                int mn = INT_MAX;
                for (int k = 0; k < n; k++) {
                    if (k == j) {
                        continue;
                    }
                    mn = min(mn, f[i + 1][k] + grid[i][j]);
                }
                f[i][j] = mn;
            }
        }
        return ranges::min(f[0]);
    }

    // DP递推+原地修改
    int minFallingPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = m - 2; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                int mn = INT_MAX;
                for (int k = 0; k < n; k++) {
                    if (k == j) {
                        continue;
                    }
                    mn = min(mn, grid[i + 1][k] + grid[i][j]);
                }
                grid[i][j] = mn;
            }
        }
        return ranges::min(grid[0]);
    }
};
// @lc code=end

