/*
 * @lc app=leetcode id=3212 lang=cpp
 *
 * [3212] Count Submatrices With Equal Frequency of X and Y
 *
 * https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/description/
 *
 * algorithms
 * Medium (50.66%)
 * Likes:    156
 * Dislikes: 26
 * Total Accepted:    26K
 * Total Submissions: 50.9K
 * Testcase Example:  '[["X","Y","."],["Y",".","."]]'
 *
 * Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or
 * '.', return the number of submatrices that contain:
 * 
 * 
 * grid[0][0]
 * an equal frequency of 'X' and 'Y'.
 * at least one 'X'.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [["X","Y","."],["Y",".","."]]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [["X","X"],["X","Y"]]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * No submatrix has an equal frequency of 'X' and 'Y'.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[".","."],[".","."]]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * No submatrix has at least one 'X'.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= grid.length, grid[i].length <= 1000
 * grid[i][j] is either 'X', 'Y', or '.'.
 * 
 * 
 */
#include <vector>
#include <array>
using namespace std;
// @lc code=start
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int ans = 0;
        vector<array<int, 2>> col_cnt(grid[0].size());
        for (auto& row : grid) {
            int s0 = 0, s1 = 0;
            for (int j = 0; j < row.size(); j++) {
                if (row[j] != '.') {
                    col_cnt[j][row[j] & 1]++;
                }
                s0 += col_cnt[j][0];
                s1 += col_cnt[j][1];
                if (s0 && s0 == s1) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

