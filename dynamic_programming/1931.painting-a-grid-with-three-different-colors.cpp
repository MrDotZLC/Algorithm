/*
 * @lc app=leetcode id=1931 lang=cpp
 *
 * [1931] Painting a Grid With Three Different Colors
 *
 * https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description/
 *
 * algorithms
 * Hard (78.34%)
 * Likes:    894
 * Dislikes: 57
 * Total Accepted:    72.6K
 * Total Submissions: 93.2K
 * Testcase Example:  '1\n1'
 *
 * You are given two integers m and n. Consider an m x n grid where each cell
 * is initially white. You can paint each cell red, green, or blue. All cells
 * must be painted.
 * 
 * Return the number of ways to color the grid with no two adjacent cells
 * having the same color. Since the answer can be very large, return it modulo
 * 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 1, n = 1
 * Output: 3
 * Explanation: The three possible colorings are shown in the image above.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 1, n = 2
 * Output: 6
 * Explanation: The six possible colorings are shown in the image above.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: m = 5, n = 5
 * Output: 580986
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m <= 5
 * 1 <= n <= 1000
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9+7;
    // 记忆化递归
    int colorTheGrid1(int m, int n) {
        vector<int> pow3(m + 1);
        pow3[0] = 1;
        for (int i = 1; i <= m; i++) {
            pow3[i] = pow3[i - 1] * 3;
        }
        vector<int> valid;
        for (int color = 0; color < pow3[m];  color++) {
            bool ok = true;
            for (int i = 1; i < m; i++) {
                if (color / pow3[i] % 3 == color / pow3[i - 1] % 3) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                valid.push_back(color);
            }
        }

        int nv = valid.size();
        vector<vector<int>> nxt(nv);
        for (int i = 0; i < nv; i++) {
            for (int j = 0; j < nv; j++) {
                bool ok = true;
                for (int k = 0; k < m; k++) {
                    if (valid[i] / pow3[k] % 3 == valid[j] / pow3[k] % 3) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    nxt[i].push_back(j);
                }
            }
        }

        vector<vector<int>> memo(n, vector<int>(nv, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i == 0) {
                return 1;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int k : nxt[j]) {
                res = (res + dfs(dfs, i - 1, k)) % MOD;
            }
            return res;
        };
        long long ans = 0;
        for (int j = 0; j < nv; j++) {
            ans += dfs(dfs, n - 1, j);
        }
        return ans % MOD;
    }

    // DP
    int colorTheGrid(int m, int n) {
        vector<int> pow3(m + 1);
        pow3[0] = 1;
        for (int i = 1; i <= m; i++) {
            pow3[i] = pow3[i - 1] * 3;
        }

        vector<int> valid;
        for (int color = 0; color < pow3[m];  color++) {
            bool ok = true;
            for (int i = 1; i < m; i++) {
                if (color / pow3[i] % 3 == color / pow3[i - 1] % 3) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                valid.push_back(color);
            }
        }

        int nv = valid.size();
        vector<vector<int>> nxt(nv);
        for (int i = 0; i < nv; i++) {
            for (int j = 0; j < nv; j++) {
                bool ok = true;
                for (int k = 0; k < m; k++) {
                    if (valid[i] / pow3[k] % 3 == valid[j] / pow3[k] % 3) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    nxt[i].push_back(j);
                }
            }
        }

        vector f(n, vector<int>(nv));
        ranges::fill(f[0], 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < nv; j++) {
                for (int k : nxt[j]) {
                    f[i][j] = (f[i][j] + f[i - 1][k]) % MOD;
                }
            }
        }

        long long ans = 0;
        for (int j = 0; j < nv; j++) {
            ans += f[n - 1][j];
        }
        return ans % MOD;
    }
};
// @lc code=end

