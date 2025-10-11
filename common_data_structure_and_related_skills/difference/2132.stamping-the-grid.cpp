/*
 * @lc app=leetcode id=2132 lang=cpp
 *
 * [2132] Stamping the Grid
 *
 * https://leetcode.com/problems/stamping-the-grid/description/
 *
 * algorithms
 * Hard (33.64%)
 * Likes:    413
 * Dislikes: 47
 * Total Accepted:    9.3K
 * Total Submissions: 27.2K
 * Testcase Example:  '[[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]]\n4\n3'
 *
 * You are given an m x n binary matrix grid where each cell is either 0
 * (empty) or 1 (occupied).
 * 
 * You are then given stamps of size stampHeight x stampWidth. We want to fit
 * the stamps such that they follow the given restrictions and
 * requirements:
 * 
 * 
 * Cover all the empty cells.
 * Do not cover any of the occupied cells.
 * We can put as many stamps as we want.
 * Stamps can overlap with each other.
 * Stamps are not allowed to be rotated.
 * Stamps must stay completely inside the grid.
 * 
 * 
 * Return true if it is possible to fit the stamps while following the given
 * restrictions and requirements. Otherwise, return false.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]],
 * stampHeight = 4, stampWidth = 3
 * Output: true
 * Explanation: We have two overlapping stamps (labeled 1 and 2 in the image)
 * that are able to cover all the empty cells.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]], stampHeight = 2,
 * stampWidth = 2 
 * Output: false 
 * Explanation: There is no way to fit the stamps onto all the empty cells
 * without the stamps going outside the grid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[r].length
 * 1 <= m, n <= 10^5
 * 1 <= m * n <= 2 * 10^5
 * grid[r][c] is either 0 or 1.
 * 1 <= stampHeight, stampWidth <= 10^5
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(), n = grid[0].size();

        // 计算二维前缀和
        vector<vector<int>> sum(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] -
                                    sum[i][j] + grid[i][j];
            }
        }

        // 计算二维差分
        vector<vector<int>> diff(m + 2, vector<int>(n + 2));
        for (int i2 = stampHeight; i2 <= m; i2++) {
            for (int j2 = stampWidth; j2 <= n; j2++) {
                int i1 = i2 - stampHeight + 1;
                int j1 = j2 - stampWidth + 1;
                if (sum[i2][j2] - sum[i2][j1 - 1] - sum[i1 - 1][j2] +
                        sum[i1 - 1][j1 - 1] ==
                    0) {
                    diff[i1][j1]++;
                    diff[i1][j2 + 1]--;
                    diff[i2 + 1][j1]--;
                    diff[i2 + 1][j2 + 1]++;
                }
            }
        }

        // 还原二维差分为计数矩阵
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                diff[i + 1][j + 1] += diff[i + 1][j] + diff[i][j + 1] -
                                    diff[i][j];
                if (grid[i][j] == 0 && diff[i + 1][j + 1] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end

