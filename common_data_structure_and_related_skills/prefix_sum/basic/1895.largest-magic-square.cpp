/*
 * @lc app=leetcode id=1895 lang=cpp
 *
 * [1895] Largest Magic Square
 *
 * https://leetcode.com/problems/largest-magic-square/description/
 *
 * algorithms
 * Medium (52.59%)
 * Likes:    323
 * Dislikes: 267
 * Total Accepted:    13.9K
 * Total Submissions: 26.3K
 * Testcase Example:  '[[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]'
 *
 * A k x k magic square is a k x k grid filled with integers such that every
 * row sum, every column sum, and both diagonal sums are all equal. The
 * integers in the magic square do not have to be distinct. Every 1 x 1 grid is
 * trivially a magic square.
 * 
 * Given an m x n integer grid, return the size (i.e., the side length k) of
 * the largest magic square that can be found within this grid.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
 * Output: 3
 * Explanation: The largest magic square has a size of 3.
 * Every row sum, column sum, and diagonal sum of this magic square is equal to
 * 12.
 * - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
 * - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
 * - Diagonal sums: 5+4+3 = 6+4+2 = 12
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
 * Output: 2
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 50
 * 1 <= grid[i][j] <= 10^6
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> r_sum(m, vector<int>(n + 1, 0)),
            c_sum(m + 1, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r_sum[i][j + 1] = r_sum[i][j] + grid[i][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                c_sum[i + 1][j] = c_sum[i][j] + grid[i][j];
            }
        }

        for (int k = min(m, n); k > 1; k--) {
            for (int i = 0; i <= m - k; i++) {
                for (int j = 0; j <= n - k; j++) {
                    int target = r_sum[i][j + k] - r_sum[i][j];
                    bool ok = true;

                    // 检查行
                    for (int r = i; r < i + k; r++) {
                        if (r_sum[r][j + k] - r_sum[r][j] != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) {
                        continue;
                    }

                    // 检查列
                    for (int c = j; c < j + k; c++) {
                        if (c_sum[i + k][c] - c_sum[i][c] != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) {
                        continue;
                    }

                    // 检查对角
                    int diag1 = 0, diag2 = 0;
                    for (int t = 0; t < k; t++) {
                        diag1 += grid[i + t][j + t];
                        diag2 += grid[i + t][j + k - 1 - t];
                    }
                    if (diag1 != target || diag2 != target) {
                        continue;
                    }

                    return k;
                }
            }
        }
        return 1;
    }
};
// @lc code=end

