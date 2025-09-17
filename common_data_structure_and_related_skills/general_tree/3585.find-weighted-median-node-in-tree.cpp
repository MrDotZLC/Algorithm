/*
 * @lc app=leetcode id=3585 lang=cpp
 *
 * [3585] Find Weighted Median Node in Tree
 *
 * https://leetcode.com/problems/find-weighted-median-node-in-tree/description/
 *
 * algorithms
 * Hard (22.84%)
 * Likes:    61
 * Dislikes: 5
 * Total Accepted:    3.6K
 * Total Submissions: 15.2K
 * Testcase Example:  '2\n[[0,1,7]]\n[[1,0],[0,1]]'
 *
 * You are given an integer n and an undirected, weighted tree rooted at node 0
 * with n nodes numbered from 0 to n - 1. This is represented by a 2D array
 * edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from
 * node ui to vi with weight wi.
 * 
 * The weighted median node is defined as the first node x on the path from ui
 * to vi such that the sum of edge weights from ui to x is greater than or
 * equal to half of the total path weight.
 * 
 * You are given a 2D integer array queries. For each queries[j] = [uj, vj],
 * determine the weighted median node along the path from uj to vj.
 * 
 * Return an array ans, where ans[j] is the node index of the weighted median
 * for queries[j].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
 * 
 * Output: [0,1]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * 
 * 
 * Query
 * Path
 * Edge
 * Weights
 * Total
 * Path
 * Weight
 * Half
 * Explanation
 * Answer
 * 
 * 
 * 
 * 
 * [1, 0]
 * 1 → 0
 * [7]
 * 7
 * 3.5
 * Sum from 1 → 0 = 7 >= 3.5, median is node 0.
 * 0
 * 
 * 
 * [0, 1]
 * 0 → 1
 * [7]
 * 7
 * 3.5
 * Sum from 0 → 1 = 7 >= 3.5, median is node 1.
 * 1
 * 
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, edges = [[0,1,2],[2,0,4]], queries = [[0,1],[2,0],[1,2]]
 * 
 * Output: [1,0,2]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * 
 * 
 * Query
 * Path
 * Edge
 * Weights
 * Total
 * Path
 * Weight
 * Half
 * Explanation
 * Answer
 * 
 * 
 * 
 * 
 * [0, 1]
 * 0 → 1
 * [2]
 * 2
 * 1
 * Sum from 0 → 1 = 2 >= 1, median is node 1.
 * 1
 * 
 * 
 * [2, 0]
 * 2 → 0
 * [4]
 * 4
 * 2
 * Sum from 2 → 0 = 4 >= 2, median is node 0.
 * 0
 * 
 * 
 * [1, 2]
 * 1 → 0 → 2
 * [2, 4]
 * 6
 * 3
 * Sum from 1 → 0 = 2 < 3.
 * Sum from 1 → 2 = 2 + 4 = 6 >= 3, median is node 2.
 * 2
 * 
 * 
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 5, edges = [[0,1,2],[0,2,5],[1,3,1],[2,4,3]], queries =
 * [[3,4],[1,2]]
 * 
 * Output: [2,2]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * 
 * 
 * Query
 * Path
 * Edge
 * Weights
 * Total
 * Path
 * Weight
 * Half
 * Explanation
 * Answer
 * 
 * 
 * 
 * 
 * [3, 4]
 * 3 → 1 → 0 → 2 → 4
 * [1, 2, 5, 3]
 * 11
 * 5.5
 * Sum from 3 → 1 = 1 < 5.5.
 * Sum from 3 → 0 = 1 + 2 = 3 < 5.5.
 * Sum from 3 → 2 = 1 + 2 + 5 = 8 >= 5.5, median is node 2.
 * 2
 * 
 * 
 * [1, 2]
 * 1 → 0 → 2
 * [2, 5]
 * 7
 * 3.5
 * 
 * Sum from 1 → 0 = 2 < 3.5.
 * Sum from 1 → 2 = 2 + 5 = 7 >= 3.5, median is node
 * 2.
 * 
 * 2
 * 
 * 
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^5
 * edges.length == n - 1
 * edges[i] == [ui, vi, wi]
 * 0 <= ui, vi < n
 * 1 <= wi <= 10^9
 * 1 <= queries.length <= 10^5
 * queries[j] == [uj, vj]
 * 0 <= uj, vj < n
 * The input is generated such that edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <cmath>
using namespace std;
// @lc code=start
class LcaBinaryLifting {
public:
    vector<int> depth;
    vector<long long> dis;
    vector<vector<int>> pa;

    LcaBinaryLifting(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        int m = bit_width((unsigned) n); // n 的二进制长度
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }

        depth.resize(n);
        dis.resize(n);
        pa.resize(n, vector<int>(m, -1));

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (auto& [y, w] : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dis[y] = dis[x] + w;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (int p = pa[x][i]; p != -1) {
                    pa[x][i + 1] = pa[p][i];
                }
            }
        }
    }

    int get_kth_ancestor(int node, int k) {
        for (; k; k &= k - 1) {
            node = pa[node][countr_zero((unsigned) k)];
        }
        return node;
    }

    // 返回 x 和 y 的最近公共祖先（节点编号从 0 开始）
    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) {
            swap(x, y);
        }
        y = get_kth_ancestor(y, depth[y] - depth[x]); // 使 y 和 x 在同一深度
        if (y == x) {
            return x;
        }
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py; // 同时往上跳 2^i 步
            }
        }
        return pa[x][0];
    }

    // 返回 x 到 y 的距离（最短路长度）
    long long get_dis(int x, int y) {
        return dis[x] + dis[y] - dis[get_lca(x, y)] * 2;
    }

    // 从 x 往上跳【至多】d 距离，返回最远能到达的节点
    int upto_dis(int x, long long d) {
        long long dx = dis[x];
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int p = pa[x][i];
            if (p != -1 && dx - dis[p] <= d) {
                x = p;
            }
        }
        return x;
    };
};
class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        LcaBinaryLifting g(edges);

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            int x = q[0], y = q[1];
            if (x == y) {
                ans.push_back(x);
                continue;
            }
            int lca = g.get_lca(x, y);
            long long dis_xy =  g.dis[x] + g.dis[y] - 2 * g.dis[lca];
            long long half = (dis_xy + 1) / 2;
            int res;
            if (g.dis[x] - g.dis[lca] >= half) {
                int t = g.upto_dis(x, half - 1);
                res = g.pa[t][0];
            } else {
                res = g.upto_dis(y, dis_xy - half); 
            }
            ans.push_back(res);
        }
        return ans;
    }
};
// @lc code=end

