/*
 * @lc app=leetcode id=3515 lang=cpp
 *
 * [3515] Shortest Path in a Weighted Tree
 *
 * https://leetcode.com/problems/shortest-path-in-a-weighted-tree/description/
 *
 * algorithms
 * Hard (32.60%)
 * Likes:    53
 * Dislikes: 2
 * Total Accepted:    5K
 * Total Submissions: 13.9K
 * Testcase Example:  '2\n[[1,2,7]]\n[[2,2],[1,1,2,4],[2,2]]'
 *
 * You are given an integer n and an undirected, weighted tree rooted at node 1
 * with n nodes numbered from 1 to n. This is represented by a 2D array edges
 * of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge
 * from node ui to vi with weight wi.
 * 
 * You are also given a 2D integer array queries of length q, where each
 * queries[i] is either:
 * 
 * 
 * [1, u, v, w'] – Update the weight of the edge between nodes u and v to w',
 * where (u, v) is guaranteed to be an edge present in edges.
 * [2, x] – Compute the shortest path distance from the root node 1 to node
 * x.
 * 
 * 
 * Return an integer array answer, where answer[i] is the shortest path
 * distance from node 1 to x for the i^th query of [2, x].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
 * 
 * Output: [7,4]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Query [2,2]: The shortest path from root node 1 to node 2 is 7.
 * Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
 * Query [2,2]: The shortest path from root node 1 to node 2 is 4.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, edges = [[1,2,2],[1,3,4]], queries =
 * [[2,1],[2,3],[1,1,3,7],[2,2],[2,3]]
 * 
 * Output: [0,4,2,7]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Query [2,1]: The shortest path from root node 1 to node 1 is 0.
 * Query [2,3]: The shortest path from root node 1 to node 3 is 4.
 * Query [1,1,3,7]: The weight of edge (1,3) changes from 4 to 7.
 * Query [2,2]: The shortest path from root node 1 to node 2 is 2.
 * Query [2,3]: The shortest path from root node 1 to node 3 is 7.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 4, edges = [[1,2,2],[2,3,1],[3,4,5]], queries =
 * [[2,4],[2,3],[1,2,3,3],[2,2],[2,3]]
 * 
 * Output: [8,3,2,5]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Query [2,4]: The shortest path from root node 1 to node 4 consists of edges
 * (1,2), (2,3), and (3,4) with weights 2 + 1 + 5 = 8.
 * Query [2,3]: The shortest path from root node 1 to node 3 consists of edges
 * (1,2) and (2,3) with weights 2 + 1 = 3.
 * Query [1,2,3,3]: The weight of edge (2,3) changes from 1 to 3.
 * Query [2,2]: The shortest path from root node 1 to node 2 is 2.
 * Query [2,3]: The shortest path from root node 1 to node 3 consists of edges
 * (1,2) and (2,3) with updated weights 2 + 3 = 5.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * edges.length == n - 1
 * edges[i] == [ui, vi, wi]
 * 1 <= ui, vi <= n
 * 1 <= wi <= 10^4
 * The input is generated such that edges represents a valid tree.
 * 1 <= queries.length == q <= 10^5
 * queries[i].length == 2 or 4
 * 
 * queries[i] == [1, u, v, w'] or,
 * queries[i] == [2, x]
 * 1 <= u, v, x <= n
 * (u, v) is always an edge from edges.
 * 1 <= w' <= 10^4
 * 
 * 
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
template<typename T>
class FenwickTree {
public:
    FenwickTree(int n) : _tree(n + 1) {}; // 使用下标1 ~ n+1

    void update(int i, T val) { // a[i] 增加 val
        for (; i < _tree.size(); i += i & -i) {
            _tree[i] += val;
        }
    }

    T pre(int i) const {// 求前缀和 a[1] + ... + a[i]
        T res = 0;
        // i &= i - 1 等价于 i -= i & -i
        // 含义均为 清除最低位的1
        for (; i > 0; i &= i - 1) {
            res += _tree[i];
        }
        return res;
    }

    T range(int l, int r) const { 
        return pre(r) - pre(l - 1); 
    }

private:
    vector<T> _tree;
};

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<int>> g(n + 1);
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> in(n + 1), out(n + 1);
        int clock = 0;
        auto dfs = [&](auto &dfs, int x, int parent) -> void {
            in[x] = ++clock;
            for (int y : g[x]) {
                if (y != parent) {
                    dfs(dfs, y, x);
                }
            }
            out[x] = clock;
        };
        dfs(dfs, 1, 0);

        // 对于一条边 x-y（y 是 x 的儿子），把边权保存在 weight[y] 中
        vector<int> weight(n + 1);
        FenwickTree<int> diff(n);
        auto update = [&](int x, int y, int w) {
            // 确保y是x的儿子
            if (in[x] > in[y]) {
                y = x;
            }
            int d = w - weight[y];
            weight[y] = w;
            diff.update(in[y], d); // 更新差分
            diff.update(out[y] + 1, -d); // 更新差分
        };

        for (auto &e : edges) {
            update(e[0], e[1], e[2]);
        }

        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                update(q[1], q[2], q[3]);
            } else {
                ans.push_back(diff.pre(in[q[1]]));
            }
        }
        return ans;
    }
};
// @lc code=end

