/*
 * @lc app=leetcode id=3446 lang=cpp
 *
 * [3446] Sort Matrix by Diagonals
 *
 * https://leetcode.com/problems/sort-matrix-by-diagonals/description/
 *
 * algorithms
 * Medium (70.63%)
 * Likes:    487
 * Dislikes: 93
 * Total Accepted:    128.6K
 * Total Submissions: 151.8K
 * Testcase Example:  '[[1,7,3],[9,8,2],[4,5,6]]'
 *
 * You are given an n x n square matrix of integers grid. Return the matrix
 * such that:
 * 
 * 
 * The diagonals in the bottom-left triangle (including the middle diagonal)
 * are sorted in non-increasing order.
 * The diagonals in the top-right triangle are sorted in non-decreasing
 * order.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
 * 
 * Output: [[8,2,3],[9,6,7],[4,5,1]]
 * 
 * Explanation:
 * 
 * 
 * 
 * The diagonals with a black arrow (bottom-left triangle) should be sorted in
 * non-increasing order:
 * 
 * 
 * [1, 8, 6] becomes [8, 6, 1].
 * [9, 5] and [4] remain unchanged.
 * 
 * 
 * The diagonals with a blue arrow (top-right triangle) should be sorted in
 * non-decreasing order:
 * 
 * 
 * [7, 2] becomes [2, 7].
 * [3] remains unchanged.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[0,1],[1,2]]
 * 
 * Output: [[2,1],[1,0]]
 * 
 * Explanation:
 * 
 * 
 * 
 * The diagonals with a black arrow must be non-increasing, so [0, 2] is
 * changed to [2, 0]. The other diagonals are already in the correct order.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[1]]
 * 
 * Output: [[1]]
 * 
 * Explanation:
 * 
 * Diagonals with exactly one element are already in order, so no changes are
 * needed.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * grid.length == grid[i].length == n
 * 1 <= n <= 10
 * -10^5 <= grid[i][j] <= 10^5
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
    // k = i - j + n
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int k = 1; k < m + n; k++) {
            int min_j = max(n - k, 0);
            int max_j = min(m - 1 + n - k, n - 1); 
            vector<int> a;
            for (int j = min_j; j <= max_j; j++) {
                a.push_back(grid[k + j - n][j]);
            }
            if (min_j > 0) {
                ranges::sort(a);
            } else {
                ranges::sort(a, greater());
            }

            for (int j = min_j; j <= max_j; j++) {
                grid[k + j - n][j] = a[j - min_j];
            }
        }
        return grid;
    }
};
// @lc code=end

