/*
 * @lc app=leetcode id=3425 lang=cpp
 *
 * [3425] Longest Special Path
 *
 * https://leetcode.com/problems/longest-special-path/description/
 *
 * algorithms
 * Hard (20.21%)
 * Likes:    117
 * Dislikes: 16
 * Total Accepted:    5.1K
 * Total Submissions: 24.9K
 * Testcase Example:  '[[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]]\n[2,1,2,1,3,1]'
 *
 * You are given an undirected tree rooted at node 0 with n nodes numbered from
 * 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i]
 * = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length
 * lengthi. You are also given an integer array nums, where nums[i] represents
 * the value at node i.
 * 
 * A special path is defined as a downward path from an ancestor node to a
 * descendant node such that all the values of the nodes in that path are
 * unique.
 * 
 * Note that a path may start and end at the same node.
 * 
 * Return an array result of size 2, where result[0] is the length of the
 * longest special path, and result[1] is the minimum number of nodes in all
 * possible longest special paths.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums =
 * [2,1,2,1,3,1]
 * 
 * Output: [6,2]
 * 
 * Explanation:
 * 
 * In the image below, nodes are colored by their corresponding values in
 * nums
 * 
 * 
 * 
 * The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length
 * of 6. The minimum number of nodes across all longest special paths is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: edges = [[1,0,8]], nums = [2,2]
 * 
 * Output: [0,1]
 * 
 * Explanation:
 * 
 * 
 * 
 * The longest special paths are 0 and 1, both having a length of 0. The
 * minimum number of nodes across all longest special paths is 1.
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
                       int top_depth) -> void {
            int color = nums[x];
            int old_depth = last_depth[color];
            top_depth = max(old_depth, top_depth);

            // 结点数取反比较，即同等路径长度下，取结点数最少的结果
            ans = max(ans, pair(dis.back() - dis[top_depth],
                                top_depth - (int) dis.size()));

            last_depth[color] = dis.size();
            for (auto &[y, w] : g[x]) {
                if (y != parent) {
                    dis.push_back(dis.back() + w);
                    dfs(y, x, top_depth);
                    dis.pop_back(); // 恢复现场
                }
            }
            last_depth[color] = old_depth;
        };

        dfs(0, -1, 0);

        return {ans.first, -ans.second}; // 结点数在前面取反了
    }
};
// @lc code=end

