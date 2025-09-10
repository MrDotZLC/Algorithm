/*
 * @lc app=leetcode id=3203 lang=cpp
 *
 * [3203] Find Minimum Diameter After Merging Two Trees
 *
 * https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
 *
 * algorithms
 * Hard (57.31%)
 * Likes:    679
 * Dislikes: 39
 * Total Accepted:    76.5K
 * Total Submissions: 133.7K
 * Testcase Example:  '[[0,1],[0,2],[0,3]]\n[[0,1]]'
 *
 * There exist two undirected trees with n and m nodes, numbered from 0 to n -
 * 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays
 * edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i]
 * = [ai, bi] indicates that there is an edge between nodes ai and bi in the
 * first tree and edges2[i] = [ui, vi] indicates that there is an edge between
 * nodes ui and vi in the second tree.
 * 
 * You must connect one node from the first tree with another node from the
 * second tree with an edge.
 * 
 * Return the minimum possible diameter of the resulting tree.
 * 
 * The diameter of a tree is the length of the longest path between any two
 * nodes in the tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * We can obtain a tree of diameter 3 by connecting node 0 from the first tree
 * with any node from the second tree.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 =
 * [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * We can obtain a tree of diameter 5 by connecting node 0 from the first tree
 * with node 0 from the second tree.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n, m <= 10^5
 * edges1.length == n - 1
 * edges2.length == m - 1
 * edges1[i].length == edges2[i].length == 2
 * edges1[i] = [ai, bi]
 * 0 <= ai, bi < n
 * edges2[i] = [ui, vi]
 * 0 <= ui, vi < m
 * The input is generated such that edges1 and edges2 represent valid trees.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int a = diameter(edges1);
        int b = diameter(edges2);
        return max({a, b, (a + 1) / 2 + (b + 1) / 2 + 1});
    }

    int diameter(vector<vector<int>>& edges) {
        vector<vector<int>> g(edges.size() + 1);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = 0;
        auto dfs = [&](auto &dfs, int x, int parent) ->int {
            int mx = 0;
            for (int y : g[x]) {
                if (y != parent) {
                    int sub_mx = dfs(dfs, y, x) + 1;
                    ans = max(ans, mx + sub_mx);
                    mx = max(mx, sub_mx);
                }
            }
            return mx;
        };

        dfs(dfs, 0, -1);
        return ans;
    }
};
// @lc code=end

