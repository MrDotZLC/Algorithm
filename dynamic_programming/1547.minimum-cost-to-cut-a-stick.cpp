/*
 * @lc app=leetcode id=1547 lang=cpp
 *
 * [1547] Minimum Cost to Cut a Stick
 *
 * https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/
 *
 * algorithms
 * Hard (62.21%)
 * Likes:    4726
 * Dislikes: 155
 * Total Accepted:    206.3K
 * Total Submissions: 329.8K
 * Testcase Example:  '7\n[1,3,4,5]'
 *
 * Given a wooden stick of length n units. The stick is labelled from 0 to n.
 * For example, a stick of length 6 is labelled as follows:
 * 
 * Given an integer array cuts where cuts[i] denotes a position you should
 * perform a cut at.
 * 
 * You should perform the cuts in order, you can change the order of the cuts
 * as you wish.
 * 
 * The cost of one cut is the length of the stick to be cut, the total cost is
 * the sum of costs of all cuts. When you cut a stick, it will be split into
 * two smaller sticks (i.e. the sum of their lengths is the length of the stick
 * before the cut). Please refer to the first example for a better
 * explanation.
 * 
 * Return the minimum total cost of the cuts.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 7, cuts = [1,3,4,5]
 * Output: 16
 * Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the
 * following scenario:
 * 
 * The first cut is done to a rod of length 7 so the cost is 7. The second cut
 * is done to a rod of length 6 (i.e. the second part of the first cut), the
 * third is done to a rod of length 4 and the last cut is to a rod of length 3.
 * The total cost is 7 + 6 + 4 + 3 = 20.
 * Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario
 * with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).
 * 
 * Example 2:
 * 
 * 
 * Input: n = 9, cuts = [5,6,1,4,2]
 * Output: 22
 * Explanation: If you try the given cuts ordering the cost will be 25.
 * There are much ordering with total cost <= 25, for example, the order [4, 6,
 * 5, 2, 1] has total cost = 22 which is the minimum possible.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^6
 * 1 <= cuts.length <= min(n - 1, 100)
 * 1 <= cuts[i] <= n - 1
 * All the integers in cuts array are distinct.
 * 
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
// @lc code=start
/**
 * 记忆化递归/DP
 * f(i,j)表示要分割木棒的左右端点下标
 * f(i,j)=min{f(i,k)+f(k,j)+j-i}, k∈cuts
 * 边界：i>j时，f=0
 * 入口：f(0,n) 
 */
class Solution {
public:
    // 记忆化搜索
    int minCost1(int n, vector<int>& cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        ranges::sort(cuts);

        int m = cuts.size();
        vector<vector<int>> memo(m, vector<int>(m));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i + 1 == j) {
                return 0;
            }
            int &res = memo[i][j];
            if (res) {
                return res;
            }
            res = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                res = min(res, dfs(i, k) + dfs(k, j));
            }
            return res += cuts[j] - cuts[i];
        };
        return dfs(0, m - 1);
    }

    // DP
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        ranges::sort(cuts);

        int m = cuts.size();
        vector<vector<int>> f(m, vector<int>(m));
        for (int i = m - 1; i >= 0; i--) {
            for (int j = i + 2; j < m; j++) {
                f[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                }
                f[i][j] += cuts[j] - cuts[i];
            }
        }
        return f[0][m - 1];
    }
};
// @lc code=end

