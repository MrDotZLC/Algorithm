/*
 * @lc app=leetcode id=1901 lang=cpp
 *
 * [1901] Find a Peak Element II
 *
 * https://leetcode.com/problems/find-a-peak-element-ii/description/
 *
 * algorithms
 * Medium (53.41%)
 * Likes:    2480
 * Dislikes: 153
 * Total Accepted:    140.2K
 * Total Submissions: 261.6K
 * Testcase Example:  '[[1,4],[3,2]]'
 *
 * A peak element in a 2D grid is an element that is strictly greater than all
 * of its adjacent neighbors to the left, right, top, and bottom.
 * 
 * Given a 0-indexed m x n matrix mat where no two adjacent cells are equal,
 * find any peak element mat[i][j] and return the length 2 array [i,j].
 * 
 * You may assume that the entire matrix is surrounded by an outer perimeter
 * with the value -1 in each cell.
 * 
 * You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: mat = [[1,4],[3,2]]
 * Output: [0,1]
 * Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both
 * acceptable answers.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
 * Output: [1,1]
 * Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both
 * acceptable answers.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 500
 * 1 <= mat[i][j] <= 10^5
 * No two adjacent cells are equal.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        auto check_range = [&](int row) -> int {
            return ranges::max_element(mat[row]) - mat[row].begin();
        };

        int L = -1, R = mat.size() - 1;
        while (L + 1 < R) {
            int row = L + (R - L) / 2;
            int col = check_range(row);
            (mat[row][col] < mat[row + 1][col] ? L : R) = row;
        }
        return {R, check_range(R)};
    }
};
// @lc code=end

