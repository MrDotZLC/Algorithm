/*
 * @lc app=leetcode id=931 lang=cpp
 *
 * [931] Minimum Falling Path Sum
 *
 * https://leetcode.com/problems/minimum-falling-path-sum/description/
 *
 * algorithms
 * Medium (61.16%)
 * Likes:    6860
 * Dislikes: 169
 * Total Accepted:    613.4K
 * Total Submissions: 1M
 * Testcase Example:  '[[2,1,3],[6,5,4],[7,8,9]]'
 *
 * Given an n x n array of integers matrix, return the minimum sum of any
 * falling path through matrix.
 * 
 * A falling path starts at any element in the first row and chooses the
 * element in the next row that is either directly below or diagonally
 * left/right. Specifically, the next element from position (row, col) will be
 * (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
 * Output: 13
 * Explanation: There are two falling paths with a minimum sum as shown.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: matrix = [[-19,57],[-40,-5]]
 * Output: -59
 * Explanation: The falling path with a minimum sum is shown.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == matrix.length == matrix[i].length
 * 1 <= n <= 100
 * -100 <= matrix[i][j] <= 100
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int minFallingPathSum1(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (j < 0 || j >= n) {
                return INT_MAX;
            }
            if (i == 0) {
                return matrix[0][j];
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            return ans = min({dfs(i - 1, j - 1), dfs(i - 1, j),
                              dfs(i - 1, j + 1)}) +
                         matrix[i][j];
        };
        int ans = INT_MAX;
        for (int j = 0; j < n; j++) {
            ans = min(ans, dfs(n - 1, j));
        }
        return ans;
    }

    // DP递推+记忆化搜索
    int minFallingPathSum2(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> f(n, vector<int>(n + 2, INT_MAX)); // 左右各增一些表示边界
        for (int j = 0; j < n; j++) {
            f[0][j + 1] = matrix[0][j];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                f[i][j + 1] = min({f[i - 1][j], f[i - 1][j + 1],
                                   f[i - 1][j + 2]}) +
                              matrix[i][j];
            }
        }
        return *min_element(f[n - 1].begin() + 1, f[n - 1].begin() + n + 1);
    }

    // DP递推+空间优化
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> f(n + 2, INT_MAX); // 左右各增一些表示边界
        f[0] = f[n + 1] = INT_MAX;
        for (int i = 0; i < n; i++) {
            f[i + 1] = matrix[0][i];
        }
        for (int i = 1; i < n; i++) {
            int pre = f[0];
            for (int j = 0; j < n; j++) {
                int tmp = pre;
                pre = f[j + 1];
                f[j + 1] =
                    min({tmp, f[j + 1], f[j + 2]}) + matrix[i][j];
            }
        }
        return *min_element(f.begin() + 1, f.begin() + n + 1);
    }
};
// @lc code=end

