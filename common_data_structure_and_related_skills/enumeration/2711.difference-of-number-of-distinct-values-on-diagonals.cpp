/*
 * @lc app=leetcode id=2711 lang=cpp
 *
 * [2711] Difference of Number of Distinct Values on Diagonals
 *
 * https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/description/
 *
 * algorithms
 * Medium (67.85%)
 * Likes:    140
 * Dislikes: 210
 * Total Accepted:    21.9K
 * Total Submissions: 32.2K
 * Testcase Example:  '[[1,2,3],[3,1,5],[3,2,1]]'
 *
 * Given a 2D grid of size m x n, you should find the matrix answer of size m x
 * n.
 * 
 * The cell answer[r][c] is calculated by looking at the diagonal values of the
 * cell grid[r][c]:
 * 
 * 
 * Let leftAbove[r][c] be the number of distinct values on the diagonal to the
 * left and above the cell grid[r][c] not including the cell grid[r][c]
 * itself.
 * Let rightBelow[r][c] be the number of distinct values on the diagonal to the
 * right and below the cell grid[r][c], not including the cell grid[r][c]
 * itself.
 * Then answer[r][c] = |leftAbove[r][c] - rightBelow[r][c]|.
 * 
 * 
 * A matrix diagonal is a diagonal line of cells starting from some cell in
 * either the topmost row or leftmost column and going in the bottom-right
 * direction until the end of the matrix is reached.
 * 
 * 
 * For example, in the below diagram the diagonal is highlighted using the cell
 * with indices (2, 3) colored gray:
 * 
 * 
 * Red-colored cells are left and above the cell.
 * Blue-colored cells are right and below the cell.
 * 
 * 
 * 
 * 
 * 
 * 
 * Return the matrix answer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,2,3],[3,1,5],[3,2,1]]
 * 
 * Output: Output: [[1,1,0],[1,0,1],[0,1,1]]
 * 
 * Explanation:
 * 
 * To calculate the answer cells:
 * 
 * 
 * 
 * 
 * answer
 * left-above elements
 * leftAbove
 * right-below elements
 * rightBelow
 * |leftAbove - rightBelow|
 * 
 * 
 * 
 * 
 * [0][0]
 * []
 * 0
 * [grid[1][1], grid[2][2]]
 * |{1, 1}| = 1
 * 1
 * 
 * 
 * [0][1]
 * []
 * 0
 * [grid[1][2]]
 * |{5}| = 1
 * 1
 * 
 * 
 * [0][2]
 * []
 * 0
 * []
 * 0
 * 0
 * 
 * 
 * [1][0]
 * []
 * 0
 * [grid[2][1]]
 * |{2}| = 1
 * 1
 * 
 * 
 * [1][1]
 * [grid[0][0]]
 * |{1}| = 1
 * [grid[2][2]]
 * |{1}| = 1
 * 0
 * 
 * 
 * [1][2]
 * [grid[0][1]]
 * |{2}| = 1
 * []
 * 0
 * 1
 * 
 * 
 * [2][0]
 * []
 * 0
 * []
 * 0
 * 0
 * 
 * 
 * [2][1]
 * [grid[1][0]]
 * |{3}| = 1
 * []
 * 0
 * 1
 * 
 * 
 * [2][2]
 * [grid[0][0], grid[1][1]]
 * |{1, 1}| = 1
 * []
 * 0
 * 1
 * 
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1]]
 * 
 * Output: Output: [[0]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n, grid[i][j] <= 50
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // k = i - j + n
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        unordered_set<int> st;
        for (int k = 2; k < m + n - 1; k++) {
            int min_j = max(n - k, 0);
            int max_j = min(n - k + m - 1, n - 1);

            st.clear();
            for (int j = min_j; j <= max_j; j++) {
                int i = j + k - n;
                ans[i][j] = st.size();
                st.insert(grid[i][j]);
            }
            st.clear();
            for (int j = max_j; j >= min_j; j--) {
                int i = j + k - n;
                ans[i][j] = abs(ans[i][j] - (int)st.size());
                st.insert(grid[i][j]);
            }
        }
        return ans;
    }
};
// @lc code=end

