/*
 * @lc app=leetcode id=980 lang=cpp
 *
 * [980] Unique Paths III
 *
 * https://leetcode.com/problems/unique-paths-iii/description/
 *
 * algorithms
 * Hard (82.40%)
 * Likes:    5405
 * Dislikes: 196
 * Total Accepted:    241.7K
 * Total Submissions: 292.9K
 * Testcase Example:  '[[1,0,0,0],[0,0,0,0],[0,0,2,-1]]'
 *
 * You are given an m x n integer array grid where grid[i][j] could be:
 * 
 * 
 * 1 representing the starting square. There is exactly one starting
 * square.
 * 2 representing the ending square. There is exactly one ending square.
 * 0 representing empty squares we can walk over.
 * -1 representing obstacles that we cannot walk over.
 * 
 * 
 * Return the number of 4-directional walks from the starting square to the
 * ending square, that walk over every non-obstacle square exactly once.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 * Output: 2
 * Explanation: We have the following two paths: 
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 * 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 * Output: 4
 * Explanation: We have the following four paths: 
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 * 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 * 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 * 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[0,1],[2,0]]
 * Output: 0
 * Explanation: There is no path that walks over every empty square exactly
 * once.
 * Note that the starting and ending square can be anywhere in the grid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 20
 * 1 <= m * n <= 20
 * -1 <= grid[i][j] <= 2
 * There is exactly one starting cell and one ending cell.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // dfs + backtracking
    int uniquePathsIII1(vector<vector<int>>& grid) {
        int ans = 0, m = grid.size(), n = grid[0].size();

        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1},};
        int left_0 = 0, start_r = -1, start_c = -1;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int x = grid[r][c];
                if (x == 1) {
                    start_r = r;
                    start_c = c;
                    grid[r][c] = 0;
                    left_0++;
                } else if (x == 0) {
                    left_0++;
                }
            }
        } 

        auto dfs = [&](auto &dfs, int r, int c) -> void {
            if (r < 0 || r >= m || c < 0 || c >= n) {
                return;
            }

            int g = grid[r][c];

            if (g == 2 && left_0 == 0) {
                ans++;
                return;
            } else if (g == 0) {
                left_0--;
            } else {
                return;
            }

            grid[r][c] = -1;
            for (auto &[dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                dfs(dfs, nr, nc);
            }
            left_0++;
            grid[r][c] = g;
        };

        dfs(dfs, start_r, start_c);
          
        return ans;
    }

    // dp + bit
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int vis = 0, start_r = -1, start_c = -1;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int x = grid[r][c];
                if (x == 1) {
                    start_r = r;
                    start_c = c;
                } else if (x == -1) {
                    vis |= 1 << (r * n + c);
                }
            }
        } 

        int all = (1 << m * n) - 1; // 全集
        unordered_map<int, int> memo;

        auto dfs = [&](this auto &&dfs, int r, int c, int vis) -> int {
            int p = r * n + c;
            if (r < 0 || r >= m || c < 0 || c >= n || vis >> p & 1) {
                return 0;
            }

            int g = grid[r][c];
            vis |= 1 << p;

            if (g == 2) {
                return vis == all;
            }

            int key = (p << m * n) | vis;
            if (memo[key]) {
                return memo[key];
            }
            
            return memo[key] = dfs(r - 1, c, vis) + dfs(r + 1, c, vis) +
                               dfs(r, c - 1, vis) + dfs(r, c + 1, vis);
        };
        
        return dfs(start_r, start_c, vis);
    }
};
// @lc code=end

