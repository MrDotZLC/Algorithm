#include <vector>
#include <iostream>


using namespace std;

template <typename T, typename Compare = std::less<T>>
class Heap {

public:
    Heap() = default;

    explicit Heap(const Compare& compare) : _compare(compare) {}

    // 插入
    void push(const T& value) {
        _heap.push_back(value);
        sift_up(_heap.size() - 1);
    }

    // 删除堆顶
    void pop() {
        if (_heap.empty()) {
            return;
        }

        _heap[0] = std::move(_heap.back());
        _heap.pop_back();

        if (!_heap.empty()) {
            sift_down(0);
        }
    }

    // 获取堆顶元素
    const T& top() const {
        return _heap[0];
    }

    bool empty() const {
        return _heap.empty();
    }

    size_t size() const {
        return _heap.size();
    }

private:
    std::vector<T> _heap;
    Compare _compare;

    // 向上调整
    void sift_up(size_t i) {
        while (i > 0) {
            size_t pa = (i - 1) / 2;

            // 如果父节点已拥有更高优先级
            if (!_compare(_heap[pa], _heap[i])) {
                break;
            }

            swap(_heap[pa], _heap[i]);
            i = pa;
        }
    }

    // 向下调整
    void sift_down(size_t i) {
        size_t n = _heap.size();

        while (true) {
            size_t l = 2 * i + 1;
            size_t r = 2 * i + 2;
            size_t best = i;

            // 左孩子优先级更高
            if (l < n && _compare(_heap[best], _heap[l])) {
                best = l;
            }

            // 右孩子优先级更高
            if (r < n && _compare(_heap[best], _heap[r])) {
                best = r;
            }

            if (best == i) {
                break;
            }

            swap(_heap[i], _heap[best]);
            i = best;
        }
    }
};

int main() {
    // 大根堆
    Heap<int, less<int>> maxHeap;

    maxHeap.push(3);
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(1);
    maxHeap.push(8);

    while (!maxHeap.empty()) {
        cout << maxHeap.top() << ' ';
        maxHeap.pop();
    }

    cout << '\n';

    // 小根堆
    Heap<int, greater<int>> minHeap;

    minHeap.push(3);
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(1);
    minHeap.push(8);

    while (!minHeap.empty()) {
        cout << minHeap.top() << ' ';
        minHeap.pop();
    }

    cout << '\n';
}