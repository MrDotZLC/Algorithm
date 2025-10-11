/*
 * @lc app=leetcode id=2536 lang=cpp
 *
 * [2536] Increment Submatrices by One
 *
 * https://leetcode.com/problems/increment-submatrices-by-one/description/
 *
 * algorithms
 * Medium (52.21%)
 * Likes:    492
 * Dislikes: 62
 * Total Accepted:    25.8K
 * Total Submissions: 48.6K
 * Testcase Example:  '3\n[[1,1,2,2],[0,0,1,1]]'
 *
 * You are given a positive integer n, indicating that we initially have an n x
 * n 0-indexed integer matrix mat filled with zeroes.
 * 
 * You are also given a 2D integer array query. For each query[i] = [row1i,
 * col1i, row2i, col2i], you should do the following operation:
 * 
 * 
 * Add 1 to every element in the submatrix with the top left corner (row1i,
 * col1i) and the bottom right corner (row2i, col2i). That is, add 1 to
 * mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
 * 
 * 
 * Return the matrix mat after performing every query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
 * Output: [[1,1,0],[1,2,1],[0,1,1]]
 * Explanation: The diagram above shows the initial matrix, the matrix after
 * the first query, and the matrix after the second query.
 * - In the first query, we add 1 to every element in the submatrix with the
 * top left corner (1, 1) and bottom right corner (2, 2).
 * - In the second query, we add 1 to every element in the submatrix with the
 * top left corner (0, 0) and bottom right corner (1, 1).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, queries = [[0,0,1,1]]
 * Output: [[1,1],[1,1]]
 * Explanation: The diagram above shows the initial matrix and the matrix after
 * the first query.
 * - In the first query we add 1 to every element in the matrix.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 500
 * 1 <= queries.length <= 10^4
 * 0 <= row1i <= row2i < n
 * 0 <= col1i <= col2i < n
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n + 2, vector<int>(n + 2));
        for (auto &q : queries) {
            int r1 = q[0], c1 = q[1], r2 = q[2], c2 = q[3];
            diff[r1 + 1][c1 + 1]++;
            diff[r1 + 1][c2 + 2]--;
            diff[r2 + 2][c1 + 1]--;
            diff[r2 + 2][c2 + 2]++;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                diff[i + 1][j + 1] +=
                    diff[i + 1][j] + diff[i][j + 1] - diff[i][j];
            }
        }
        diff.pop_back();
        diff.erase(diff.begin());
        for (auto &row : diff) {
            row.pop_back();
            row.erase(row.begin());
        }
        return diff;
    }
};
// @lc code=end

