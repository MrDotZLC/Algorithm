/*
 * @lc app=leetcode id=2440 lang=cpp
 *
 * [2440] Create Components With Same Value
 *
 * https://leetcode.com/problems/create-components-with-same-value/description/
 *
 * algorithms
 * Hard (52.12%)
 * Likes:    425
 * Dislikes: 7
 * Total Accepted:    9.8K
 * Total Submissions: 18.6K
 * Testcase Example:  '[6,2,2,2,6]\n[[0,1],[1,2],[1,3],[3,4]]'
 *
 * There is an undirected tree with n nodes labeled from 0 to n - 1.
 * 
 * You are given a 0-indexed integer array nums of length n where nums[i]
 * represents the value of the i^th node. You are also given a 2D integer array
 * edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an
 * edge between nodes ai and bi in the tree.
 * 
 * You are allowed to delete some edges, splitting the tree into multiple
 * connected components. Let the value of a component be the sum of all nums[i]
 * for which node i is in the component.
 * 
 * Return the maximum number of edges you can delete, such that every connected
 * component in the tree has the same value.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]] 
 * Output: 2 
 * Explanation: The above figure shows how we can delete the edges [0,1] and
 * [3,4]. The created components are nodes [0], [1,2,3] and [4]. The sum of the
 * values in each component equals 6. It can be proven that no better deletion
 * exists, so the answer is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2], edges = []
 * Output: 0
 * Explanation: There are no edges to be deleted.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 2 * 10^4
 * nums.length == n
 * 1 <= nums[i] <= 50
 * edges.length == n - 1
 * edges[i].length == 2
 * 0 <= edges[i][0], edges[i][1] <= n - 1
 * edges represents a valid tree.
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        vector<vector<int>> g(nums.size());
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int target;
        auto dfs = [&](auto &dfs, int x, int parent) -> int {
            int sum = nums[x];
            for (int y : g[x]) {
                if (y != parent) {
                    int res = dfs(dfs, y, x);
                    if (res < 0) {
                        return -1;
                    }
                    sum += res;
                }
            }
            if (sum > target) {
                return -1;
            }
            return sum < target ? sum : 0;
        };

        int total = reduce(nums.begin(), nums.end());
        int mx = ranges::max(nums);
        for (int i = total / mx; ;i--) {
            if (total % i == 0) {
                target = total / i;
                if (dfs(dfs, 0, -1) == 0) {
                    return i - 1;
                }
            }
        }
    }
};
// @lc code=end

