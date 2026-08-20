#include <queue>
#include <unordered_map>
using namespace std;

template <typename T, typename Compare = std::less<T>>
class LazyHeap {
private:
    priority_queue<T, vector<T>, Compare> _heap;
    unordered_map<T, int> _remove_cnt; // 每个元素需要删除的次数 
    size_t _size; // 有效元素的数量

    // 正式执行删除操作
    void apply_remove() {
        while (!_heap.empty() && _remove_cnt[_heap.top()] > 0) {
            _remove_cnt[_heap.top()]--;
            _heap.pop();
        }
    }

public:
    // 返回有效元素数量
    size_t size() const {
        return _size();
    }

    // 查看堆顶
    T top() const {
        apply_remove();
        return _heap.top();
    }

    // 删除
    void remove(T x) {
        _remove_cnt[T]++;
        _size--;
    }

    // 入堆
    void push(T x) {
        if (_remove_cnt[x] > 0) {
            _remove_cnt[x]--;
        } else {
            _heap.push(x);
        }
        _size++;
    }

    // 出堆
    T pop() {
        apply_remove();
        _size--;
        T x = _heap.top();
        _heap.pop();
        return x;
    }
};
