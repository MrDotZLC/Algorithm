/*
 * @lc app=leetcode id=3219 lang=cpp
 *
 * [3219] Minimum Cost for Cutting Cake II
 *
 * https://leetcode.com/problems/minimum-cost-for-cutting-cake-ii/description/
 *
 * algorithms
 * Hard (54.70%)
 * Likes:    123
 * Dislikes: 18
 * Total Accepted:    23.6K
 * Total Submissions: 42.8K
 * Testcase Example:  '3\n2\n[1,3]\n[5]'
 *
 * There is an m x n cake that needs to be cut into 1 x 1 pieces.
 * 
 * You are given integers m, n, and two arrays:
 * 
 * 
 * horizontalCut of size m - 1, where horizontalCut[i] represents the cost to
 * cut along the horizontal line i.
 * verticalCut of size n - 1, where verticalCut[j] represents the cost to cut
 * along the vertical line j.
 * 
 * 
 * In one operation, you can choose any piece of cake that is not yet a 1 x 1
 * square and perform one of the following cuts:
 * 
 * 
 * Cut along a horizontal line i at a cost of horizontalCut[i].
 * Cut along a vertical line j at a cost of verticalCut[j].
 * 
 * 
 * After the cut, the piece of cake is divided into two distinct pieces.
 * 
 * The cost of a cut depends only on the initial cost of the line and does not
 * change.
 * 
 * Return the minimum total cost to cut the entire cake into 1 x 1 pieces.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 3, n = 2, horizontalCut = [1,3], verticalCut = [5]
 * 
 * Output: 13
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Perform a cut on the vertical line 0 with cost 5, current total cost is
 * 5.
 * Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
 * Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
 * Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
 * Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
 * 
 * 
 * The total cost is 5 + 1 + 1 + 3 + 3 = 13.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 2, n = 2, horizontalCut = [7], verticalCut = [4]
 * 
 * Output: 15
 * 
 * Explanation:
 * 
 * 
 * Perform a cut on the horizontal line 0 with cost 7.
 * Perform a cut on the vertical line 0 on 1 x 2 subgrid with cost 4.
 * Perform a cut on the vertical line 0 on 1 x 2 subgrid with cost 4.
 * 
 * 
 * The total cost is 7 + 4 + 4 = 15.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 10^5
 * horizontalCut.length == m - 1
 * verticalCut.length == n - 1
 * 1 <= horizontalCut[i], verticalCut[i] <= 10^3
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
    // 记忆化搜索
    long long minimumCost1(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        vector memo(m + 1, vector(n + 1, vector(m + 1, vector<int>(n + 1))));
        auto dfs = [&](this auto &&dfs, int sr, int sc, int er, int ec) -> int {
            if (sr + 1 == er && sc + 1 == ec) {
                return 0;
            }
            int &res = memo[sr][sc][er][ec];
            if (res) {
                return res;
            }
            res = INT_MAX / 2;
            for (int i = sr + 1; i <= er - 1; i++) {
                res =
                    min(res, dfs(sr, sc, i, ec) + dfs(i, sc, er, ec) +
                                 horizontalCut[i - 1]);
            }
            for (int i = sc + 1; i <= ec - 1; i++) {
                res =
                    min(res, dfs(sr, sc, er, i) + dfs(sr, i, er, ec) +
                                 verticalCut[i - 1]);
            }
            return res;
        };
        return dfs(0 ,0, m, n);
    }

    // 最小生成树+贪心+双指针
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        ranges::sort(horizontalCut);
        ranges::sort(verticalCut);
        long long ans = 0;
        int i = 0, j = 0;
        while (i < m - 1 || j < n - 1) {
            if (j == n - 1 || i < m - 1 && horizontalCut[i] < verticalCut[j]) {
                ans += horizontalCut[i++] * (n - j);
            } else {
                ans += verticalCut[j++] * (m - i);
            }
        }
        return ans;
    }
};
// @lc code=end

