/*
 * @lc app=leetcode id=1617 lang=cpp
 *
 * [1617] Count Subtrees With Max Distance Between Cities
 *
 * https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/description/
 *
 * algorithms
 * Hard (66.83%)
 * Likes:    566
 * Dislikes: 44
 * Total Accepted:    13.8K
 * Total Submissions: 20.7K
 * Testcase Example:  '4\n[[1,2],[2,3],[2,4]]'
 *
 * There are n cities numbered from 1 to n. You are given an array edges of
 * size n-1, where edges[i] = [ui, vi] represents a bidirectional edge between
 * cities ui and vi. There exists a unique path between each pair of cities. In
 * other words, the cities form a tree.
 * 
 * A subtree is a subset of cities where every city is reachable from every
 * other city in the subset, where the path between each pair passes through
 * only the cities from the subset. Two subtrees are different if there is a
 * city in one subtree that is not present in the other.
 * 
 * For each d from 1 to n-1, find the number of subtrees in which the maximum
 * distance between any two cities in the subtree is equal to d.
 * 
 * Return an array of size n-1 where the d^th element (1-indexed) is the number
 * of subtrees in which the maximum distance between any two cities is equal to
 * d.
 * 
 * Notice that the distance between the two cities is the number of edges in
 * the path between them.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: n = 4, edges = [[1,2],[2,3],[2,4]]
 * Output: [3,4,0]
 * Explanation:
 * The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
 * The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max
 * distance of 2.
 * No subtree has two nodes where the max distance between them is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, edges = [[1,2]]
 * Output: [1]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, edges = [[1,2],[2,3]]
 * Output: [2,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 15
 * edges.length == n-1
 * edges[i].length == 2
 * 1 <= ui, vi <= n
 * All pairs (ui, vi) are distinct.
 * 
 */
#include <vector>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // binary + backtracking
    vector<int> countSubgraphsForEachDiameter1(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> ans(n - 1);
        for (int mask = 3; mask < 1 << n; ++mask) {
            if ((mask & (mask - 1)) == 0) { // 至少有2个点
                continue;
            }
            int vis = 0, diameter = 0;
            function<int(int)> dfs = [&](int x) -> int {
                vis |= 1 << x;
                int mx_l = 0;
                for (int y : g[x]) {
                    if (mask & (1 << y) && (vis & (1 << y)) == 0) {
                        int sub_ml = dfs(y) + 1;
                        diameter = max(diameter, mx_l + sub_ml);
                        mx_l = max(mx_l, sub_ml);
                    }
                }
                return mx_l;
            };
            dfs(__builtin_ctz(mask));
            if (vis == mask) {
                ans[diameter - 1]++;
            }
        }
        return ans;
    }

    // 枚举直径端点 + 子树方案的乘法原理
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<vector<int>> dis(n, vector<int>(n));
        function<void(int, int, int)> dfs = [&](int i, int x,
                                                int parent) -> void {
            for (int y : g[x]) {
                if (y != parent) {
                    dis[i][y] = dis[i][x] + 1;
                    dfs(i, y, x);
                }
            }
        };
        for (int i = 0; i < n; i++) {
            dfs(i, i, -1);
        }

        vector<int> ans(n - 1);
        auto dfs2 = [&](this auto &&dfs2, int i, int j, int d, int x,
                        int parent) -> int {
            int cnt = 1;  // 选
            for (int y : g[x]) {
                if (y != parent &&
                    (dis[i][y] < d || dis[i][y] == d && y > j) &&
                    (dis[j][y] < d || dis[j][y] == d && y > i)) {
                    cnt *= dfs2(i, j, d, y, x);
                }
            }
            if (dis[i][x] + dis[j][x] > d) {  // 不是必选点
                cnt++;                        // 不选
            }
            return cnt;
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans[dis[i][j] - 1] += dfs2(i, j, dis[i][j], i, -1);
            }
        }
        return ans;
    }
};
// @lc code=end

