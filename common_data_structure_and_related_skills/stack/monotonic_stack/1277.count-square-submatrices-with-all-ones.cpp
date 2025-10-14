/*
 * @lc app=leetcode id=1277 lang=cpp
 *
 * [1277] Count Square Submatrices with All Ones
 *
 * https://leetcode.com/problems/count-square-submatrices-with-all-ones/description/
 *
 * algorithms
 * Medium (78.81%)
 * Likes:    5883
 * Dislikes: 114
 * Total Accepted:    460.3K
 * Total Submissions: 570.9K
 * Testcase Example:  '[[0,1,1,1],[1,1,1,1],[0,1,1,1]]'
 *
 * Given a m * n matrix of ones and zeros, return how many square submatrices
 * have all ones.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: matrix =
 * [
 * [0,1,1,1],
 * [1,1,1,1],
 * [0,1,1,1]
 * ]
 * Output: 15
 * Explanation: 
 * There are 10 squares of side 1.
 * There are 4 squares of side 2.
 * There is  1 square of side 3.
 * Total number of squares = 10 + 4 + 1 = 15.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: matrix = 
 * [
 * ⁠ [1,0,1],
 * ⁠ [1,1,0],
 * ⁠ [1,1,0]
 * ]
 * Output: 7
 * Explanation: 
 * There are 6 squares of side 1.  
 * There is 1 square of side 2. 
 * Total number of squares = 6 + 1 = 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 300
 * 1 <= arr[0].length <= 300
 * 0 <= arr[i][j] <= 1
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int ans = 0, n = matrix[0].size();
        vector<int> heights(n + 1);
        for (auto &row : matrix) {
            for (int i = 0; i < n; i++) {
                if (row[i] == 0) {
                    heights[i] = 0;
                } else {
                    heights[i]++;
                }
            }

            vector<int> stk; // (i, f, hieghts[i])
            stk.emplace_back(-1);
            for (int r = 0; r < n + 1; r++) {
                int h_r = heights[r];
                while (stk.size() > 1 && heights[stk.back()] >= h_r) {
                    int h_i = heights[stk.back()];
                    stk.pop_back();
                    int l = stk.back();
                    int w = r - l - 1;
                    int lower = (l < 0 ? h_r : max(heights[l], h_r)) + 1;
                    int upper = min(w, h_i);
                    if (upper >= lower) {
                        ans += (2 * w + 2 - lower - upper) * (upper - lower + 1) / 2; // ∑_H∈[lower, upper] (w - H + 1)
                    }
                }
                stk.emplace_back(r);
            }
        }
        return ans;
    }
};
// @lc code=end

