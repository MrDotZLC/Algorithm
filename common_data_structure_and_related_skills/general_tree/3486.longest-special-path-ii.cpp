/*
 * @lc app=leetcode id=3486 lang=cpp
 *
 * [3486] Longest Special Path II
 *
 * https://leetcode.com/problems/longest-special-path-ii/description/
 *
 * algorithms
 * Hard (16.14%)
 * Likes:    26
 * Dislikes: 6
 * Total Accepted:    1.7K
 * Total Submissions: 11K
 * Testcase Example:  '[[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]]\n' +
  '[1,1,0,3,1,2,1,1,0]'
 *
 * You are given an undirected tree rooted at node 0, with n nodes numbered
 * from 0 to n - 1. This is represented by a 2D array edges of length n - 1,
 * where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi
 * with length lengthi. You are also given an integer array nums, where nums[i]
 * represents the value at node i.
 * 
 * A special path is defined as a downward path from an ancestor node to a
 * descendant node in which all node values are distinct, except for at most
 * one value that may appear twice.
 * 
 * Return an array result of size 2, where result[0] is the length of the
 * longest special path, and result[1] is the minimum number of nodes in all
 * possible longest special paths.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges =
 * [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums =
 * [1,1,0,3,1,2,1,1,0]
 * 
 * Output: [9,3]
 * 
 * Explanation:
 * 
 * In the image below, nodes are colored by their corresponding values in
 * nums.
 * 
 * 
 * 
 * The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having
 * a length of 9. The minimum number of nodes across all longest special paths
 * is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges = [[1,0,3],[0,2,4],[0,3,5]], nums = [1,1,0,2]
 * 
 * Output: [5,2]
 * 
 * Explanation:
 * 
 * 
 * 
 * The longest path is 0 -> 3 consisting of 2 nodes with a length of 5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 5 * 10^4
 * edges.length == n - 1
 * edges[i].length == 3
 * 0 <= ui, vi < n
 * 1 <= lengthi <= 10^3
 * nums.length == n
 * 0 <= nums[i] <= 5 * 10^4
 * The input is generated such that edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        vector<vector<pair<int, int>>> g(nums.size());
        for (auto &e : edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }

        pair<int, int> ans = {-1, 0};
        vector<int> dis = {0};
        unordered_map<int, int>
            last_depth;  // 颜色最后一次出现的深度+1，深度从0开始，区别于颜色不存在的0

        auto dfs = [&](this auto &&dfs, int x, int parent,
                       int top_depth, int last1) -> void {
            int color = nums[x];
            int last2 = last_depth[color];
            top_depth = max(top_depth, min(last1, last2));

            // 结点数取反比较，即同等路径长度下，取结点数最少的结果
            ans = max(ans, pair(dis.back() - dis[top_depth],
                                top_depth - (int) dis.size()));

            last_depth[color] = dis.size();
            for (auto &[y, w] : g[x]) {
                if (y != parent) {
                    dis.push_back(dis.back() + w);
                    // 维护last1，表示所有颜色的上端限制，与top_depth的作用不重复
                    dfs(y, x, top_depth, max(last1, last2));
                    dis.pop_back(); // 恢复现场
                }
            }
            last_depth[color] = last2;
        };

        dfs(0, -1, 0, 0);

        return {ans.first, -ans.second}; // 结点数在前面取反了
    }
};
// @lc code=end

