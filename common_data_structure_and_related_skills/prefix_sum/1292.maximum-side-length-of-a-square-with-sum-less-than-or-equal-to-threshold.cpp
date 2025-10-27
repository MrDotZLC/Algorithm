/*
 * @lc app=leetcode id=1292 lang=cpp
 *
 * [1292] Maximum Side Length of a Square with Sum Less than or Equal to Threshold
 *
 * https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/description/
 *
 * algorithms
 * Medium (53.59%)
 * Likes:    1125
 * Dislikes: 100
 * Total Accepted:    38.9K
 * Total Submissions: 72.4K
 * Testcase Example:  '[[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]]\n4'
 *
 * Given a m x n matrix mat and an integer threshold, return the maximum
 * side-length of a square with a sum less than or equal to threshold or return
 * 0 if there is no such square.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold =
 * 4
 * Output: 2
 * Explanation: The maximum side length of square with sum less than 4 is 2 as
 * shown.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]],
 * threshold = 1
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 300
 * 0 <= mat[i][j] <= 10^4
 * 0 <= threshold <= 10^5
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] -
                                    sum[i][j] + mat[i][j];
            }
        }

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = ans; k <= i; k++) {
                    if (k + 1 <= ans) { // 边长
                        continue;
                    }
                    int row0 = i - k, col0 = j - k;
                    if (col0 < 0) {
                        break;
                    }
                    int area_sum = sum[i + 1][j + 1] - sum[i + 1][col0] -
                                   sum[row0][j + 1] + sum[row0][col0];

                    if (area_sum <= threshold) {
                        ans = k + 1;
                    } else {
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
// @lc code=end

