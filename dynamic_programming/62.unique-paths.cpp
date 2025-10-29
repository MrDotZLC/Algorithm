/*
 * @lc app=leetcode id=62 lang=cpp
 *
 * [62] Unique Paths
 *
 * https://leetcode.com/problems/unique-paths/description/
 *
 * algorithms
 * Medium (65.90%)
 * Likes:    17958
 * Dislikes: 485
 * Total Accepted:    2.6M
 * Total Submissions: 3.9M
 * Testcase Example:  '3\n7'
 *
 * There is a robot on an m x n grid. The robot is initially located at the
 * top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time.
 * 
 * Given the two integers m and n, return the number of possible unique paths
 * that the robot can take to reach the bottom-right corner.
 * 
 * The test cases are generated so that the answer will be less than or equal
 * to 2 * 10^9.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 3, n = 7
 * Output: 28
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 3, n = 2
 * Output: 3
 * Explanation: From the top-left corner, there are a total of 3 ways to reach
 * the bottom-right corner:
 * 1. Right -> Down -> Down
 * 2. Down -> Down -> Right
 * 3. Down -> Right -> Down
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 100
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归+记忆化
    int uniquePaths1(int m, int n) {
        vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            if (i == 0 && j == 0) {
                return 1;
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            return ans = dfs(i - 1, j) + dfs(i, j - 1);
        };
        return dfs(m - 1, n - 1);
    }

    // DP递推+空间优化
    int uniquePaths2(int m, int n) {
        vector<int> f(n + 1);
        f[1] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                f[j + 1] += f[j];
            }
        }
        return f[n];
    }

    // 数学组合 从m - 1 + n - 1个操作中选出m - 1个向下移动
    // DP递推+空间优化
    int uniquePaths(int m, int n) {
        return comb(n + m - 2, m - 1);
    }
    int comb(int n, int k) {
        k = min(k, n - k);
        long long ans = 1;
        for (int i = 1; i <= k; i++) {
            ans = ans * (n + 1 - i) / i;
        }
        return ans;
    }
};
// @lc code=end

