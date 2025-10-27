/*
 * @lc app=leetcode id=1782 lang=cpp
 *
 * [1782] Count Pairs Of Nodes
 *
 * https://leetcode.com/problems/count-pairs-of-nodes/description/
 *
 * algorithms
 * Hard (41.06%)
 * Likes:    333
 * Dislikes: 170
 * Total Accepted:    8.5K
 * Total Submissions: 20.7K
 * Testcase Example:  '4\n[[1,2],[2,4],[1,3],[2,3],[2,1]]\n[2,3]'
 *
 * You are given an undirected graph defined by an integer n, the number of
 * nodes, and a 2D integer array edges, the edges in the graph, where edges[i]
 * = [ui, vi] indicates that there is an undirected edge between ui and vi. You
 * are also given an integer array queries.
 * 
 * Let incident(a, b) be defined as the number of edges that are connected to
 * either node a or b.
 * 
 * The answer to the j^th query is the number of pairs of nodes (a, b) that
 * satisfy both of the following conditions:
 * 
 * 
 * a < b
 * incident(a, b) > queries[j]
 * 
 * 
 * Return an array answers such that answers.length == queries.length and
 * answers[j] is the answer of the j^th query.
 * 
 * Note that there can be multiple edges between the same two nodes.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
 * Output: [6,5]
 * Explanation: The calculations for incident(a, b) are shown in the table
 * above.
 * The answers for each of the queries are as follows:
 * - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
 * - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value
 * greater than 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5, edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]],
 * queries = [1,2,3,4,5]
 * Output: [10,10,9,8,6]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 2 * 10^4
 * 1 <= edges.length <= 10^5
 * 1 <= ui, vi <= n
 * ui != vi
 * 1 <= queries.length <= 20
 * 0 <= queries[j] < edges.length
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> deg(n + 1);
        unordered_map<int, int> freq;
        // 存储每个点的度数
        // 存储每个点对的不重复度数和，使用十六进制位运算使点对哈希化
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            if (x > y) swap(x, y);
            deg[x]++;
            deg[y]++;
            freq[x << 16 | y]++;
        }

        // 使用双指针得出所有符合两点度数大于查询的方案数
        vector<int> ans(queries.size());
        vector<int> sorted_deg = deg;
        sort(sorted_deg.begin(), sorted_deg.end());
        for (int i = 0; i < queries.size(); i++) {
            int q = queries[i];
            int l = 1, r = n;
            while (l < r) {
                if (sorted_deg[l] + sorted_deg[r] <= q) {
                    l++;
                } else {
                    ans[i] += r - l;
                    r--;
                }
            }
            for (auto [hash, repeat] : freq) {
                int sum = deg[hash >> 16] + deg[hash & 0xffff];
                if (sum > q && sum - repeat <= q) {
                    ans[i]--;
                }
                cout << repeat << endl;
            }
        }
        return ans;
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<vector<int>> edges = {{1,2}, {2,4}, {1,3}, {2,3}, {2,1}};
    vector<int> queries = {2, 3};
    sol.countPairs(4, edges, queries);
}