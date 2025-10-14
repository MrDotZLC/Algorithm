/*
 * @lc app=leetcode id=1504 lang=cpp
 *
 * [1504] Count Submatrices With All Ones
 *
 * https://leetcode.com/problems/count-submatrices-with-all-ones/description/
 *
 * algorithms
 * Medium (57.35%)
 * Likes:    2634
 * Dislikes: 219
 * Total Accepted:    143K
 * Total Submissions: 201.3K
 * Testcase Example:  '[[1,0,1],[1,1,0],[1,1,0]]'
 *
 * Given an m x n binary matrix mat, return the number of submatrices that have
 * all ones.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
 * Output: 13
 * Explanation: 
 * There are 6 rectangles of side 1x1.
 * There are 2 rectangles of side 1x2.
 * There are 3 rectangles of side 2x1.
 * There is 1 rectangle of side 2x2. 
 * There is 1 rectangle of side 3x1.
 * Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
 * Output: 24
 * Explanation: 
 * There are 8 rectangles of side 1x1.
 * There are 5 rectangles of side 1x2.
 * There are 2 rectangles of side 1x3. 
 * There are 4 rectangles of side 2x1.
 * There are 2 rectangles of side 2x2. 
 * There are 2 rectangles of side 3x1. 
 * There is 1 rectangle of side 3x2. 
 * Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 150
 * mat[i][j] is either 0 or 1.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int ans = 0, n = mat[0].size();
        vector<int> heights(n);
        for (auto &row : mat) {
            for (int i = 0; i < n; i++) {
                if (row[i] == 0) {
                    heights[i] = 0;
                } else {
                    heights[i]++;
                }
            }

            vector<tuple<int, int, int>> stk; // (i, f, hieghts[i])
            stk.emplace_back(-1, 0, -1);
            for (int r = 0; r < n; r++) {
                int h = heights[r];
                while (get<2>(stk.back()) >= h) {
                    stk.pop_back();
                }
                auto [l, f, _] = stk.back();
                f += (r - l) * h;
                ans += f;
                stk.emplace_back(r, f, h);
            }
        }
        return ans;
    }
};
// @lc code=end

