/*
 * @lc app=leetcode id=2538 lang=cpp
 *
 * [2538] Difference Between Maximum and Minimum Price Sum
 *
 * https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/description/
 *
 * algorithms
 * Hard (32.05%)
 * Likes:    463
 * Dislikes: 19
 * Total Accepted:    9.8K
 * Total Submissions: 30.3K
 * Testcase Example:  '6\n[[0,1],[1,2],[1,3],[3,4],[3,5]]\n[9,8,7,6,10,5]'
 *
 * There exists an undirected and initially unrooted tree with n nodes indexed
 * from 0 to n - 1. You are given the integer n and a 2D integer array edges of
 * length n - 1, where edges[i] = [ai, bi] indicates that there is an edge
 * between nodes ai and bi in the tree.
 * 
 * Each node has an associated price. You are given an integer array price,
 * where price[i] is the price of the i^th node.
 * 
 * The price sum of a given path is the sum of the prices of all nodes lying on
 * that path.
 * 
 * The tree can be rooted at any node root of your choice. The incurred cost
 * after choosing root is the difference between the maximum and minimum price
 * sum amongst all paths starting at root.
 * 
 * Return the maximum possible cost amongst all possible root choices.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price =
 * [9,8,7,6,10,5]
 * Output: 24
 * Explanation: The diagram above denotes the tree after rooting it at node 2.
 * The first part (colored in red) shows the path with the maximum price sum.
 * The second part (colored in blue) shows the path with the minimum price sum.
 * - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and
 * the sum of the prices is 31.
 * - The second path contains the node [2] with the price [7].
 * The difference between the maximum and minimum price sum is 24. It can be
 * proved that 24 is the maximum cost.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, edges = [[0,1],[1,2]], price = [1,1,1]
 * Output: 2
 * Explanation: The diagram above denotes the tree after rooting it at node 0.
 * The first part (colored in red) shows the path with the maximum price sum.
 * The second part (colored in blue) shows the path with the minimum price sum.
 * - The first path contains nodes [0,1,2]: the prices are [1,1,1], and the sum
 * of the prices is 3.
 * - The second path contains node [0] with a price [1].
 * The difference between the maximum and minimum price sum is 2. It can be
 * proved that 2 is the maximum cost.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * edges.length == n - 1
 * 0 <= ai, bi <= n - 1
 * edges represents a valid tree.
 * price.length == n
 * 1 <= price[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        long ans = 0;
        function<pair<long, long>(int, int)> dfs = [&](int x, int parent) -> pair<long, long> {
            long p = price[x], max_s1 = p, max_s2 = 0;
            for (int y : g[x]) {
                if (y != parent) {
                    auto [s1, s2] = dfs(y, x);
                    ans = max({ans, max_s1 + s2, max_s2 + s1});
                    max_s1 = max(max_s1, s1 + p);
                    max_s2 = max(max_s2, s2 + p);
                }
            }
            return {max_s1, max_s2};
        };

        dfs(0, -1);
        return ans;
    }
};
// @lc code=end

