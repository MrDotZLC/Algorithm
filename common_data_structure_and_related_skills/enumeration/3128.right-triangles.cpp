/*
 * @lc app=leetcode id=3128 lang=cpp
 *
 * [3128] Right Triangles
 *
 * https://leetcode.com/problems/right-triangles/description/
 *
 * algorithms
 * Medium (47.27%)
 * Likes:    129
 * Dislikes: 23
 * Total Accepted:    22.3K
 * Total Submissions: 46.8K
 * Testcase Example:  '[[0,1,0],[0,1,1],[0,1,0]]'
 *
 * You are given a 2D boolean matrix grid.
 * 
 * A collection of 3 elements of grid is a right triangle if one of its
 * elements is in the same row with another element and in the same column with
 * the third element. The 3 elements may not be next to each other.
 * 
 * Return an integer that is the number of right triangles that can be made
 * with 3 elements of grid such that all of them have a value of 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 0
 * 1
 * 1
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 0
 * 1
 * 1
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 0
 * 1
 * 1
 * 
 * 
 * 0
 * 1
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * There are two right triangles with elements of the value 1. Notice that the
 * blue ones do not form a right triangle because the 3 elements are in the
 * same column.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * 
 * 1
 * 0
 * 0
 * 0
 * 
 * 
 * 0
 * 1
 * 0
 * 1
 * 
 * 
 * 1
 * 0
 * 0
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * Input: grid = [[1,0,0,0],[0,1,0,1],[1,0,0,0]]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * There are no right triangles with elements of the value 1.  Notice that the
 * blue ones do not form a right triangle.
 * 
 * 
 * Example 3:
 * 
 * 
 * 
 * 
 * 
 * 1
 * 0
 * 1
 * 
 * 
 * 1
 * 0
 * 0
 * 
 * 
 * 1
 * 0
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 1
 * 0
 * 1
 * 
 * 
 * 1
 * 0
 * 0
 * 
 * 
 * 1
 * 0
 * 0
 * 
 * 
 * 
 * 
 * 
 * 
 * Input: grid = [[1,0,1],[1,0,0],[1,0,0]]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * There are two right triangles with elements of the value 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= grid.length <= 1000
 * 1 <= grid[i].length <= 1000
 * 0 <= grid[i][j] <= 1
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        long long ans = 0;
        int n = grid[0].size();
        vector<int> col_sum(n, -1);
        for (auto &row : grid) {
            for (int col = 0; col < n; col++) {
                col_sum[col] += row[col];
            }
        }

        for (auto &row : grid) {
            int row_sum = reduce(row.begin(), row.end(), 0) - 1;
            for (int col = 0; col < n; col++) {
                if (row[col]) {
                    ans += row_sum * col_sum[col];
                }
            }
        }
        return ans;
    }
};
// @lc code=end

