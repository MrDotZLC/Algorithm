/*
 * @lc app=leetcode id=847 lang=cpp
 *
 * [847] Shortest Path Visiting All Nodes
 *
 * https://leetcode.com/problems/shortest-path-visiting-all-nodes/description/
 *
 * algorithms
 * Hard (65.49%)
 * Likes:    4570
 * Dislikes: 181
 * Total Accepted:    143.8K
 * Total Submissions: 219.1K
 * Testcase Example:  '[[1,2,3],[0],[0],[0]]'
 *
 * You have an undirected, connected graph of n nodes labeled from 0 to n - 1.
 * You are given an array graph where graph[i] is a list of all the nodes
 * connected with node i by an edge.
 * 
 * Return the length of the shortest path that visits every node. You may start
 * and stop at any node, you may revisit nodes multiple times, and you may
 * reuse edges.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: graph = [[1,2,3],[0],[0],[0]]
 * Output: 4
 * Explanation: One possible path is [1,0,2,0,3]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
 * Output: 4
 * Explanation: One possible path is [0,1,4,2,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == graph.length
 * 1 <= n <= 12
 * 0 <= graph[i].length < n
 * graph[i] does not contain i.
 * If graph[a] contains b, then graph[b] contains a.
 * The input graph is always connected.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 状压DP
 * 先求得两点的直接距离，再比较两点间所有路径，求得两点之间的最短路径
 * f(mask,last)表示已计算点下标集合为mask且上个点为last时的最短路径
 * f(mask,last)=min{f(mask|1<<k)+dist(last,k)}, k属于[0,n-1]&&(mask>>k&1)==0
 * 边界：mask=U，U=[0,n-1]
 * 入口：f(1<<i,i)，i∈[0,n-1]
 */
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX / 2));
        for (int u = 0; u < n; u++) {
            dist[u][u] = 0;
            for (int v : graph[u]) {
                dist[u][v] = dist[v][u] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[j][i] =
                            dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        int m = 1 << n;
        vector<vector<int>> memo(m - 1, vector<int>(n, INT_MAX / 2));
        auto dfs = [&](this auto &&dfs, int mask, int last) -> int {
            if (mask == m - 1) {
                return 0;
            }
            int &res = memo[mask][last];
            if (res != INT_MAX / 2) {
                return res;
            }
            for (int cur = 0; cur < n; cur++) {
                if ((mask >> cur & 1) == 0) {
                    res = min(res, dfs(mask | 1 << cur, cur) + dist[last][cur]);
                }
            }
            return res;
        };
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min(ans, dfs(1 << i, i));
        }
        return ans;
    }
};
// @lc code=end

