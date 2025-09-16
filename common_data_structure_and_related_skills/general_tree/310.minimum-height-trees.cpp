/*
 * @lc app=leetcode id=310 lang=cpp
 *
 * [310] Minimum Height Trees
 *
 * https://leetcode.com/problems/minimum-height-trees/description/
 *
 * algorithms
 * Medium (42.06%)
 * Likes:    8738
 * Dislikes: 410
 * Total Accepted:    449.3K
 * Total Submissions: 1.1M
 * Testcase Example:  '4\n[[1,0],[1,2],[1,3]]'
 *
 * A tree is an undirected graph in which any two vertices are connected by
 * exactly one path. In other words, any connected graph without simple cycles
 * is a tree.
 * 
 * Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1
 * edges where edges[i] = [ai, bi] indicates that there is an undirected edge
 * between the two nodes ai and bi in the tree, you can choose any node of the
 * tree as the root. When you select a node x as the root, the result tree has
 * height h. Among all possible rooted trees, those with minimum height (i.e.
 * min(h))  are called minimum height trees (MHTs).
 * 
 * Return a list of all MHTs' root labels. You can return the answer in any
 * order.
 * 
 * The height of a rooted tree is the number of edges on the longest downward
 * path between the root and a leaf.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4, edges = [[1,0],[1,2],[1,3]]
 * Output: [1]
 * Explanation: As shown, the height of the tree is 1 when the root is the node
 * with label 1 which is the only MHT.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
 * Output: [3,4]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 2 * 10^4
 * edges.length == n - 1
 * 0 <= ai, bi < n
 * ai != bi
 * All the pairs (ai, bi) are distinct.
 * The given input is guaranteed to be a tree and there will be no repeated
 * edges.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <deque>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // memory + dfs -> TLE
    vector<int> findMinHeightTrees1(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }
        
        unordered_map<int, int> m;
        int min_d = n + 1;
        function<int(int, int)> dfs = [&](int x, int parent) -> int {
            int k = x * 1e5 + parent;
            if (m[k]) {
                return m[k];
            }
            int d = 0;
            for (int y : g[x]) {
                if (y != parent) {
                    int sub_d = dfs(y, x);
                    d = max(d, sub_d);
                }
            }
            m[k] = d + 1;
            return d + 1;
        };

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int d = dfs(i, -1);
            if (d > min_d) {
                continue;
            }
            if (d < min_d) {
                min_d = d;
                ans.clear();
            }
            ans.push_back(i);
        }
        return ans;
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        vector<vector<int>> g(n);
        vector<int> degree(n ,0);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
            degree[x]++;
            degree[y]++;
        }
        
        deque<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                q.push_back(i);
            }
        }

        vector<int> ans;
        int remaining = n;
        while (remaining > 2) {
            int sz = q.size();
            remaining -= sz;

            for (int i = 0; i < sz; i++) {
                int x = q.front();
                q.pop_front();
                for (int y : g[x]) {
                    if (--degree[y] == 1) {
                        q.push_back(y);
                    }
                }
            }
        }

        ans.insert(ans.end(), q.begin(), q.end());
        return ans;
    }
};
// @lc code=end

