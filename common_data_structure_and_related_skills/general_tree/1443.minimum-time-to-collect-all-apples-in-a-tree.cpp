/*
 * @lc app=leetcode id=1443 lang=cpp
 *
 * [1443] Minimum Time to Collect All Apples in a Tree
 *
 * https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/description/
 *
 * algorithms
 * Medium (63.08%)
 * Likes:    3797
 * Dislikes: 331
 * Total Accepted:    146.6K
 * Total Submissions: 231.9K
 * Testcase Example:  '7\n' +
  '[[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]]\n' +
  '[false,false,true,false,true,true,false]'
 *
 * Given an undirected tree consisting of n vertices numbered from 0 to n-1,
 * which has some apples in their vertices. You spend 1 second to walk over one
 * edge of the tree. Return the minimum time in seconds you have to spend to
 * collect all apples in the tree, starting at vertex 0 and coming back to this
 * vertex.
 * 
 * The edges of the undirected tree are given in the array edges, where
 * edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and
 * bi. Additionally, there is a boolean array hasApple, where hasApple[i] =
 * true means that vertex i has an apple; otherwise, it does not have any
 * apple.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
 * [false,false,true,false,true,true,false]
 * Output: 8 
 * Explanation: The figure above represents the given tree where red vertices
 * have an apple. One optimal path to collect all apples is shown by the green
 * arrows.  
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
 * [false,false,true,false,false,true,false]
 * Output: 6
 * Explanation: The figure above represents the given tree where red vertices
 * have an apple. One optimal path to collect all apples is shown by the green
 * arrows.  
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
 * [false,false,false,false,false,false,false]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * edges.length == n - 1
 * edges[i].length == 2
 * 0 <= ai < bi <= n - 1
 * hasApple.length == n
 * 
 * 
 */
#include <vector>
#include <map>
using namespace std;
// @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        int ans = 0;
        vector<int> parents(n, -1);
        vector<bool> visited(n, false);
        visited[0] = true;

        auto build_parents = [&](this auto &&build_parents, map<int,vector<int>>& m, int val) -> void {
            for (auto x : m[val]) {
                if (x != 0 && parents[x] == -1) {
                    parents[x] = val;
                    build_parents(m, x);
                }
            }
        };

        map<int,vector<int>> m;
        for (auto &e : edges) {
            m[e[0]].emplace_back(e[1]);
            m[e[1]].emplace_back(e[0]);
        }
        build_parents(m, 0);

        auto dfs = [&](auto &dfs, int x) -> void {
            if (!visited[x]) {
                visited[x] = true;
                ans++;
                dfs(dfs, parents[x]);
            }
        };
        
        for (int i = 0; i < n; i++) {
            if (hasApple[i]) {
                dfs(dfs, i);
            }
        }
        return ans * 2;
    }
};
// @lc code=end

