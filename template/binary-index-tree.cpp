#include <vector>

using namespace std;

// 树状数组（Binary Index Tree）
// 用于维护一个数组的前缀和，支持单点更新和区间查询
// 用最低位的1来表示区间的长度，BIT[i]表示区间[i - (i & -i) + 1, i]的和
template<typename T>
class BinaryIndexTree {

public:
    BinaryIndexTree(int n) : _tree(n + 1) {}

    // 单点更新
    void update(int i, int val) {
        // 更新所有包含 i 的区间（）
        for (;i < _tree.size(); i += i & -i) {
            _tree[i] += val;
        }
    }

    // 区间查询 [1, i] 的和
    T pre(int i) const {
        T res = 0;
        // 查询所有包含 i 的区间（每次清除最低位的1）
        for (; i > 0; i -= (i & -i)) {
            res += _tree[i];
        }
        return res;
    }

    // 区间查询 [l, r] 的和
    T range(int l, int r) const {
        return pre(r) - pre(l - 1);
    }

private:
    vector<int> _tree;
};