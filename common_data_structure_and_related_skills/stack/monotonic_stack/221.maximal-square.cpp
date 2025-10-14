/*
 * @lc app=leetcode id=221 lang=cpp
 *
 * [221] Maximal Square
 *
 * https://leetcode.com/problems/maximal-square/description/
 *
 * algorithms
 * Medium (48.95%)
 * Likes:    10819
 * Dislikes: 253
 * Total Accepted:    866.8K
 * Total Submissions: 1.8M
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * Given an m x n binary matrix filled with 0's and 1's, find the largest
 * square containing only 1's and return its area.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: matrix =
 * [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * Output: 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: matrix = [["0","1"],["1","0"]]
 * Output: 1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: matrix = [["0"]]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 300
 * matrix[i][j] is '0' or '1'.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 逐层生成单调栈
    int maximalSquare(vector<vector<char>>& matrix) {
        int ans = 0, n = matrix[0].size();
        vector<int> heights(n + 1);
        for (auto &row : matrix) {
            for (int i = 0; i < n; i++) {
                if (row[i] == '0') {
                    heights[i] = 0;
                } else {
                    heights[i]++;
                }
            }
            ans = max(ans, largestRectangleArea(heights));
        }
        return ans * ans;
    }

    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        // i右侧小于等于height[i]，哪怕有重复元素，
        // 其中一个元素一定不会算漏，如此就能一次循环得到左右两边的最小下标
        // 如：13531，第一个3会算漏得3*2，第二个则不会得3*3
        vector<int> stk;
        stk.push_back(-1);
        int ans = 0;

        for (int r = 0; r < n; r++) {
            int h = heights[r];
            while (stk.size() > 1 && h <= heights[stk.back()]) {
                int i = stk.back(); // 矩形高
                stk.pop_back();
                int l = stk.back();
                ans = max(ans, min(heights[i], r - l - 1 ));// 宽度为r-1-(l+1)+1=r-l-1;
            }
            stk.push_back(r);
        }

        return ans;
    }
};
// @lc code=end

