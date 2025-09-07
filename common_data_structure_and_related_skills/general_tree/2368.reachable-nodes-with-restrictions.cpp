/*
 * @lc app=leetcode id=2368 lang=cpp
 *
 * [2368] Reachable Nodes With Restrictions
 *
 * https://leetcode.com/problems/reachable-nodes-with-restrictions/description/
 *
 * algorithms
 * Medium (59.60%)
 * Likes:    762
 * Dislikes: 31
 * Total Accepted:    77.9K
 * Total Submissions: 130.4K
 * Testcase Example:  '7\n[[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]]\n[4,5]'
 *
 * There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1
 * edges.
 * 
 * You are given a 2D integer array edges of length n - 1 where edges[i] = [ai,
 * bi] indicates that there is an edge between nodes ai and bi in the tree. You
 * are also given an integer array restricted which represents restricted
 * nodes.
 * 
 * Return the maximum number of nodes you can reach from node 0 without
 * visiting a restricted node.
 * 
 * Note that node 0 will not be a restricted node.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted =
 * [4,5]
 * Output: 4
 * Explanation: The diagram above shows the tree.
 * We have that [0,1,2,3] are the only nodes that can be reached from node 0
 * without visiting a restricted node.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 7, edges = [[0,1],[0,2],[0,5],[0,4],[3,2],[6,5]], restricted =
 * [4,2,1]
 * Output: 3
 * Explanation: The diagram above shows the tree.
 * We have that [0,5,6] are the only nodes that can be reached from node 0
 * without visiting a restricted node.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^5
 * edges.length == n - 1
 * edges[i].length == 2
 * 0 <= ai, bi < n
 * ai != bi
 * edges represents a valid tree.
 * 1 <= restricted.length < n
 * 1 <= restricted[i] < n
 * All the values of restricted are unique.
 * 
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int> r(restricted.begin(), restricted.end());
        vector<vector<int>> graph(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            if (!r.contains(x) && !r.contains(y)) {
                graph[x].emplace_back(y);
                graph[y].emplace_back(x);
            }
        }
        auto dfs = [&](this auto &&dfs, int x, int parent) -> int {
            int cnt = 1;
            for (int y : graph[x]) {
                if (y != parent) {
                    cnt += dfs(y, x);
                }
            }
            return cnt;
        };
        return dfs(0, -1);
    }

};
// @lc code=end

