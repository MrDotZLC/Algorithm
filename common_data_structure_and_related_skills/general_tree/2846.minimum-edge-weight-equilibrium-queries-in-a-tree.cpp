/*
 * @lc app=leetcode id=2846 lang=cpp
 *
 * [2846] Minimum Edge Weight Equilibrium Queries in a Tree
 *
 * https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/description/
 *
 * algorithms
 * Hard (43.47%)
 * Likes:    343
 * Dislikes: 8
 * Total Accepted:    8.4K
 * Total Submissions: 19.2K
 * Testcase Example:  '7\n' +
  '[[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]]\n' +
  '[[0,3],[3,6],[2,6],[0,6]]'
 *
 * There is an undirected tree with n nodes labeled from 0 to n - 1. You are
 * given the integer n and a 2D integer array edges of length n - 1, where
 * edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and
 * vi with weight wi in the tree.
 * 
 * You are also given a 2D integer array queries of length m, where queries[i]
 * = [ai, bi]. For each query, find the minimum number of operations required
 * to make the weight of every edge on the path from ai to bi equal. In one
 * operation, you can choose any edge of the tree and change its weight to any
 * value.
 * 
 * Note that:
 * 
 * 
 * Queries are independent of each other, meaning that the tree returns to its
 * initial state on each new query.
 * The path from ai to bi is a sequence of distinct nodes starting with node ai
 * and ending with node bi such that every two adjacent nodes in the sequence
 * share an edge in the tree.
 * 
 * 
 * Return an array answer of length m where answer[i] is the answer to the i^th
 * query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]],
 * queries = [[0,3],[3,6],[2,6],[0,6]]
 * Output: [0,0,1,3]
 * Explanation: In the first query, all the edges in the path from 0 to 3 have
 * a weight of 1. Hence, the answer is 0.
 * In the second query, all the edges in the path from 3 to 6 have a weight of
 * 2. Hence, the answer is 0.
 * In the third query, we change the weight of edge [2,3] to 2. After this
 * operation, all the edges in the path from 2 to 6 have a weight of 2. Hence,
 * the answer is 1.
 * In the fourth query, we change the weights of edges [0,1], [1,2] and [2,3]
 * to 2. After these operations, all the edges in the path from 0 to 6 have a
 * weight of 2. Hence, the answer is 3.
 * For each queries[i], it can be shown that answer[i] is the minimum number of
 * operations needed to equalize all the edge weights in the path from ai to
 * bi.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 8, edges =
 * [[1,2,6],[1,3,4],[2,4,6],[2,5,3],[3,6,6],[3,0,8],[7,0,2]], queries =
 * [[4,6],[0,4],[6,5],[7,4]]
 * Output: [1,2,2,3]
 * Explanation: In the first query, we change the weight of edge [1,3] to 6.
 * After this operation, all the edges in the path from 4 to 6 have a weight of
 * 6. Hence, the answer is 1.
 * In the second query, we change the weight of edges [0,3] and [3,1] to 6.
 * After these operations, all the edges in the path from 0 to 4 have a weight
 * of 6. Hence, the answer is 2.
 * In the third query, we change the weight of edges [1,3] and [5,2] to 6.
 * After these operations, all the edges in the path from 6 to 5 have a weight
 * of 6. Hence, the answer is 2.
 * In the fourth query, we change the weights of edges [0,7], [0,3] and [1,3]
 * to 6. After these operations, all the edges in the path from 7 to 4 have a
 * weight of 6. Hence, the answer is 3.
 * For each queries[i], it can be shown that answer[i] is the minimum number of
 * operations needed to equalize all the edge weights in the path from ai to
 * bi.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^4
 * edges.length == n - 1
 * edges[i].length == 3
 * 0 <= ui, vi < n
 * 1 <= wi <= 26
 * The input is generated such that edges represents a valid tree.
 * 1 <= queries.length == m <= 2 * 10^4
 * queries[i].length == 2
 * 0 <= ai, bi < n
 * 
 * 
 */
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, int>>> g(n);
        for (auto &e: edges) {
            int x = e[0], y = e[1], w = e[2] - 1;
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }

        int m = floor(log2(n)) + 1;
        vector<vector<int>> pa(n, vector<int>(m, -1));
        vector<vector<vector<int>>> cnt(n, vector<vector<int>>(m, vector<int>(26)));
        vector<int> depth(n);

        auto dfs = [&](auto &dfs, int x, int parent) -> void {
            pa[x][0] = parent;
            for (auto &[y, w] : g[x]) {
                if (y != parent) {
                    cnt[y][0][w] = 1;
                    depth[y] = depth[x] + 1;
                    dfs(dfs, y, x);
                }
            }
        };
        dfs(dfs, 0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                int p = pa[x][i];
                if (p != -1) {
                    pa[x][i + 1] = pa[p][i];
                    for (int j = 0; j < 26; j++) {
                        // i + 1等于上跳2 * (2 ^ i)， 需要: x跳2^i的计数 + p再跳2^i的计数
                        cnt[x][i + 1][j] = cnt[x][i][j] + cnt[p][i][j];
                    }
                }
            }
        }

        vector<int> ans;
        for (auto &q : queries) {
            int x = q[0], y = q[1];
            int path_len = depth[x] + depth[y];
            int cw[26]{};
            if (depth[x] > depth[y]) {
                swap(x, y);
            }
            
            // 让x、y处于同一高度
            int k = depth[y] - depth[x];
            int k_width = k ? floor(log2(k)) + 1 : 0;
            for (int i = 0; i < k_width; i++) {
                if (k >> i & 1) {
                    for (int j = 0; j < 26; j++) {
                        cw[j] += cnt[y][i][j];
                    }
                    y = pa[y][i];
                }
            }

            // x、y一起往上跳，直到跳到lca的子节点
            if (x != y) {
                for (int i = pa[x].size() - 1; i >= 0; i--) {
                    int px = pa[x][i], py = pa[y][i];
                    if (px != py) {
                        for (int j = 0; j < 26; j++) {
                            cw[j] += cnt[x][i][j] + cnt[y][i][j];
                        }
                        x = px;
                        y = py;
                    }
                }
                for (int j = 0; j < 26; j++) { // x、y已经是lca子节点，累加这两条边的权重
                    cw[j] += cnt[x][0][j] + cnt[y][0][j];
                }
                x = pa[x][0];
            }

            int lca = x;
            path_len -= 2 * depth[lca];
            ans.push_back(path_len - *ranges::max_element(cw, cw + 26));
        }
        return ans;
    }
};
// @lc code=end

