/*
 * @lc app=leetcode id=576 lang=cpp
 *
 * [576] Out of Boundary Paths
 *
 * https://leetcode.com/problems/out-of-boundary-paths/description/
 *
 * algorithms
 * Medium (48.18%)
 * Likes:    3968
 * Dislikes: 295
 * Total Accepted:    225.1K
 * Total Submissions: 466.1K
 * Testcase Example:  '2\n2\n2\n0\n0'
 *
 * There is an m x n grid with a ball. The ball is initially at the position
 * [startRow, startColumn]. You are allowed to move the ball to one of the four
 * adjacent cells in the grid (possibly out of the grid crossing the grid
 * boundary). You can apply at most maxMove moves to the ball.
 * 
 * Given the five integers m, n, maxMove, startRow, startColumn, return the
 * number of paths to move the ball out of the grid boundary. Since the answer
 * can be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
 * Output: 6
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
 * Output: 12
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 50
 * 0 <= maxMove <= 50
 * 0 <= startRow < m
 * 0 <= startColumn < n
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9+7;
    int dir[4][4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // 记忆化搜索
    int findPaths1(int m, int n, int maxMove, int startRow, int startColumn) {
        vector memo(m, vector(n, vector<int>(maxMove + 1, -1)));
        auto dfs = [&](this auto &&dfs, int i, int j, int k) -> int {
            if (i < 0 || i >= m || j < 0 || j >= n) {
                return 1;
            }
            if (k == 0) {
                return 0;
            }
            int &res = memo[i][j][k];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (auto &d : dir) {
                int ni = i + d[0], nj = j + d[1];
                res += dfs(ni, nj, k - 1);
                res %= MOD;
            }
            return res;
        };
        return dfs(startRow, startColumn, maxMove);
    }

    // DP
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        vector f(m + 2,
                 vector(n + 2, vector<long long>(maxMove + 1)));
        // 初始化边界值
        for (int i = 0; i <= m + 1; i++) {
            f[i][0][0] = 1;
            f[i][n + 1][0] = 1;
        }
        for (int j = 0; j <= n + 1; j++) {
            f[0][j][0] = 1;
            f[m + 1][j][0] = 1;
        }
        for (int k = 1; k <= maxMove; k++) {
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    f[i][j][k] =
                        (f[i - 1][j][k - 1] + f[i + 1][j][k - 1] +
                         f[i][j - 1][k - 1] + f[i][j + 1][k - 1]) %
                        MOD;
                }
            }
        }
        return (int) (reduce(f[startRow + 1][startColumn + 1].begin(),
                             f[startRow + 1][startColumn + 1].end(),
                             0LL) %
                      MOD);
    }
};
// @lc code=end

