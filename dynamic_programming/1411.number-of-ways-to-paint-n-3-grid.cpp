/*
 * @lc app=leetcode id=1411 lang=cpp
 *
 * [1411] Number of Ways to Paint N × 3 Grid
 *
 * https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/description/
 *
 * algorithms
 * Hard (65.12%)
 * Likes:    1140
 * Dislikes: 56
 * Total Accepted:    42.2K
 * Total Submissions: 64.5K
 * Testcase Example:  '1'
 *
 * You have a grid of size n x 3 and you want to paint each cell of the grid
 * with exactly one of the three colors: Red, Yellow, or Green while making
 * sure that no two adjacent cells have the same color (i.e., no two cells that
 * share vertical or horizontal sides have the same color).
 * 
 * Given n the number of rows of the grid, return the number of ways you can
 * paint this grid. As the answer may grow large, the answer must be computed
 * modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1
 * Output: 12
 * Explanation: There are 12 possible way to paint the grid as shown.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5000
 * Output: 30228214
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == grid.length
 * 1 <= n <= 5000
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
/**
 * @brief 
 * DP
 * 一列数据可用三进制表示
 * 预处理[0,3^n-1]，得到相邻颜色不同的方案集合valid
 * 计算每一行相邻元素都与valid不同的nxt
 * 枚举每一列的所有可能
 * f(i,j)表示对于n*i的网格，第i+1列涂色为valid[j]时的方案数
 * f(i,j)=sum{f(i-1,k)}, k∈nxt[j]
 * 
 * 边界：i=0,f=1
 * 入口：f(n-1,j), j∈[0,size(valid))
 */
class Solution {
public:
    const int MOD = 1e9+7;
    // 记忆化递归
    int numOfWays(int n) {
        vector<long long> pow3(4);
        pow3[0] = 1;
        for (int i = 1; i <= 3; i++) {
            pow3[i] = pow3[i - 1] * 3;
        }

        vector<int> valid;
        for (int color = 0; color < pow3[3]; color++) {
            bool ok = true;
            for (int i = 1; i < 3; i++) {
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
                for (int k = 0; k < 3; k++) {
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
};
// @lc code=end

