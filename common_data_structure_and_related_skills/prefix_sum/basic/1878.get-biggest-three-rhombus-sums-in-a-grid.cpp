/*
 * @lc app=leetcode id=1878 lang=cpp
 *
 * [1878] Get Biggest Three Rhombus Sums in a Grid
 *
 * https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/description/
 *
 * algorithms
 * Medium (49.39%)
 * Likes:    227
 * Dislikes: 530
 * Total Accepted:    19.7K
 * Total Submissions: 39.7K
 * Testcase Example:  '[[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]'
 *
 * You are given an m x n integer matrix grid​​​.
 * 
 * A rhombus sum is the sum of the elements that form the border of a regular
 * rhombus shape in grid​​​. The rhombus must have the shape of a square
 * rotated 45 degrees with each of the corners centered in a grid cell. Below
 * is an image of four valid rhombus shapes with the corresponding colored
 * cells that should be included in each rhombus sum:
 * 
 * Note that the rhombus can have an area of 0, which is depicted by the purple
 * rhombus in the bottom right corner.
 * 
 * Return the biggest three distinct rhombus sums in the grid in descending
 * order. If there are less than three distinct values, return all of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid =
 * [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
 * Output: [228,216,211]
 * Explanation: The rhombus shapes for the three biggest distinct rhombus sums
 * are depicted above.
 * - Blue: 20 + 3 + 200 + 5 = 228
 * - Red: 200 + 2 + 10 + 4 = 216
 * - Green: 5 + 200 + 4 + 2 = 211
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [20,9,8]
 * Explanation: The rhombus shapes for the three biggest distinct rhombus sums
 * are depicted above.
 * - Blue: 4 + 2 + 6 + 8 = 20
 * - Red: 9 (area 0 rhombus in the bottom right corner)
 * - Green: 8 (area 0 rhombus in the bottom middle)
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[7,7,7]]
 * Output: [7]
 * Explanation: All three possible rhombus sums are the same, so return
 * [7].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 50
 * 1 <= grid[i][j] <= 10^5
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        ds.resize(m + 1, vector<int>(n + 1, 0));
        as.resize(m + 1, vector<int>(n + 1, 0));
        x = y = z = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = grid[i][j];
                ds[i + 1][j + 1] = ds[i][j] + v; // ↘
                as[i + 1][j] = as[i][j + 1] + v; // ↙
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = grid[i][j];
                update(v);
                for (int k = 1; k <= i && k + i < m && k <= j && k + j < n; k++) {
                    int a = query_diagonal(i - k, j, k);
                    int b = query_anti_diagonal(i - k + 1, j - 1, k - 1);
                    int c = query_diagonal(i, j - k, k);
                    int d = query_anti_diagonal(i, j + k, k + 1);
                    update(a + b + c + d);
                }
            }
        }

        if (z == 0) {
            return y == 0 ? vector<int>{x} : vector<int>{x, y};
        }
        return {x, y, z};
    }

    int query_diagonal(int x, int y, int k) {
        return ds[x + k][y + k] - ds[x][y];
    }

    int query_anti_diagonal(int x, int y, int k){ 
        return as[x + k][y + 1 - k] - as[x][y + 1];
    }

    void update(int v) {
        if (v > x) {
            z = y;
            y = x;
            x = v;
        } else if (v > y && v < x) {
            z = y;
            y = v;
        } else if (v > z && v < y) {
            z = v;
        }
    }

private:
    vector<vector<int>> ds, as;
    int x, y, z;
};
// @lc code=end

