/*
 * @lc app=leetcode id=1039 lang=cpp
 *
 * [1039] Minimum Score Triangulation of Polygon
 *
 * https://leetcode.com/problems/minimum-score-triangulation-of-polygon/description/
 *
 * algorithms
 * Medium (60.33%)
 * Likes:    2292
 * Dislikes: 297
 * Total Accepted:    135.5K
 * Total Submissions: 201.5K
 * Testcase Example:  '[1,2,3]'
 *
 * You have a convex n-sided polygon where each vertex has an integer value.
 * You are given an integer array values where values[i] is the value of the
 * i^th vertex in clockwise order.
 * 
 * Polygon triangulation is a process where you divide a polygon into a set of
 * triangles and the vertices of each triangle must also be vertices of the
 * original polygon. Note that no other shapes other than triangles are allowed
 * in the division. This process will result in n - 2 triangles.
 * 
 * You will triangulate the polygon. For each triangle, the weight of that
 * triangle is the product of the values at its vertices. The total score of
 * the triangulation is the sum of these weights over all n - 2 triangles.
 * 
 * Return the minimum possible score that you can achieve with some
 * triangulation of the polygon.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: values = [1,2,3]
 * 
 * Output: 6
 * 
 * Explanation: The polygon is already triangulated, and the score of the only
 * triangle is 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: values = [3,7,4,5]
 * 
 * Output: 144
 * 
 * Explanation: There are two triangulations, with possible scores: 3*7*5 +
 * 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.
 * The minimum score is 144.
 * 
 * 
 * Example 3:
 * 
 * ​​​​​​​
 * 
 * 
 * Input: values = [1,3,1,4,1,5]
 * 
 * Output: 13
 * 
 * Explanation: The minimum score triangulation is 1*1*3 + 1*1*4 + 1*1*5 +
 * 1*1*1 = 13.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == values.length
 * 3 <= n <= 50
 * 1 <= values[i] <= 100
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 把0和n-1作为底边顶点，在(1,n-2)中枚举上顶点k，状态转移方程：
 * f(i,j) = min{f(i,k) + f(k,j) + v[i]*v[k]*v[j]}, k属于(0,n-1)
 * 边界：f(i,j)=0, 当i+1=j
 */
class Solution {
public:
    // 记忆化递归
    int minScoreTriangulation1(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i + 1 == j) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                res = min(res, dfs(dfs, i, k) + dfs(dfs, k, j) +
                                   values[i] * values[k] * values[j]);
            }
            return res;
        };
        return dfs(dfs, 0, n - 1);
    }

    // DP
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> f(n, vector<int>(n));
        // f[i]是从f[k]转移得来，则倒序枚举且i+1=j是初始值，即i∈[n-3, 0]
        for (int i = n - 3; i >= 0; i--) {
            // f[i][j]是从f[i][k]转移得来，则正序枚举，j∈[i+2, n-1]
            for (int j = i + 2; j < n; j++) {
                // 默认值为极大值，f不初始化INT_MAX是防止累加溢出
                f[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] +
                                               values[i] * values[k] *
                                                   values[j]);
                }
            }
        }
        return f[0][n - 1];
    }
};
// @lc code=end

