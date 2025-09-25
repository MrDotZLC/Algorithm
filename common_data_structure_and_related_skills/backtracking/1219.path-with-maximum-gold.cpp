/*
 * @lc app=leetcode id=1219 lang=cpp
 *
 * [1219] Path with Maximum Gold
 *
 * https://leetcode.com/problems/path-with-maximum-gold/description/
 *
 * algorithms
 * Medium (68.16%)
 * Likes:    3403
 * Dislikes: 104
 * Total Accepted:    243.8K
 * Total Submissions: 357.6K
 * Testcase Example:  '[[0,6,0],[5,8,7],[0,9,0]]'
 *
 * In a gold mine grid of size m x n, each cell in this mine has an integer
 * representing the amount of gold in that cell, 0 if it is empty.
 * 
 * Return the maximum amount of gold you can collect under the
 * conditions:
 * 
 * 
 * Every time you are located in a cell you will collect all the gold in that
 * cell.
 * From your position, you can walk one step to the left, right, up, or
 * down.
 * You can't visit the same cell more than once.
 * Never visit a cell with 0 gold.
 * You can start and stop collecting gold from any position in the grid that
 * has some gold.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
 * Output: 24
 * Explanation:
 * [[0,6,0],
 * ⁠[5,8,7],
 * ⁠[0,9,0]]
 * Path to get the maximum gold, 9 -> 8 -> 7.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
 * Output: 28
 * Explanation:
 * [[1,0,7],
 * ⁠[2,0,6],
 * ⁠[3,4,5],
 * ⁠[0,3,0],
 * ⁠[9,0,20]]
 * Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 15
 * 0 <= grid[i][j] <= 100
 * There are at most 25 cells containing gold.
 * 
 * 
 */
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int getMaximumGold(vector<vector<int>> &grid) {
        vector<tuple<int, int, int>> golds;
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c]) {
                    golds.emplace_back(grid[r][c], r, c);
                }
            }
        }
        int ans = 0, n = golds.size();
        vector<int> vis(n);
        auto dfs = [&](auto &dfs, int sum, int pre_j) -> void {
            ans = max(ans, sum);
            for (int j = 0; j < n; j++) {
                if (vis[j] || 
                    pre_j >= 0 &&
                        abs(get<1>(golds[pre_j]) - get<1>(golds[j])) +
                                abs(get<2>(golds[pre_j]) -
                                    get<2>(golds[j])) !=
                            1) {
                    continue;
                }
                vis[j] = 1;
                dfs(dfs, sum + get<0>(golds[j]), j);
                vis[j] = 0;
            }
        };
        dfs(dfs, 0, -1);
        return ans;
    }

    int getMaximumGold1(vector<vector<int>>& grid) {
        int ans = 0, m = grid.size(), n = grid[0].size();

        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1},};

        auto dfs = [&](auto &dfs, int r, int c) -> int {
            if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
                return 0;
            }

            int gold = grid[r][c];
            grid[r][c] = 0;
            int mx = 0;
            for (auto &[dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                mx = max(mx, dfs(dfs, nr, nc));
            }
            grid[r][c] = gold;

            return mx + gold;

        };
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c]) {
                    ans = max(ans, dfs(dfs, r, c));
                }
            }
        }
        return ans;
    }
};
// @lc code=end

