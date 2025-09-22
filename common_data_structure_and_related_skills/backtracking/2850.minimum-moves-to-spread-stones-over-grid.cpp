/*
 * @lc app=leetcode id=2850 lang=cpp
 *
 * [2850] Minimum Moves to Spread Stones Over Grid
 *
 * https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/description/
 *
 * algorithms
 * Medium (44.41%)
 * Likes:    544
 * Dislikes: 77
 * Total Accepted:    28K
 * Total Submissions: 62.8K
 * Testcase Example:  '[[1,1,0],[1,1,1],[1,2,1]]'
 *
 * You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing
 * the number of stones in each cell. The grid contains exactly 9 stones, and
 * there can be multiple stones in a single cell.
 * 
 * In one move, you can move a single stone from its current cell to any other
 * cell if the two cells share a side.
 * 
 * Return the minimum number of moves required to place one stone in each
 * cell.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
 * Output: 3
 * Explanation: One possible sequence of moves to place one stone in each cell
 * is: 
 * 1- Move one stone from cell (2,1) to cell (2,2).
 * 2- Move one stone from cell (2,2) to cell (1,2).
 * 3- Move one stone from cell (1,2) to cell (0,2).
 * In total, it takes 3 moves to place one stone in each cell of the grid.
 * It can be shown that 3 is the minimum number of moves required to place one
 * stone in each cell.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,3,0],[1,0,0],[1,0,3]]
 * Output: 4
 * Explanation: One possible sequence of moves to place one stone in each cell
 * is:
 * 1- Move one stone from cell (0,1) to cell (0,2).
 * 2- Move one stone from cell (0,1) to cell (1,1).
 * 3- Move one stone from cell (2,2) to cell (1,2).
 * 4- Move one stone from cell (2,2) to cell (2,1).
 * In total, it takes 4 moves to place one stone in each cell of the grid.
 * It can be shown that 4 is the minimum number of moves required to place one
 * stone in each cell.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * grid.length == grid[i].length == 3
 * 0 <= grid[i][j] <= 9
 * Sum of grid is equal to 9.
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        // 记录需要移入移出的位置
        vector<pair<int, int>> from, to;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j]) {
                    for (int k = 1; k < grid[i][j]; k++) {
                        from.push_back({i, j});
                    }
                } else {
                    to.push_back({i, j});
                }
            }
        }

        // 堆from全排列，计算最小的移入移出的曼哈顿距离
        int ans = INT_MAX, n = from.size();
        vector<int> path(n), on_path(n);
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                int total = 0;
                for (int j = 0; j < n; j++) {
                    total += abs(from[path[j]].first - to[j].first) +
                             abs(from[path[j]].second - to[j].second);
                }
                ans = min(ans, total);
            }

            for (int j = 0; j < n; j++) {
                if (!on_path[j]) {
                    path[i] = j;
                    on_path[j] = 1;
                    dfs(dfs, i + 1);
                    on_path[j] = 0;
                }
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

