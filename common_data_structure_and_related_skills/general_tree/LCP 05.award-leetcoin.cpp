/* 
    LCP 05. 发 LeetCoin
    同步题目状态

    困难
    相关标签
    premium lock icon
    相关企业
    力扣决定给一个刷题团队发LeetCoin作为奖励。同时，为了监控给大家发了多少LeetCoin，力扣有时候也会进行查询。
    

    该刷题团队的管理模式可以用一棵树表示：
    团队只有一个负责人，编号为1。除了该负责人外，每个人有且仅有一个领导（负责人没有领导）；
    不存在循环管理的情况，如A管理B，B管理C，C管理A。
    

    力扣想进行的操作有以下三种：
    给团队的一个成员（也可以是负责人）发一定数量的LeetCoin；
    给团队的一个成员（也可以是负责人），以及他/她管理的所有人（即他/她的下属、他/她下属的下属，……），发一定数量的LeetCoin；
    查询某一个成员（也可以是负责人），以及他/她管理的所有人被发到的LeetCoin之和。
    

    输入：
    N表示团队成员的个数（编号为1～N，负责人为1）；
    leadership是大小为(N - 1) * 2的二维数组，其中每个元素[a, b]代表b是a的下属；
    operations是一个长度为Q的二维数组，代表以时间排序的操作，格式如下：
    operations[i][0] = 1: 代表第一种操作，operations[i][1]代表成员的编号，operations[i][2]代表LeetCoin的数量；
    operations[i][0] = 2: 代表第二种操作，operations[i][1]代表成员的编号，operations[i][2]代表LeetCoin的数量；
    operations[i][0] = 3: 代表第三种操作，operations[i][1]代表成员的编号；

    输出：
    返回一个数组，数组里是每次查询的返回值（发LeetCoin的操作不需要任何返回值）。由于发的LeetCoin很多，请把每次查询的结果模1e9+7 (1000000007)。

    示例 1：
    输入：N = 6, leadership = [[1, 2], [1, 6], [2, 3], [2, 5], [1, 4]], operations = [[1, 1, 500], [2, 2, 50], [3, 1], [2, 6, 15], [3, 1]]
    输出：[650, 665]
    解释：团队的管理关系见下图。
    第一次查询时，每个成员得到的LeetCoin的数量分别为（按编号顺序）：500, 50, 50, 0, 50, 0;
    第二次查询时，每个成员得到的LeetCoin的数量分别为（按编号顺序）：500, 50, 50, 0, 50, 15.

    限制：
    1 <= N <= 50000
    1 <= Q <= 50000
    operations[i][0] != 3 时，1 <= operations[i][2] <= 5000
*/
#include <vector>
using namespace std;
// @lc code=start
class BIT {
// 区间更新 + 区间查询公式推导:
//
// 差分数组 d 定义：
//    d[i] = a[i] - a[i-1]   (a[0] = 0)
//
// 原数组 a[i] 可以由 d 还原：
//    a[i] = d[1] + d[2] + ... + d[i]
//
// 区间和 [1..x] = a[1] + a[2] + ... + a[x]
//                = sum_{i=1..x} a[i]
//                = sum_{i=1..x} (sum_{j=1..i} d[j])
//
// 交换求和顺序（按列累加）：
//                = sum_{j=1..x} (sum_{i=j..x} d[j])
//                = sum_{j=1..x} d[j] * (x - j + 1)
//
// 拆分公式：
//    sum_{j=1..x} d[j] * (x - j + 1)
//  = sum_{j=1..x} d[j] * x - sum_{j=1..x} d[j] * (j-1)
//  = x * prefix_sum(d, x) - prefix_sum(d[j]*(j-1), x)
//
// 在 BIT 中对应：
//    sum[]        存储 prefix_sum(d, x)
//    ntimessum[]  存储 prefix_sum(d[j]*(j-1), x)
//
// 区间和 [l..r] = askii(r) - askii(l-1)
public:
    BIT(int n) : _n(n), _sum(n + 1), _weight_sum(n + 1) {}

    long long lowbit(long long x) {
        return x & (-x);
    }

    void update_interval(int l, int r, long long val) {
        update(l, val);
        update(r + 1, -val);
    }

    long long query_based_PU(int l, int r) { // PU: point update
        if (l > r) {
            return 0;
        }
        return base_query(r) - base_query(l - 1);
    }

    long long query_based_PU(int pos) { // PU: point update
        return query_based_PU(pos, pos);
    }

    long long query_based_RU(int l, int r) { // RU: Range update
        if (l > r) {
            return 0;
        }
        return query_based_range_update(r) - query_based_range_update(l - 1);
    }

    long long query_based_RU(int pos) { // RU: Range update
        return query_based_range_update(pos);
    }

private:
    int _n;
    vector<long long> _sum; // 前缀和
    vector<long long> _weight_sum; // 加权前缀和 (j - 1)∑d[j]

    void update(int pos, long long val) {
        long long x = pos;
        while (pos <= _n) {
            _sum[pos] += val;
            _weight_sum[pos] += val * (x - 1); 
            pos += lowbit(pos);
        }
    }

    long long base_query(int pos) {
        if (!pos) {
            return 0;
        }
        long long res = 0;
        while (pos) {
            res += _sum[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    long long query_based_range_update(int pos) {
        if (!pos) {
            return 0;
        }
        long long res = 0, x = pos;
        while (pos) {
            res += x * _sum[pos] - _weight_sum[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

};

class Solution {
public:
    int MOD = 1e9 + 7;
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        vector<vector<int>> g(n + 1);
        for (auto& e : leadership) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
        }

        vector<int> in(n + 1), out(n + 1);
        int clock = 0;
        auto dfs = [&](auto &dfs, int x) -> void {
            in[x] = ++clock;
            for (int y : g[x]) {
                dfs(dfs, y);
            }
            out[x] = clock;
        };
        dfs(dfs, 1);

        BIT tree(n);
        vector<int> ans;
        for (auto &o : operations) {
            if (o[0] == 1) {
                tree.update_interval(in[o[1]], in[o[1]], o[2]);
            } else if (o[0] == 2) {
                tree.update_interval(in[o[1]], out[o[1]], o[2]);
            } else {
                long long res = tree.query_based_RU(in[o[1]], out[o[1]]);
                ans.push_back((res % MOD + MOD) % MOD);
            }
        }
        return ans;
    }
};
// @lc code=end

