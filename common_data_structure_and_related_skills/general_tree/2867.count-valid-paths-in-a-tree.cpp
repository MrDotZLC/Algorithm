/*
 * @lc app=leetcode id=2867 lang=cpp
 *
 * [2867] Count Valid Paths in a Tree
 *
 * https://leetcode.com/problems/count-valid-paths-in-a-tree/description/
 *
 * algorithms
 * Hard (34.93%)
 * Likes:    279
 * Dislikes: 8
 * Total Accepted:    8.9K
 * Total Submissions: 25.2K
 * Testcase Example:  '5\n[[1,2],[1,3],[2,4],[2,5]]'
 *
 * There is an undirected tree with n nodes labeled from 1 to n. You are given
 * the integer n and a 2D integer array edges of length n - 1, where edges[i] =
 * [ui, vi] indicates that there is an edge between nodes ui and vi in the
 * tree.
 * 
 * Return the number of valid paths in the tree.
 * 
 * A path (a, b) is valid if there exists exactly one prime number among the
 * node labels in the path from a to b.
 * 
 * Note that:
 * 
 * 
 * The path (a, b) is a sequence of distinct nodes starting with node a and
 * ending with node b such that every two adjacent nodes in the sequence share
 * an edge in the tree.
 * Path (a, b) and path (b, a) are considered the same and counted only
 * once.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
 * Output: 4
 * Explanation: The pairs with exactly one prime number on the path between
 * them are: 
 * - (1, 2) since the path from 1 to 2 contains prime number 2. 
 * - (1, 3) since the path from 1 to 3 contains prime number 3.
 * - (1, 4) since the path from 1 to 4 contains prime number 2.
 * - (2, 4) since the path from 2 to 4 contains prime number 2.
 * It can be shown that there are only 4 valid paths.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 6, edges = [[1,2],[1,3],[2,4],[3,5],[3,6]]
 * Output: 6
 * Explanation: The pairs with exactly one prime number on the path between
 * them are: 
 * - (1, 2) since the path from 1 to 2 contains prime number 2.
 * - (1, 3) since the path from 1 to 3 contains prime number 3.
 * - (1, 4) since the path from 1 to 4 contains prime number 2.
 * - (1, 6) since the path from 1 to 6 contains prime number 3.
 * - (2, 4) since the path from 2 to 4 contains prime number 2.
 * - (3, 6) since the path from 3 to 6 contains prime number 3.
 * It can be shown that there are only 6 valid paths.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * edges.length == n - 1
 * edges[i].length == 2
 * 1 <= ui, vi <= n
 * The input is generated such that edges represent a valid tree.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
const int MX = 1e5;
bool np[MX + 1];
int init = []() {
    np[1] = true;
    for (int i = 2; i * i <= MX; i++) {
        if (!np[i]) {
            for (int j = i * i; j <= MX; j += i) {
                np[j] = true;
            }
        }
    }
    return 0;
}();

class Solution {
public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n + 1);
        for (auto &e: edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> size(n + 1);
        vector<int> nodes;
        auto dfs = [&](auto &dfs, int x, int parent) -> void {
            nodes.push_back(x);
            for (int y : g[x]) {
                if (y != parent && np[y]) {
                    dfs(dfs, y, x);
                }
            }
        };

        long long ans = 0;
        for (int x = 1; x <= n; x++) { // 遍历所有质数
            if (np[x]) {
                continue;
            }
            int sum = 0;
            for (int y : g[x]) { // 遍历质数下所有的非质数连通块
                if (!np[y]) {
                    continue;
                }
                if (size[y] == 0) { // 没遍历过的
                    nodes.clear();
                    dfs(dfs, y, -1); // 遍历y下的非质数联通快
                    for (int z : nodes) {
                        size[z] = nodes.size();
                    }
                }
                // 这 size[y] 个非质数与之前遍历到的 sum 个非质数，两两之间的路径只包含质数 x
                ans += (long long) size[y] * sum;
                sum += size[y];
            }
            ans += sum;
        }
        return ans;
    }
};
// @lc code=end

