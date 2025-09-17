/*
 * @lc app=leetcode id=3559 lang=cpp
 *
 * [3559] Number of Ways to Assign Edge Weights II
 *
 * https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/description/
 *
 * algorithms
 * Hard (61.25%)
 * Likes:    49
 * Dislikes: 1
 * Total Accepted:    6K
 * Total Submissions: 10K
 * Testcase Example:  '[[1,2]]\n[[1,1],[1,2]]'
 *
 * There is an undirected tree with n nodes labeled from 1 to n, rooted at node
 * 1. The tree is represented by a 2D integer array edges of length n - 1,
 * where edges[i] = [ui, vi] indicates that there is an edge between nodes ui
 * and vi.
 * 
 * Initially, all edges have a weight of 0. You must assign each edge a weight
 * of either 1 or 2.
 * 
 * The cost of a path between any two nodes u and v is the total weight of all
 * edges in the path connecting them.
 * 
 * You are given a 2D integer array queries. For each queries[i] = [ui, vi],
 * determine the number of ways to assign weights to edges in the path such
 * that the cost of the path between ui and vi is odd.
 * 
 * Return an array answer, where answer[i] is the number of valid assignments
 * for queries[i].
 * 
 * Since the answer may be large, apply modulo 10^9 + 7 to each answer[i].
 * 
 * Note: For each query, disregard all edges not in the path between node ui
 * and vi.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: edges = [[1,2]], queries = [[1,1],[1,2]]
 * 
 * Output: [0,1]
 * 
 * Explanation:
 * 
 * 
 * Query [1,1]: The path from Node 1 to itself consists of no edges, so the
 * cost is 0. Thus, the number of valid assignments is 0.
 * Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2).
 * Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the
 * number of valid assignments is 1.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]
 * 
 * Output: [2,1,4]
 * 
 * Explanation:
 * 
 * 
 * Query [1,4]: The path from Node 1 to Node 4 consists of two edges (1 → 3 and
 * 3 → 4). Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the
 * number of valid assignments is 2.
 * Query [3,4]: The path from Node 3 to Node 4 consists of one edge (3 → 4).
 * Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the
 * number of valid assignments is 1.
 * Query [2,5]: The path from Node 2 to Node 5 consists of three edges (2 → 1,
 * 1 → 3, and 3 → 5). Assigning (1,2,2), (2,1,2), (2,2,1), or (1,1,1) makes the
 * cost odd. Thus, the number of valid assignments is 4.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^5
 * edges.length == n - 1
 * edges[i] == [ui, vi]
 * 1 <= queries.length <= 10^5
 * queries[i] == [ui, vi]
 * 1 <= ui, vi <= n
 * edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <cmath>
using namespace std;
// @lc code=start
class LCABinaryLifting {
public:
    LCABinaryLifting(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        int m = floor(log2(n)) + 1;
        // int m = bit_width((unsigned) n);
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        depth.resize(n);
        pa.resize(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int x, int parent) -> void {
            pa[x][0] = parent;
            for (int y : g[x]) {
                if (y != parent) {
                    depth[y] = depth[x] + 1;
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
        for (; k; k &= k - 1) {
            node = pa[node][countr_zero((unsigned) k)];
        }
        return node;
        // int m = floor(log2(k)) + 1;
        // for (int i = 0; i < m; i++) {
        //     if (k >> i & 1) {
        //         node = pa[node][i];
        //         if (node == -1) {
        //             break;
        //         }
        //     }
        // }
        // return node;
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
                y = py; // 同时往上跳2^i步
            }
        }
        return pa[x][0];
    }

    int get_dis(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[get_lca(x, y)];
    }

private:
    vector<int> depth;
    vector<vector<int>> pa;
};

const int MOD = 1e9 + 7;
const int MX = 1e5; 

int pow2[MX];

auto init = [] {
    // 预处理2的幂
    pow2[0] = 1;
    for (int i = 1; i < MX; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    return 0;
}();

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        LCABinaryLifting g(edges);
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int x = queries[i][0] - 1, y = queries[i][1] - 1;
            if (x != y) {
                ans[i] = pow2[g.get_dis(x, y) - 1];
            }
        }
        return ans;
    }
};
// @lc code=end

