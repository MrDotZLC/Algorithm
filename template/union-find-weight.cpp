#include <vector>
#include <numeric>
using namespace std;

template<typename T>
class UnionFindWeight {

private:
    vector<int> _parents; // 集合的代表元素
    vector<T> _dis;   // 集合的大小
    int _cc;              // 连通块个数

public:
    UnionFindWeight(int n) : _parents(n), _dis(n), _cc(n) {
        iota(_parents.begin(), _parents.end(), 0);
    }

    // 返回 x 所在集合的代表元素，同时做路经压缩
    int find(int x) {
        if (_parents[x] != x) {
            int root = find(_parents[x]);
            _dis[x] += _dis[_parents[x]];
            _parents[x] = root;
        }
        return _parents[x];
    }

    // 判断 x 和 y 是否在同一个集合中
    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    // 计算从 from 到 to 的距离，需保证在同一集合
    T distance(int from, int to) {
        find(from);
        find(to);
        return _dis[from] - _dis[to];
    }

    // 把 from 所在集合合并到 to 所在集合中
    // 返回是否合并成功
    bool merge(int from, int to, T value) {
        int x = find(from);
        int y = find(to);
        if (from == to) {
            return _dis[from] - _dis[to] == value;
        }
        //    x --------- y
        //   /           /
        // from ------- to
        // 已知 x-from = dis[from] 和 y-to = dis[to]，现在合并 from 和 to，新增信息 to-from = value
        // 由于 y-from = (y-x) + (x-from) = (y-to) + (to-from)
        // 所以 y-x = (to-from) + (y-to) - (x-from) = value + dis[to] - dis[from]
        _parents[from] = to;
        _dis[from] = value + _dis[to] - _dis[from];
        return true;
    }
};
