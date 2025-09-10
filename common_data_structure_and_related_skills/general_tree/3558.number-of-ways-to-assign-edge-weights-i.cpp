/*
 * @lc app=leetcode id=3558 lang=cpp
 *
 * [3558] Number of Ways to Assign Edge Weights I
 *
 * https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/description/
 *
 * algorithms
 * Medium (53.99%)
 * Likes:    51
 * Dislikes: 6
 * Total Accepted:    12.3K
 * Total Submissions: 23K
 * Testcase Example:  '[[1,2]]'
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
 * Select any one node x at the maximum depth. Return the number of ways to
 * assign edge weights in the path from node 1 to x such that its total cost is
 * odd.
 * 
 * Since the answer may be large, return it modulo 10^9 + 7.
 * 
 * Note: Ignore all edges not in the path from node 1 to x.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: edges = [[1,2]]
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * 
 * The path from Node 1 to Node 2 consists of one edge (1 → 2).
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
 * Input: edges = [[1,2],[1,3],[3,4],[3,5]]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node
 * can be selected for processing.
 * For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and
 * 3 → 4).
 * Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of
 * valid assignments is 2.
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
 * 1 <= ui, vi <= n
 * edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        vector<vector<int>> g(edges.size() + 2);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        auto dfs = [&](this auto &&dfs, int x, int parent) -> int {
            int mx_d = 0;
            for (auto &y : g[x]) {
                if (y != parent) {
                    mx_d = max(mx_d, dfs(y, x) + 1);
                }
            }
            return mx_d;
        };
        int k = dfs(1, 0);
        return qpow(2, k - 1);
    }
    
    long long qpow(long long x, int n, int MOD = 1e9+7) {
        long long res = 1;
        for (; n > 0; n /= 2) {
            if (n % 2) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
        }
        return res;
    }
};
// @lc code=end

