/*
 * @lc app=leetcode id=2684 lang=cpp
 *
 * [2684] Maximum Number of Moves in a Grid
 *
 * https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/
 *
 * algorithms
 * Medium (58.83%)
 * Likes:    945
 * Dislikes: 28
 * Total Accepted:    130.9K
 * Total Submissions: 222.6K
 * Testcase Example:  '[[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]'
 *
 * You are given a 0-indexed m x n matrix grid consisting of positive
 * integers.
 * 
 * You can start at any cell in the first column of the matrix, and traverse
 * the grid in the following way:
 * 
 * 
 * From a cell (row, col), you can move to any of the cells: (row - 1, col +
 * 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell
 * you move to, should be strictly bigger than the value of the current cell.
 * 
 * 
 * Return the maximum number of moves that you can perform.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
 * Output: 3
 * Explanation: We can start at the cell (0, 0) and make the following moves:
 * - (0, 0) -> (0, 1).
 * - (0, 1) -> (1, 2).
 * - (1, 2) -> (2, 3).
 * It can be shown that it is the maximum number of moves that can be made.
 * 
 * Example 2:
 * 
 * 
 * 
 * Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
 * Output: 0
 * Explanation: Starting from any cell in the first column we cannot perform
 * any moves.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 2 <= m, n <= 1000
 * 4 <= m * n <= 10^5
 * 1 <= grid[i][j] <= 10^6
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
    int maxMoves1(vector<vector<int>>& grid) {
        // 纵向移动，默认值为0，大于当前值才可移动，移动一次+1
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        auto dfs = [&](this auto &&dfs, int r, int c,
                       int pre) -> int {
            if (r < 0 || r > n - 1 || c > m - 1 || pre >= grid[r][c]) {
                return 0;
            }
            int &ans = memo[r][c];
            if (ans != -1) {
                return ans;
            }
            return ans = max({dfs(r - 1, c + 1, grid[r][c]),
                              dfs(r, c + 1, grid[r][c]),
                              dfs(r + 1, c + 1, grid[r][c])}) +
                         1;
        };
        int ans = 0;
        for (int r = 0; r < n; r++) {
            ans = max(ans, dfs(r, 0, 0));
            if (ans == m) {
                return ans - 1;
            }
        }
        return ans - 1;
    }

    // DP递推
    int maxMoves(vector<vector<int>>& grid) {
        // 纵向移动，默认值为0，大于当前值才可移动，移动一次+1
        int n = grid.size(), m = grid[0].size();
        vector<bool> f1(n, true);
        int ans = 0;
        int dirs[3] = {-1, 0, 1};

        for (int c = 1; c < m; c++) {
            vector<bool> f0 = f1;
            fill(f1.begin(), f1.end(), false);
            bool flag = false;
            for (int r = 0; r < n; r++) {
                int cur = grid[r][c];
                
                for (int dr : dirs) {
                    int nr = r + dr;
                    if (nr >= 0 && nr < n && f0[nr] && grid[nr][c - 1] < cur) {
                        flag = true;
                        f1[r] = true;
                    }
                }
            }
            if (!flag) {
                return c - 1;
            }
        }
        return m - 1;
    }
};
// @lc code=end

