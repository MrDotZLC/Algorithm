/*
 * @lc app=leetcode id=3332 lang=cpp
 *
 * [3332] Maximum Points Tourist Can Earn
 *
 * https://leetcode.com/problems/maximum-points-tourist-can-earn/description/
 *
 * algorithms
 * Medium (46.47%)
 * Likes:    89
 * Dislikes: 15
 * Total Accepted:    14.4K
 * Total Submissions: 30.6K
 * Testcase Example:  '2\n1\n[[2,3]]\n[[0,2],[1,0]]'
 *
 * You are given two integers, n and k, along with two 2D integer arrays,
 * stayScore and travelScore.
 * 
 * A tourist is visiting a country with n cities, where each city is directly
 * connected to every other city. The tourist's journey consists of exactly k
 * 0-indexed days, and they can choose any city as their starting point.
 * 
 * Each day, the tourist has two choices:
 * 
 * 
 * Stay in the current city: If the tourist stays in their current city curr
 * during day i, they will earn stayScore[i][curr] points.
 * Move to another city: If the tourist moves from their current city curr to
 * city dest, they will earn travelScore[curr][dest] points.
 * 
 * 
 * Return the maximum possible points the tourist can earn.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The tourist earns the maximum number of points by starting in city 1 and
 * staying in that city.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, k = 2, stayScore = [[3,4,2],[2,1,2]], travelScore =
 * [[0,2,1],[2,0,4],[3,2,0]]
 * 
 * Output: 8
 * 
 * Explanation:
 * 
 * The tourist earns the maximum number of points by starting in city 1,
 * staying in that city on day 0, and traveling to city 2 on day 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 200
 * 1 <= k <= 200
 * n == travelScore.length == travelScore[i].length == stayScore[i].length
 * k == stayScore.length
 * 1 <= stayScore[i][j] <= 100
 * 0 <= travelScore[i][j] <= 100
 * travelScore[i][i] == 0
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    int maxScore1(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<vector<int>> memo(k, vector<int>(n));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i == k) {
                return 0;
            }
            int &res = memo[i][j];
            if (res) {
                return res;
            }
            // 停留在j城市
            res = dfs(i + 1, j) + stayScore[i][j];
            // 去往其他城市
            for (int d = 0; d < travelScore[j].size(); d++) {
                res = max(res, dfs(i + 1, d) + travelScore[j][d]);
            }
            return res;
        };
        int ans = 0;
        for (int j = 0; j < n; j++) {
            ans = max(ans, dfs(0, j));
        }
        return ans;
    }

    // DP（逆向枚举）+空间优化：第i到第k-1天在j城市的最大收益
    int maxScore2(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<int> f(n);
        for (int i = k - 1; i >= 0; i--) {
            vector<int> prev = f;
            for (int j = 0; j < n; j++) {
                f[j] = prev[j] + stayScore[i][j];
                for (int d = 0; d < travelScore.size(); d++) {
                    f[j] = max(f[j], prev[d] + travelScore[j][d]);
                }
            }
        }
        return ranges::max(f);
    }

    // DP（正向枚举）+空间优化：第0到第i天在j城市的最大收益
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        int ans = 0;
        vector<vector<int>> f(2, vector<int>(n));
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < n; j++) {
                for (int other = 0; other < n; other++) {
                    if (other == j) {
                        f[i % 2][j] = max(f[i % 2][j], f[(i - 1) % 2][j] + stayScore[i - 1][j]);
                    } else {
                        f[i % 2][j] = max(f[i % 2][j], f[(i - 1) % 2][other] + travelScore[other][j]);
                    }
                }
                ans = max(ans, f[i % 2][j]);
            }
        }
        return ans;
    }
};
// @lc code=end

