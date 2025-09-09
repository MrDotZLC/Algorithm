/*
 * @lc app=leetcode id=3372 lang=cpp
 *
 * [3372] Maximize the Number of Target Nodes After Connecting Trees I
 *
 * https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/description/
 *
 * algorithms
 * Medium (69.67%)
 * Likes:    436
 * Dislikes: 262
 * Total Accepted:    82.4K
 * Total Submissions: 118.3K
 * Testcase Example:  '[[0,1],[0,2],[2,3],[2,4]]\n[[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]\n2'
 *
 * There exist two undirected trees with n and m nodes, with distinct labels in
 * ranges [0, n - 1] and [0, m - 1], respectively.
 * 
 * You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m
 * - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an
 * edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi]
 * indicates that there is an edge between nodes ui and vi in the second tree.
 * You are also given an integer k.
 * 
 * Node u is target to node v if the number of edges on the path from u to v is
 * less than or equal to k. Note that a node is always target to itself.
 * 
 * Return an array of n integers answer, where answer[i] is the maximum
 * possible number of nodes target to node i of the first tree if you have to
 * connect one node from the first tree to another node in the second tree.
 * 
 * Note that queries are independent from each other. That is, for every query
 * you will remove the added edge before proceeding to the next query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 =
 * [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
 * 
 * Output: [9,7,9,8,8]
 * 
 * Explanation:
 * 
 * 
 * For i = 0, connect node 0 from the first tree to node 0 from the second
 * tree.
 * For i = 1, connect node 1 from the first tree to node 0 from the second
 * tree.
 * For i = 2, connect node 2 from the first tree to node 4 from the second
 * tree.
 * For i = 3, connect node 3 from the first tree to node 4 from the second
 * tree.
 * For i = 4, connect node 4 from the first tree to node 4 from the second
 * tree.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k =
 * 1
 * 
 * Output: [6,3,3,3,3]
 * 
 * Explanation:
 * 
 * For every i, connect node i of the first tree with any node of the second
 * tree.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n, m <= 1000
 * edges1.length == n - 1
 * edges2.length == m - 1
 * edges1[i].length == edges2[i].length == 2
 * edges1[i] = [ai, bi]
 * 0 <= ai, bi < n
 * edges2[i] = [ui, vi]
 * 0 <= ui, vi < m
 * The input is generated such that edges1 and edges2 represent valid
 * trees.
 * 0 <= k <= 1000
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int mx2 = 0;
        if (k > 0) {
            auto g = build_tree(edges2);
            for (int i = 0; i < g.size(); i++) {
                mx2 = max(mx2, dfs(i, -1, 0, g, k - 1));
            }
        }

        auto g = build_tree(edges1);
        vector<int> ans(edges1.size() + 1);
        for (int i = 0; i < g.size(); i++) {
            ans[i] = dfs(i, -1, 0, g, k) + mx2;
        }
        return ans;
    }

    vector<vector<int>> build_tree(vector<vector<int>>& edges) {
        vector<vector<int>> g(edges.size() + 1);
        for (auto &e : edges) {
            g[e[0]].emplace_back(e[1]);
            g[e[1]].emplace_back(e[0]);
        }
        return g;
    }

    int dfs(int x, int parent, int depth, vector<vector<int>> &g, int k) {
        if (depth > k) {
            return 0;
        }
        int cnt = 1;
        for (int y : g[x]) {
            if (y != parent) {
                cnt += dfs(y, x, depth + 1, g, k);
            }
        }
        return cnt;
    }
};
// @lc code=end

