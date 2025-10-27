/*
 * @lc app=leetcode id=3148 lang=cpp
 *
 * [3148] Maximum Difference Score in a Grid
 *
 * https://leetcode.com/problems/maximum-difference-score-in-a-grid/description/
 *
 * algorithms
 * Medium (46.87%)
 * Likes:    272
 * Dislikes: 23
 * Total Accepted:    21.9K
 * Total Submissions: 46.4K
 * Testcase Example:  '[[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]'
 *
 * You are given an m x n matrix grid consisting of positive integers. You can
 * move from a cell in the matrix to any other cell that is either to the
 * bottom or to the right (not necessarily adjacent). The score of a move from
 * a cell with the value c1 to a cell with the value c2 is c2 - c1.
 * 
 * You can start at any cell, and you have to make at least one move.
 * 
 * Return the maximum total score you can achieve.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]
 * 
 * Output: 9
 * 
 * Explanation: We start at the cell (0, 1), and we perform the following
 * moves:
 * - Move from the cell (0, 1) to (2, 1) with a score of 7 - 5 = 2.
 * - Move from the cell (2, 1) to (2, 2) with a score of 14 - 7 = 7.
 * The total score is 2 + 7 = 9.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: grid = [[4,3,2],[3,2,1]]
 * 
 * Output: -1
 * 
 * Explanation: We start at the cell (0, 0), and we perform one move: (0, 0) to
 * (0, 1). The score is 3 - 4 = -1.
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
 * 1 <= grid[i][j] <= 10^5
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int ans = -__INT_MAX__, m = grid.size(), n = grid[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1, __INT_MAX__));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int mn = min(sum[i + 1][j], sum[i][j + 1]);
                ans = max(ans, grid[i][j] - mn);
                sum[i + 1][j + 1] = min(mn, grid[i][j]);
            }
        }
        return ans;
    }
};
// @lc code=end

