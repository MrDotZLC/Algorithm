/*
 * @lc app=leetcode id=3249 lang=cpp
 *
 * [3249] Count the Number of Good Nodes
 *
 * https://leetcode.com/problems/count-the-number-of-good-nodes/description/
 *
 * algorithms
 * Medium (54.73%)
 * Likes:    170
 * Dislikes: 46
 * Total Accepted:    29.6K
 * Total Submissions: 53.9K
 * Testcase Example:  '[[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]'
 *
 * There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted
 * at node 0. You are given a 2D integer array edges of length n - 1, where
 * edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi
 * in the tree.
 * 
 * A node is good if all the subtrees rooted at its children have the same
 * size.
 * 
 * Return the number of good nodes in the given tree.
 * 
 * A subtree of treeName is a tree consisting of a node in treeName and all of
 * its descendants.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
 * 
 * Output: 7
 * 
 * Explanation:
 * 
 * All of the nodes of the given tree are good.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges = [[0,1],[1,2],[2,3],[3,4],[0,5],[1,6],[2,7],[3,8]]
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * There are 6 good nodes in the given tree. They are colored in the image
 * above.
 * 
 * Example 3:
 * 
 * 
 * Input: edges =
 * [[0,1],[1,2],[1,3],[1,4],[0,5],[5,6],[6,7],[7,8],[0,9],[9,10],[9,12],[10,11]]
 * 
 * Output: 12
 * 
 * Explanation:
 * 
 * All nodes except node 9 are good.
 * 
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
 * The input is generated such that edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        vector<vector<int>> g(edges.size() + 1);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = 0;

        function<int(int, int)> dfs = [&](int x, int parent) -> int {
            int size = 1, sz0 = 0;
            bool is_good = true;
            for (auto &c : g[x]) {
                if (c == parent) {
                    continue;    
                }
                int sz = dfs(c, x);
                if (sz0 == 0) {
                    sz0 = sz;
                } else if (sz0 != sz) {
                    is_good = false;
                }
                size += sz;
            }
            ans += is_good;
            return size;
        };

        dfs(0, -1);
        return ans;
    }
};
// @lc code=end

