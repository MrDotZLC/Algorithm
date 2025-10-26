/*
 * @lc app=leetcode id=3493 lang=cpp
 *
 * [3493] Properties Graph
 *
 * https://leetcode.com/problems/properties-graph/description/
 *
 * algorithms
 * Medium (47.05%)
 * Likes:    85
 * Dislikes: 13
 * Total Accepted:    23.4K
 * Total Submissions: 49K
 * Testcase Example:  '[[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]]\n1'
 *
 * You are given a 2D integer array properties having dimensions n x m and an
 * integer k.
 * 
 * Define a function intersect(a, b) that returns the number of distinct
 * integers common to both arrays a and b.
 * 
 * Construct an undirected graph where each index i corresponds to
 * properties[i]. There is an edge between node i and node j if and only if
 * intersect(properties[i], properties[j]) >= k, where i and j are in the range
 * [0, n - 1] and i != j.
 * 
 * Return the number of connected components in the resulting graph.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The graph formed has 3 connected components:
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: properties = [[1,2,3],[2,3,4],[4,3,5]], k = 2
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * The graph formed has 1 connected component:
 * 
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: properties = [[1,1],[1,1]], k = 2
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * intersect(properties[0], properties[1]) = 1, which is less than k. This
 * means there is no edge between properties[0] and properties[1] in the
 * graph.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n == properties.length <= 100
 * 1 <= m == properties[i].length <= 100
 * 1 <= properties[i][j] <= 100
 * 1 <= k <= m
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <numeric>
using namespace std;
// @lc code=start
class UnionFind {
public:
    UnionFind(int n) : fa(n), sz(n, 1), cc(n) {
        // 一开始有n个集合{0}, {1}, ..., {n - 1}
        // 集合 i 的代表元是自己，大小为1
        ranges::iota(fa, 0);
    }

    // 返回 x 所在集合的代表元
    // 同时做路径压缩，也就是把 x 所在集合中的所有元素的 fa 都改成代表元
    int find(int x) {
        // 如果 fa[x] == x，则表示x就是代表元
        if (fa[x] == x) {
            return x;
        }
        return find(fa[x]);
    }

    // 判断 x 和 y 是否在同一集合
    bool is_same(int x, int y) {
        // 如果 x 的代表元和 y 的代表元相同，代表 x 和 y 在同一集合
        return find(x) == find(y);
    }

    // 把 from 所在集合合并到 to 所在集合中
    // 返回是否合并成功
    bool merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x == y) { // x 和 y 在同一集合，不做合并
            return false;
        }
        fa[x] = y;
        sz[y] += sz[x]; // sz[x]无需重置，因为只会访问sz[find(x)]，不会再访问sz[x]
        cc--;
        return true;
    }

    // 返回 x 所在集合的大小
    int get_size(int x) {
        return sz[find(x)];
    }

    // 返回连通块个数
    int get_cc() {
        return cc;
    }

private:
    vector<int> fa;
    vector<int> sz;
    int cc = 0;
};
class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        vector<unordered_set<int>> sets(n);
        for (int i = 0; i < n; i++) {
            sets[i] = unordered_set<int>(properties[i].begin(), properties[i].end());
        }

        UnionFind uf(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int cnt = 0;
                for (int x : sets[j]) {
                    cnt += sets[i].contains(x);
                }
                if (cnt >= k) {
                    uf.merge(i, j);
                }
            }
        }
        return uf.get_cc();
    }
};
// @lc code=end

