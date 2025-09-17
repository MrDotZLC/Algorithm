/*
 * @lc app=leetcode id=3553 lang=cpp
 *
 * [3553] Minimum Weighted Subgraph With the Required Paths II
 *
 * https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/description/
 *
 * algorithms
 * Hard (49.53%)
 * Likes:    46
 * Dislikes: 4
 * Total Accepted:    4K
 * Total Submissions: 8.2K
 * Testcase Example:  '[[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]]\n[[2,3,4],[0,2,5]]'
 *
 * You are given an undirected weighted tree with n nodes, numbered from 0 to n
 * - 1. It is represented by a 2D integer array edges of length n - 1, where
 * edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and
 * vi with weight wi.​
 * 
 * Additionally, you are given a 2D integer array queries, where queries[j] =
 * [src1j, src2j, destj].
 * 
 * Return an array answer of length equal to queries.length, where answer[j] is
 * the minimum total weight of a subtree such that it is possible to reach
 * destj from both src1j and src2j using edges in this subtree.
 * 
 * A subtree here is any connected subset of nodes and edges of the original
 * tree forming a valid tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries =
 * [[2,3,4],[0,2,5]]
 * 
 * Output: [12,11]
 * 
 * Explanation:
 * 
 * The blue edges represent one of the subtrees that yield the optimal
 * answer.
 * 
 * 
 * 
 * 
 * 
 * answer[0]: The total weight of the selected subtree that ensures a path from
 * src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
 * 
 * 
 * answer[1]: The total weight of the selected subtree that ensures a path from
 * src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges = [[1,0,8],[0,2,7]], queries = [[0,1,2]]
 * 
 * Output: [15]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * answer[0]: The total weight of the selected subtree that ensures a path from
 * src1 = 0 and src2 = 1 to dest = 2 is 8 + 7 = 15.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= n <= 10^5
 * edges.length == n - 1
 * edges[i].length == 3
 * 0 <= ui, vi < n
 * 1 <= wi <= 10^4
 * 1 <= queries.length <= 10^5
 * queries[j].length == 3
 * 0 <= src1j, src2j, destj < n
 * src1j, src2j, and destj are pairwise distinct.
 * The input is generated such that edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <cmath>
using namespace std;
// @lc code=start
class LCABinaryLifting {
public:
    LCABinaryLifting(vector<vector<int>> &edges) {
        int n = edges.size() + 1;
        int m = floor(log2(n)) + 1;
        vector<vector<pair<int, int>>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].push_back({y, w});
            g[y].push_back({x, w});
        }

        depth.resize(n);
        dis.resize(n);
        pa.resize(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int x, int parent) -> void {
            pa[x][0] = parent;
            for (auto &[y, w] : g[x]) {
                if (y != parent) {
                    depth[y] = depth[x] + 1;
                    dis[y] = dis[x] + w;
                    dfs(dfs, y, x);
                }
            }
        };
        dfs(dfs, 0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (int p = pa[x][i]; p != -1) {
                    pa[x][i + 1] = pa[p][i];
                }
            }
        }
    }

    int get_kth_ancestor(int node, int k) {
        int m = k == 0 ? 0 : floor(log2(k)) + 1;
        for (int i = 0; i < m; i++) {
            if (k >> i & 1) {
                node = pa[node][i];
                if (node < 0) {
                    break;
                }
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) {
            swap(x, y);
        }
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (x == y) {
            return x;
        }
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py;
            }
        }
        return pa[x][0];
    }

    int get_dis(int x, int y) {
        return dis[x] + dis[y] - dis[get_lca(x, y)] * 2;
    }

private:
    vector<int> depth, dis;
    vector<vector<int>> pa;
};

class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        LCABinaryLifting g(edges);
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int a = queries[i][0], b = queries[i][1], c = queries[i][2];
            ans[i] = (g.get_dis(a, b) + g.get_dis(b, c) + g.get_dis(c, a)) / 2;
        }
        return ans;
    }
};
// @lc code=end

