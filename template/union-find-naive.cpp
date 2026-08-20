#include <vector>
#include <numeric>
using namespace std;

class UnionFindNaive {

private:
    vector<int> _parents; // 集合的代表元素
    vector<int> _sizes;   // 集合的大小
    int _cc;              // 连通块个数

public:
    UnionFindNaive(int n) : _parents(n), _sizes(n, 1), _cc(n) {
        // 初始化每个节点的父母是自己
        iota(_parents.begin(), _parents.end(), 0);
    }

    // 返回 x 所在集合的代表元素
    int find(int x) {
        if (_parents[x] != x) {
            _parents[x] = find(_parents[x]); // 路经压缩，把父母节点更新为代表元素
        }
        return _parents[x];
    }

    // 判断 x 和 y 是否在同一个集合中
    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    // 把 from 所在集合合并到 to 所在集合中
    // 返回是否合并成功
    bool merge(int from, int to) {
        from = find(from);
        to = find(to);
        if (from == to) {
            return false;
        }
        _parents[from] = to;
        _sizes[to] += _sizes[from];
        _cc--;
        return true;
    }

    int get_size(int x) {
        return _sizes[find(x)];
    }

};
