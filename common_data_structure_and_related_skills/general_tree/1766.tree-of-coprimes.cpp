/*
 * @lc app=leetcode id=1766 lang=cpp
 *
 * [1766] Tree of Coprimes
 *
 * https://leetcode.com/problems/tree-of-coprimes/description/
 *
 * algorithms
 * Hard (42.43%)
 * Likes:    422
 * Dislikes: 36
 * Total Accepted:    12.6K
 * Total Submissions: 29.4K
 * Testcase Example:  '[2,3,3,2]\n[[0,1],[1,2],[1,3]]'
 *
 * There is a tree (i.e., a connected, undirected graph that has no cycles)
 * consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each
 * node has a value associated with it, and the root of the tree is node 0.
 * 
 * To represent this tree, you are given an integer array nums and a 2D array
 * edges. Each nums[i] represents the i^th node's value, and each edges[j] =
 * [uj, vj] represents an edge between nodes uj and vj in the tree.
 * 
 * Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the
 * greatest common divisor of x and y.
 * 
 * An ancestor of a node i is any other node on the shortest path from node i
 * to the root. A node is not considered an ancestor of itself.
 * 
 * Return an array ans of size n, where ans[i] is the closest ancestor to node
 * i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such
 * ancestor.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
 * Output: [-1,0,0,1]
 * Explanation: In the above figure, each node's value is in parentheses.
 * - Node 0 has no coprime ancestors.
 * - Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3)
 * == 1).
 * - Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime
 * (gcd(3,3) == 3), but node 0's
 * ⁠ value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
 * - Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1
 * (gcd(3,2) == 1), so node 1 is its
 * ⁠ closest valid ancestor.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: nums = [5,6,10,2,3,6,15], edges =
 * [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
 * Output: [-1,0,-1,0,0,0,-1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * nums.length == n
 * 1 <= nums[i] <= 50
 * 1 <= n <= 10^5
 * edges.length == n - 1
 * edges[j].length == 2
 * 0 <= uj, vj < n
 * uj != vj
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int MX = 51;
        vector<int> coprime[MX];
        // 预处理：coprime[i] 保存 [1, MX) 中与 i 互质的所有元素
        for (int i = 1; i < MX; i++) {
            for (int j = 1; j < MX; j++) {
                if (gcd(i, j) == 1) {
                    coprime[i].push_back(j);
                }
            }
        }
        
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> ans(n, -1);
        vector<pair<int, int>> val_depth_id(MX, {-1, -1}); // 包含深度和节点编号

        auto dfs = [&](this auto &&dfs, int x, int parent, int depth) -> void {
            int val = nums[x];
            int mx_d = -1;
            for (int j : coprime[val]) {
                auto &[d, y] = val_depth_id[j];
                if (d > mx_d) {
                    mx_d = d;
                    ans[x] = y;
                }
            }

            auto tmp = val_depth_id[val];
            val_depth_id[val] = {depth, x};
            for (auto &c : g[x]) {
                if (c != parent) {
                    dfs(c, x, depth + 1);
                }
            }
            val_depth_id[val] = tmp;
        };

        dfs(0, -1, 1);
        return ans;
    }
};
// @lc code=end

