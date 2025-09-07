/*
 * @lc app=leetcode id=1466 lang=cpp
 *
 * [1466] Reorder Routes to Make All Paths Lead to the City Zero
 *
 * https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/description/
 *
 * algorithms
 * Medium (65.17%)
 * Likes:    4525
 * Dislikes: 142
 * Total Accepted:    286K
 * Total Submissions: 437.9K
 * Testcase Example:  '6\n[[0,1],[1,3],[2,3],[4,0],[4,5]]'
 *
 * There are n cities numbered from 0 to n - 1 and n - 1 roads such that there
 * is only one way to travel between two different cities (this network form a
 * tree). Last year, The ministry of transport decided to orient the roads in
 * one direction because they are too narrow.
 * 
 * Roads are represented by connections where connections[i] = [ai, bi]
 * represents a road from city ai to city bi.
 * 
 * This year, there will be a big event in the capital (city 0), and many
 * people want to travel to this city.
 * 
 * Your task consists of reorienting some roads such that each city can visit
 * the city 0. Return the minimum number of edges changed.
 * 
 * It's guaranteed that each city can reach city 0 after reorder.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
 * Output: 3
 * Explanation: Change the direction of edges show in red such that each node
 * can reach the node 0 (capital).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
 * Output: 2
 * Explanation: Change the direction of edges show in red such that each node
 * can reach the node 0 (capital).
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, connections = [[1,0],[2,0]]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 5 * 10^4
 * connections.length == n - 1
 * connections[i].length == 2
 * 0 <= ai, bi <= n - 1
 * ai != bi
 * 
 * 
 */
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
// @lc code=start
class Solution {
public:
    // bfs
    int minReorder1(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        for (auto &conn : connections) {
            graph[conn[0]].emplace_back(conn[1]);
            graph[conn[1]].emplace_back(-conn[0]);
        }

        vector<bool> visited(n, false);
        visited[0] = true;
        deque<int> q{0};
        int ans = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop_front();
            for (auto &neighbor : graph[node]) {
                int nei = abs(neighbor);
                if (visited[nei]) {
                    continue;
                }
                visited[nei] = true;
                if (neighbor > 0) {
                    ans++;
                }
                q.push_back(nei);
            }
        }
        return ans;
    }

    // dfs
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        for (auto &conn : connections) {
            graph[conn[0]].emplace_back(conn[1]);
            graph[conn[1]].emplace_back(-conn[0]);
        }

        int ans = 0;
        auto dfs = [&](auto &dfs, int node, int parent) -> void {
            for (int neighbor : graph[node]) {
                int nei = abs(neighbor);
                if (nei != parent) {
                    if (neighbor > 0) {
                        ans++;
                    }
                    dfs(dfs, nei, node);
                }
            }
        };
        dfs(dfs, 0, -1);

        return ans;
    }
};
// @lc code=end

