/*
 * @lc app=leetcode id=498 lang=cpp
 *
 * [498] Diagonal Traverse
 *
 * https://leetcode.com/problems/diagonal-traverse/description/
 *
 * algorithms
 * Medium (63.34%)
 * Likes:    4225
 * Dislikes: 769
 * Total Accepted:    524.3K
 * Total Submissions: 787.1K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given an m x n matrix mat, return an array of all the elements of the array
 * in a diagonal order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,4,7,5,3,6,8,9]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mat = [[1,2],[3,4]]
 * Output: [1,2,3,4]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 10^4
 * 1 <= m * n <= 10^4
 * -10^5 <= mat[i][j] <= 10^5
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
    // k = i + j
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> ans;
        for (int k = 0; k < m + n - 1; k++) {
            int min_j = max(k - m + 1, 0);
            int max_j = min(k, n - 1);

            if (k % 2 == 0) {
                for (int j = min_j; j <= max_j; j++) {
                    ans.push_back(mat[k - j][j]);
                }
            } else {
                for (int j = max_j; j >= min_j; j--) {
                    ans.push_back(mat[k - j][j]);
                }
            }
        }
        return ans;
    }
};
// @lc code=end

