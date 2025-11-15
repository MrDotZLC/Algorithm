/*
 * @lc app=leetcode id=96 lang=cpp
 *
 * [96] Unique Binary Search Trees
 *
 * https://leetcode.com/problems/unique-binary-search-trees/description/
 *
 * algorithms
 * Medium (62.55%)
 * Likes:    10881
 * Dislikes: 439
 * Total Accepted:    813.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '3'
 *
 * Given an integer n, return the number of structurally unique BST's (binary
 * search trees) which has exactly n nodes of unique values from 1 to n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3
 * Output: 5
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 19
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
/**
 * 方法一：记忆化搜索/DP（二维）
 * f(i,j)表示[i,j]区间内的方案数
 * f(i,j)=sum{f(i,k-1)*f(k+1,j)}, k∈[i,j]
 * 边界：i>=j时，f(i,j)=1
 * 入口：f(0,n-1)
 * 
 * 方法二：记忆化搜索/DP（一维）
 * f(i)表示长度为i的方案数
 * f(i)=sum{f(0,k-1)*f(k+1,n-1)}
 * 边界：k-1<=0或k+1>=n-1时，f=1
 * 入口：f(n)
 * 
 * 方法三：数学计算
 * 推导看不懂，不写了
 */
class Solution {
public:
    // 方法一：二维记忆化搜索
    int numTrees1(int n) {
        vector memo(n, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i >= j) {
                return 1;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int k = i; k <= j; k++) {
                res += dfs(i, k - 1) * dfs(k + 1, j);
            }
            return res;
        };
        return dfs(0, n - 1);
    }

    // 方法二：一维DP
    int numTrees(int n) {
        vector<int> f(n + 1);
        f[0] = 1; // 0个数，方案为1
        f[1] = 1; // 1个数，方案为1
        for (int i = 2; i <= n; i++) { // 个数多的以来个数小的结果
            // n个节点的方案数 = sum{k-1个节点的方案数 * n-k个节点的方案数}
            for (int k = 1; k <= i; k++) { // k为子树的根节点
                f[i] += f[k - 1] * f[i - k];
            }
        }
        return f[n];
    }
};
// @lc code=end

