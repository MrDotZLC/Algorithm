/*
 * @lc app=leetcode id=3331 lang=cpp
 *
 * [3331] Find Subtree Sizes After Changes
 *
 * https://leetcode.com/problems/find-subtree-sizes-after-changes/description/
 *
 * algorithms
 * Medium (54.18%)
 * Likes:    100
 * Dislikes: 37
 * Total Accepted:    15.8K
 * Total Submissions: 29.2K
 * Testcase Example:  '[-1,0,0,1,1,1]\n"abaabc"'
 *
 * You are given a tree rooted at node 0 that consists of n nodes numbered from
 * 0 to n - 1. The tree is represented by an array parent of size n, where
 * parent[i] is the parent of node i. Since node 0 is the root, parent[0] ==
 * -1.
 * 
 * You are also given a string s of length n, where s[i] is the character
 * assigned to node i.
 * 
 * We make the following changes on the tree one time simultaneously for all
 * nodes x from 1 to n - 1:
 * 
 * 
 * Find the closest node y to node x such that y is an ancestor of x, and s[x]
 * == s[y].
 * If node y does not exist, do nothing.
 * Otherwise, remove the edge between x and its current parent and make node y
 * the new parent of x by adding an edge between them.
 * 
 * 
 * Return an array answer of size n where answer[i] is the size of the subtree
 * rooted at node i in the final tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: parent = [-1,0,0,1,1,1], s = "abaabc"
 * 
 * Output: [6,3,1,1,1,1]
 * 
 * Explanation:
 * 
 * The parent of node 3 will change from node 1 to node 0.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: parent = [-1,0,4,0,1], s = "abbba"
 * 
 * Output: [5,2,1,1,1]
 * 
 * Explanation:
 * 
 * The following changes will happen at the same time:
 * 
 * 
 * The parent of node 4 will change from node 1 to node 0.
 * The parent of node 2 will change from node 4 to node 1.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == parent.length == s.length
 * 1 <= n <= 10^5
 * 0 <= parent[i] <= n - 1 for all i >= 1.
 * parent[0] == -1
 * parent represents a valid tree.
 * s consists only of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes1(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> g(n); 
        for (int i = 1; i < n; i++) {
            g[parent[i]].push_back(i);
        }

        vector<int> ancestor(26, -1);
        auto rebuild = [&](auto &rebuild, int x) -> void {
            int sx = s[x] - 'a';
            int old = ancestor[sx];
            ancestor[sx] = x;
            for (int i = g[x].size() - 1; i >= 0; i--) {
                int y = g[x][i];
                int anc = ancestor[s[y] - 'a'];
                if (anc != -1) {
                    g[anc].push_back(y);
                    g[x][i] = -1;
                }
                rebuild(rebuild, y);
            }
            ancestor[sx] = old;
        };
        rebuild(rebuild, 0);
        
        vector<int> ans(n, 1);
        auto dfs = [&](auto &dfs, int x) -> void {
            for (int y : g[x]) {
                if (y != -1) {
                    dfs(dfs, y);
                    ans[x] += ans[y];
                }
            }   
        };
        dfs(dfs, 0);
        return ans;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> g(n); 
        for (int i = 1; i < n; i++) {
            g[parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> ancestor(26, -1);
        auto dfs = [&](auto &dfs, int x) -> void {
            int sx = s[x] - 'a';
            int old = ancestor[sx];
            ancestor[sx] = x;
            for (int y : g[x]) {
                dfs(dfs, y);
                int anc = ancestor[s[y] - 'a'];
                ans[anc < 0 ? x: anc] += ans[y];
            }
            ancestor[sx] = old;
        };
        
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

