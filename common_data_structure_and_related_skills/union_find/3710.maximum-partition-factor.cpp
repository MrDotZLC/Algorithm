/* 
* @lc app=leetcode id=3710 lang=cpp
    3710. Maximum Partition Factor
    Hard
    Topics
    premium lock icon
    Companies
    Hint
    You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the ith point on the Cartesian plane.

    The Manhattan distance between two points points[i] = [xi, yi] and points[j] = [xj, yj] is |xi - xj| + |yi - yj|.

    Split the n points into exactly two non-empty groups. The partition factor of a split is the minimum Manhattan distance among all unordered pairs of points that lie in the same group.

    Return the maximum possible partition factor over all valid splits.

    Note: A group of size 1 contributes no intra-group pairs. When n = 2 (both groups size 1), there are no intra-group pairs, so define the partition factor as 0.

    

    Example 1:

    Input: points = [[0,0],[0,2],[2,0],[2,2]]

    Output: 4

    Explanation:

    We split the points into two groups: {[0, 0], [2, 2]} and {[0, 2], [2, 0]}.

    In the first group, the only pair has Manhattan distance |0 - 2| + |0 - 2| = 4.

    In the second group, the only pair also has Manhattan distance |0 - 2| + |2 - 0| = 4.

    The partition factor of this split is min(4, 4) = 4, which is maximal.

    Example 2:

    Input: points = [[0,0],[0,1],[10,0]]

    Output: 11

    Explanation:​​​​​​​

    We split the points into two groups: {[0, 1], [10, 0]} and {[0, 0]}.

    In the first group, the only pair has Manhattan distance |0 - 10| + |1 - 0| = 11.

    The second group is a singleton, so it contributes no pairs.

    The partition factor of this split is 11, which is maximal.

    

    Constraints:

    2 <= points.length <= 500
    points[i] = [xi, yi]
    -108 <= xi, yi <= 108
*/
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class UnionFind {
    vector<int> fa;
    vector<int> dis; // dis[x] 表示 x 到其代表元的距离

public:
    UnionFind(int n) : fa(n), dis(n) {
        ranges::iota(fa, 0);
    }

    // 返回 x 所在集合的代表元
    // 同时做路径压缩，也就是把 x 所在集合中的所有元素的 fa 都改成代表元
    int find(int x) {
        if (fa[x] != x) {
            int rt = find(fa[x]);
            dis[x] ^= dis[fa[x]]; // 更新 x 到其代表元的距离
            fa[x] = rt;
        }
        return fa[x];
    }

    // 合并两个互斥的点
    // 如果已经合并，返回是否与已知条件矛盾
    bool merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x == y) { // from 和 to 在同一个集合，不合并
            return dis[from] != dis[to]; // 必须在不同集合
        }
        //    2 ------ 4
        //   /        /
        //  1 ------ 3
        // 如果知道 1->2 的距离和 3->4 的距离，现在合并 1 和 3，并传入 1->3 的距离（本题等于 1）
        // 由于 1->3->4 和 1->2->4 的距离相等
        // 所以 2->4 的距离为 (1->3) + (3->4) - (1->2)
        dis[x] = 1 ^ dis[to] ^ dis[from];
        fa[x] = y;
        return true;
    }
};
class Solution {
public:
    // 二分答案+判断二分图
    int maxPartitionFactor1(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 2) {
            return 0;
        }

        auto check = [&](int low) -> bool {
            vector<int> colors(n);

            auto dfs = [&](this auto &&dfs, int x, int c) -> bool {
                colors[x] = c;
                auto &p = points[x];
                for (int y = 0; y < n; y++) {
                    auto &q = points[y];
                    if (x == y || abs(p[0] - q[0]) + abs(p[1] - q[1]) >= low) {
                        continue;
                    }
                    if (colors[y] == c || colors[y] == 0 && !dfs(y, -c)) {
                        return false;
                    }
                }
                return true;
            };

            for (int i = 0; i < n; i++) {
                if (colors[i] == 0 && !dfs(i, 1)) {
                    return false;
                }
            }
            return true;
        };

        int max_dis = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                max_dis = max(max_dis,
                              abs(points[i][0] - points[j][0]) +
                                  abs(points[i][1] - points[j][1]));
            }
        }

        int L = 0, R = max_dis + 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid;
        }
        return L;
    }

    // 加权并查集
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        vector<tuple<int, int, int>> manhattan_tuples;
        manhattan_tuples.reserve(n * (n - 1) / 2); // 预分配空间
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dis = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                manhattan_tuples.emplace_back(dis, i, j);
            }
        }
        ranges::sort(manhattan_tuples, {}, [](const auto& t) { return get<0>(t); });

        UnionFind uf(n);
        for (auto& [dis, x, y] : manhattan_tuples) {
            if (!uf.merge(x, y)) {
                return dis; // x 和 y 必须在同一个集合，dis 就是这一划分的最小划分因子
            }
        }
        return 0;
    }
};
// @lc code=end