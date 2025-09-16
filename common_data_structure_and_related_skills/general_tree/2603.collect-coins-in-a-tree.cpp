/*
 * @lc app=leetcode id=2603 lang=cpp
 *
 * [2603] Collect Coins in a Tree
 *
 * https://leetcode.com/problems/collect-coins-in-a-tree/description/
 *
 * algorithms
 * Hard (37.40%)
 * Likes:    526
 * Dislikes: 17
 * Total Accepted:    13.1K
 * Total Submissions: 34.2K
 * Testcase Example:  '[1,0,0,0,0,1]\n[[0,1],[1,2],[2,3],[3,4],[4,5]]'
 *
 * There exists an undirected and unrooted tree with n nodes indexed from 0 to
 * n - 1. You are given an integer n and a 2D integer array edges of length n -
 * 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes
 * ai and bi in the tree. You are also given an array coins of size n where
 * coins[i] can be either 0 or 1, where 1 indicates the presence of a coin in
 * the vertex i.
 * 
 * Initially, you choose to start at any vertex in the tree. Then, you can
 * perform the following operations any number of times: 
 * 
 * 
 * Collect all the coins that are at a distance of at most 2 from the current
 * vertex, or
 * Move to any adjacent vertex in the tree.
 * 
 * 
 * Find the minimum number of edges you need to go through to collect all the
 * coins and go back to the initial vertex.
 * 
 * Note that if you pass an edge several times, you need to count it into the
 * answer several times.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
 * Output: 2
 * Explanation: Start at vertex 2, collect the coin at vertex 0, move to vertex
 * 3, collect the coin at vertex 5 then move back to vertex 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: coins = [0,0,0,1,1,0,0,1], edges =
 * [[0,1],[0,2],[1,3],[1,4],[2,5],[5,6],[5,7]]
 * Output: 2
 * Explanation: Start at vertex 0, collect the coins at vertices 4 and 3, move
 * to vertex 2,  collect the coin at vertex 7, then move back to vertex 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == coins.length
 * 1 <= n <= 3 * 10^4
 * 0 <= coins[i] <= 1
 * edges.length == n - 1
 * edges[i].length == 2
 * 0 <= ai, bi < n
 * ai != bi
 * edges represents a valid tree.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<vector<int>> g(n);
        vector<int> deg(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
            deg[x]++;
            deg[y]++;
        }

        int edge_size = n - 1;
        vector<int> q; // 拓扑排序队列
        for (int i = 0; i < n; i++) {
            if (deg[i] == 1 && coins[i] == 0) { // 没有金币的叶子
                q.push_back(i);
            }
        }
        while (!q.empty()) {
            edge_size--; // 删除没有金币的叶子
            int x = q.back();
            q.pop_back();
            for (int y : g[x]) {
                if (--deg[y] == 1 && coins[y] == 0) { // 没有金币的叶子
                    q.push_back(y);
                }
            }
        }       
        
        for (int i = 0; i < n; i++) { // 再次拓扑排序
            if (deg[i] == 1 && coins[i] == 1) { // 有金币的叶子
                q.push_back(i);
            }
        }
        edge_size -= q.size(); // 删掉有金币的叶子
        for (int x : q) { // 再删掉有金币叶子上面的节点，即无用节点都被清空
            for (int y : g[x]) {
                if (--deg[y] == 1) {
                    edge_size--;
                }
            }
        }

        return max(edge_size * 2, 0);
    }
};
// @lc code=end

