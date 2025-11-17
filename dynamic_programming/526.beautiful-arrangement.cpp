/*
 * @lc app=leetcode id=526 lang=cpp
 *
 * [526] Beautiful Arrangement
 *
 * https://leetcode.com/problems/beautiful-arrangement/description/
 *
 * algorithms
 * Medium (64.58%)
 * Likes:    3378
 * Dislikes: 389
 * Total Accepted:    208K
 * Total Submissions: 321.7K
 * Testcase Example:  '2'
 *
 * Suppose you have n integers labeled 1 through n. A permutation of those n
 * integers perm (1-indexed) is considered a beautiful arrangement if for every
 * i (1 <= i <= n), either of the following is true:
 * 
 * 
 * perm[i] is divisible by i.
 * i is divisible by perm[i].
 * 
 * 
 * Given an integer n, return the number of the beautiful arrangements that you
 * can construct.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2
 * Output: 2
 * Explanation: 
 * The first beautiful arrangement is [1,2]:
 * ⁠   - perm[1] = 1 is divisible by i = 1
 * ⁠   - perm[2] = 2 is divisible by i = 2
 * The second beautiful arrangement is [2,1]:
 * ⁠   - perm[1] = 2 is divisible by i = 1
 * ⁠   - i = 2 is divisible by perm[2] = 1
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
 * 1 <= n <= 15
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
/**
 * 记忆化递归/DP
 * 全排列的递归
 * f(i)表示i的二进制中，第j位是1表示第j个数已经选中，0则还未被选
 * f(i)=sum{f(i|(1<<j-1))}, j∈[1,n]&&(i>>(j-1))^0=1
 * 边界：i=(1<<n)-1，f=1，即所有元素都被选了
 * 入口：i=0，即所有元素都未被选
 */
class Solution {
public:
    // 记忆化搜索
    int countArrangement1(int n) {
        vector<int> memo(1 << n, -1);
        auto dfs = [&](auto &dfs, int prem) -> int {
            if (prem == (1 << n) - 1) {
                return 1;
            }
            int &res = memo[prem];
            if (res != -1) {
                return res;
            }
            res = 0;
            // 下标i = 集合元素个数+1
            int i = popcount((unsigned) prem) + 1;
            // 枚举第j个数
            for (int j = 1; j <= n; j++) {
                // 第j个数没被选，且下标i被j整除或被整除
                if ((prem >> j - 1 & 1) == 0 && (i % j == 0 || j % i == 0)) {
                    res += dfs(dfs, prem | (1 << j - 1));
                }
            }
            return res;
        };
        return dfs(dfs, 0);
    }

    // DP
    int countArrangement(int n) {
        vector<int> f(1 << n);
        f.back() = 1;
        for (int prem = (1 << n) - 2; prem >= 0; prem--) {
            int i = __builtin_popcount((unsigned) prem) + 1;
            for (int j = 1; j <= n; j++) {
                if ((prem >> j - 1 & 1) == 0 &&
                    (i % j == 0 || j % i == 0)) {
                    f[prem] += f[prem | (1 << j - 1)];
                }
            }
        }
        return f[0];
    }
};
// @lc code=end

