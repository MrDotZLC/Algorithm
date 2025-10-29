/*
 * @lc app=leetcode id=3393 lang=cpp
 *
 * [3393] Count Paths With the Given XOR Value
 *
 * https://leetcode.com/problems/count-paths-with-the-given-xor-value/description/
 *
 * algorithms
 * Medium (39.84%)
 * Likes:    83
 * Dislikes: 6
 * Total Accepted:    20.2K
 * Total Submissions: 50.2K
 * Testcase Example:  '[[2,1,5],[7,10,0],[12,6,4]]\n11'
 *
 * You are given a 2D integer array grid with size m x n. You are also given an
 * integer k.
 * 
 * Your task is to calculate the number of paths you can take from the top-left
 * cell (0, 0) to the bottom-right cell (m - 1, n - 1) satisfying the following
 * constraints:
 * 
 * 
 * You can either move to the right or down. Formally, from the cell (i, j) you
 * may move to the cell (i, j + 1) or to the cell (i + 1, j) if the target cell
 * exists.
 * The XOR of all the numbers on the path must be equal to k.
 * 
 * 
 * Return the total number of such paths.
 * 
 * Since the answer can be very large, return the result modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[2, 1, 5], [7, 10, 0], [12, 6, 4]], k = 11
 * 
 * Output: 3
 * 
 * Explanation: 
 * 
 * The 3 paths are:
 * 
 * 
 * (0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2)
 * (0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
 * (0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2)
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[1, 3, 3, 3], [0, 3, 3, 2], [3, 0, 1, 1]], k = 2
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * The 5 paths are:
 * 
 * 
 * (0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2) → (2, 3)
 * (0, 0) → (1, 0) → (1, 1) → (2, 1) → (2, 2) → (2, 3)
 * (0, 0) → (1, 0) → (1, 1) → (1, 2) → (1, 3) → (2, 3)
 * (0, 0) → (0, 1) → (1, 1) → (1, 2) → (2, 2) → (2, 3)
 * (0, 0) → (0, 1) → (0, 2) → (1, 2) → (2, 2) → (2, 3)
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[1, 1, 1, 2], [3, 0, 3, 2], [3, 0, 2, 2]], k = 10
 * 
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m == grid.length <= 300
 * 1 <= n == grid[r].length <= 300
 * 0 <= grid[r][c] < 16
 * 0 <= k < 16
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
    int countPathsWithXorValue1(vector<vector<int>>& grid, int k) {
        const int MOD = 1e9 + 7;
        int mx = 0;
        for (auto &r : grid) {
            mx = max(mx, ranges::max(r));
        }
        unsigned w = bit_width((unsigned)mx);
        int u = 1 << w;
        if (k >= u) {
            return 0;
        }

        int m = grid.size(), n = grid[0].size();
        vector memo(m, vector(n, vector<int>(u, -1))); 
        auto dfs = [&](this auto &&dfs, int i, int j, int x) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            int val = grid[i][j];
            if (i == 0 && j == 0) {
                return x== val;
            }
            int &ans = memo[i][j][x];
            if (ans != -1) {
                return ans;
            }
            return ans = (dfs(i, j - 1, x ^ val) + dfs(i - 1, j, x ^ val)) % MOD;
        };
        return dfs(m - 1, n - 1, k);
    }

    // DP递推
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        const int MOD = 1e9 + 7;
        int mx = 0;
        for (auto &r : grid) {
            mx = max(mx, ranges::max(r));
        }
        unsigned w = bit_width((unsigned)mx);
        int u = 1 << w;
        if (k >= u) {
            return 0;
        }

        int m = grid.size(), n = grid[0].size();
        vector f(m + 1, vector(n + 1, vector<int>(u)));
        f[0][1][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                for (int x = 0; x < u; x++) {
                    f[i + 1][j + 1][x] = (f[i + 1][j][x ^ val] + f[i][j + 1][x ^ val]) % MOD;
                }
            }
        }
        return f[m][n][k];
    }
};
// @lc code=end

