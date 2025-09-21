/*
 * @lc app=leetcode id=2959 lang=cpp
 *
 * [2959] Number of Possible Sets of Closing Branches
 *
 * https://leetcode.com/problems/number-of-possible-sets-of-closing-branches/description/
 *
 * algorithms
 * Hard (48.77%)
 * Likes:    190
 * Dislikes: 16
 * Total Accepted:    9.6K
 * Total Submissions: 19.5K
 * Testcase Example:  '3\n5\n[[0,1,2],[1,2,10],[0,2,10]]'
 *
 * There is a company with n branches across the country, some of which are
 * connected by roads. Initially, all branches are reachable from each other by
 * traveling some roads.
 * 
 * The company has realized that they are spending an excessive amount of time
 * traveling between their branches. As a result, they have decided to close
 * down some of these branches (possibly none). However, they want to ensure
 * that the remaining branches have a distance of at most maxDistance from each
 * other.
 * 
 * The distance between two branches is the minimum total traveled length
 * needed to reach one branch from another.
 * 
 * You are given integers n, maxDistance, and a 0-indexed 2D array roads, where
 * roads[i] = [ui, vi, wi] represents the undirected road between branches ui
 * and vi with length wi.
 * 
 * Return the number of possible sets of closing branches, so that any branch
 * has a distance of at most maxDistance from any other.
 * 
 * Note that, after closing a branch, the company will no longer have access to
 * any roads connected to it.
 * 
 * Note that, multiple roads are allowed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, maxDistance = 5, roads = [[0,1,2],[1,2,10],[0,2,10]]
 * Output: 5
 * Explanation: The possible sets of closing branches are:
 * - The set [2], after closing, active branches are [0,1] and they are
 * reachable to each other within distance 2.
 * - The set [0,1], after closing, the active branch is [2].
 * - The set [1,2], after closing, the active branch is [0].
 * - The set [0,2], after closing, the active branch is [1].
 * - The set [0,1,2], after closing, there are no active branches.
 * It can be proven, that there are only 5 possible sets of closing branches.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, maxDistance = 5, roads = [[0,1,20],[0,1,10],[1,2,2],[0,2,2]]
 * Output: 7
 * Explanation: The possible sets of closing branches are:
 * - The set [], after closing, active branches are [0,1,2] and they are
 * reachable to each other within distance 4.
 * - The set [0], after closing, active branches are [1,2] and they are
 * reachable to each other within distance 2.
 * - The set [1], after closing, active branches are [0,2] and they are
 * reachable to each other within distance 2.
 * - The set [0,1], after closing, the active branch is [2].
 * - The set [1,2], after closing, the active branch is [0].
 * - The set [0,2], after closing, the active branch is [1].
 * - The set [0,1,2], after closing, there are no active branches.
 * It can be proven, that there are only 7 possible sets of closing branches.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 1, maxDistance = 10, roads = []
 * Output: 2
 * Explanation: The possible sets of closing branches are:
 * - The set [], after closing, the active branch is [0].
 * - The set [0], after closing, there are no active branches.
 * It can be proven, that there are only 2 possible sets of closing
 * branches.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10
 * 1 <= maxDistance <= 10^5
 * 0 <= roads.length <= 1000
 * roads[i].length == 3
 * 0 <= ui, vi <= n - 1
 * ui != vi
 * 1 <= wi <= 1000
 * All branches are reachable from each other by traveling some roads.
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
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        int ans = 0;
        vector<vector<int>> g(n, vector<int>(n, INT_MAX / 2));
        for (auto &e : roads) {
            int x = e[0], y = e[1], w = e[2];
            g[x][y] = min(g[x][y], w);
            g[y][x] = min(g[y][x], w);
        }

        int choose = 0;
        vector<vector<int>> f(n);
        function<void(int)> dfs = [&](int i) -> void {
            if (i == n) {
                ans += check(n, choose, g, f, maxDistance);
                return;
            }
            dfs(i + 1);
            choose |= 1 << i;
            dfs(i + 1);
            choose ^= 1 << i;
        };
        dfs(0);
        return ans;
    }

    bool check(int n, int choose, vector<vector<int>> &g, vector<vector<int>> &f, int maxDistance) {
        for (int i = 0; i < n; i++) {
            if ((choose >> i) & 1) {
                f[i] = g[i];
            }
        }

        // Floyd
        for (int k = 0; k < n; k++) {
            if (((choose >> k) & 1) == 0) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (((choose >> i) & 1) == 0) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    if (((choose >> j) & 1) == 0) {
                        continue;
                    }
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (((choose >> i) & 1) == 0) {
                continue;
            }
            for (int j = 0; j < i; j++) {
                if ((choose >> j) & 1 && f[i][j] > maxDistance) {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end

