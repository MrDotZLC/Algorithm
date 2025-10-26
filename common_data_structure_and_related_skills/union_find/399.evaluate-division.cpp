/*
 * @lc app=leetcode id=399 lang=cpp
 *
 * [399] Evaluate Division
 *
 * https://leetcode.com/problems/evaluate-division/description/
 *
 * algorithms
 * Medium (63.27%)
 * Likes:    10007
 * Dislikes: 1066
 * Total Accepted:    651.3K
 * Total Submissions: 1M
 * Testcase Example:  '[["a","b"],["b","c"]]\n' +
  '[2.0,3.0]\n' +
  '[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]'
 *
 * You are given an array of variable pairs equations and an array of real
 * numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
 * equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
 * single variable.
 * 
 * You are also given some queries, where queries[j] = [Cj, Dj] represents the
 * j^th query where you must find the answer for Cj / Dj = ?.
 * 
 * Return the answers to all queries. If a single answer cannot be determined,
 * return -1.0.
 * 
 * Note: The input is always valid. You may assume that evaluating the queries
 * will not result in division by zero and that there is no contradiction.
 * 
 * Note: The variables that do not occur in the list of equations are
 * undefined, so the answer cannot be determined for them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
 * [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 * Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
 * Explanation: 
 * Given: a / b = 2.0, b / c = 3.0
 * queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
 * return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
 * note: x is undefined => -1.0
 * 
 * Example 2:
 * 
 * 
 * Input: equations = [["a","b"],["b","c"],["bc","cd"]], values =
 * [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 * Output: [3.75000,0.40000,5.00000,0.20000]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: equations = [["a","b"]], values = [0.5], queries =
 * [["a","b"],["b","a"],["a","c"],["x","y"]]
 * Output: [0.50000,2.00000,-1.00000,-1.00000]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= equations.length <= 20
 * equations[i].length == 2
 * 1 <= Ai.length, Bi.length <= 5
 * values.length == equations.length
 * 0.0 < values[i] <= 20.0
 * 1 <= queries.length <= 20
 * queries[i].length == 2
 * 1 <= Cj.length, Dj.length <= 5
 * Ai, Bi, Cj, Dj consist of lower case English letters and digits.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;
// @lc code=start
class UnionFind {
public:
    UnionFind(int n) : pa(n), mul(n, 1) {
        // 一开始有 n 个集合 {0}, {1}, ..., {n-1}
        // 集合 i 的代表元是自己，自己 * 1 = 自己
        ranges::iota(pa, 0);
    }

    // 返回 x 所在集合的代表元
    // 同时做路径压缩，也就是把 x 所在集合中的所有元素的 fa 都改成代表元
    int find (int x) {
        if (x != pa[x]) {
            int root = find(pa[x]);
            mul[x] *= mul[pa[x]];
            pa[x] = root;
        }
        return pa[x];
    }

    // 判断 x 和 y 是否在同一个集合
    bool is_same(int x, int y) {
        // 如果 x 的代表元和 y 的代表元相同，那么 x 和 y 就在同一个集合
        // 这就是代表元的作用：用来快速判断两个元素是否在同一个集合
        return find(x) == find(y);
    }

    // 合并 from 和 to，新增信息 to / from = value
    // 其中 to 和 from 表示未知量，下文的 x 和 y 也表示未知量
    void merge(int from, int to, double value) {
        int x = find(from), y = find(to);
        if (x != y) {
            //    x --------- y
            //   /           /
            // from ------- to
            // 已知 x/from = mul[from] 和 y/to = mul[to]，现在合并 from 和 to，新增信息 to/from = value
            // 由于 y/from = (y/x) * (x/from) = (y/to) * (to/from)
            // 所以 y/x = (y/to) * (to/from) / (x/from) = mul[to] * value / mul[from]
            mul[x] = mul[to] * value / mul[from];
            pa[x] = y;
        }
    }

    double get_mul(int x) {
        return mul[x];
    }
private:
    vector<int> pa;
    vector<double> mul;
};
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, int> variable_to_id;
        for (auto &equation : equations) {
            for (auto &s : equation) {
                if (!variable_to_id.contains(s)) {
                    variable_to_id[s] = variable_to_id.size();
                }
            }
        }

        UnionFind uf(variable_to_id.size());
        for (int i = 0; i < equations.size(); i++) {
            uf.merge(variable_to_id[equations[i][1]], variable_to_id[equations[i][0]], values[i]);
        }

        vector<double> ans;
        for (auto q : queries) {
            auto it_c = variable_to_id.find(q[0]);
            if (it_c == variable_to_id.end()) {
                ans.push_back(-1);
                continue;
            }

            auto it_d = variable_to_id.find(q[1]);
            if (it_d == variable_to_id.end() || !uf.is_same(it_c->second, it_d->second)) {
                ans.push_back(-1);
                continue;
            }

            ans.push_back(uf.get_mul(it_d->second) / uf.get_mul(it_c->second));
        }
        return ans;
    }
};
// @lc code=end

