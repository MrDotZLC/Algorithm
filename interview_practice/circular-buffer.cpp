#include <vector>
#include <stdexcept>
#include <atomic>
#include <optional>
#include <iostream>
using namespace std;

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(int cap) 
        : buf_(cap), cap_(cap), head_(0), tail_(0), size_(0) {}
    
    void push(const T& val) {
        if (full()) {
            throw runtime_error("CircularBuffer is full");
        }
        buf_[tail_] = val;
        tail_ = (tail_ + 1) % cap_;
        ++size_;
    }

    optional<T> pop() {
        if (empty()) {
            return nullopt;
        }
        T val = buf_[head_];
        head_ = (head_ + 1) % cap_;
        --size_;
        return val;
    }

    T& front() {
        if (empty()) {
            throw runtime_error("CircularBuffer is empty");
        }
        return buf_[head_];
    }

    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == cap_; }
    int size() const { return size_; }
    int capacity() const { return cap_; }

private:
    vector<T> buf_;
    int cap_;
    int head_;
    int tail_;
    int size_;
};

// 无锁 SPSC 单生产者单消费者 循环队列
// 注意：cap 必须为 2 的幂，利用位掩码替代取模（更快）
template<typename T>
class SPSCCirCularBuffer {
public:
    explicit SPSCCirCularBuffer(int cap)
        : buf_(cap), mask_(cap - 1), head_(0), tail_(0) {
        if ((cap & mask_) != 0) {
            throw runtime_error("cap must be a power of 2!");
        }
    }

    bool push(const T& val) {
        size_t tail = tail_.load(memory_order_relaxed);
        size_t next = (tail + 1) & mask_;
        if (next == head_.load(memory_order_acquire)) {
            return false;
        }
        buf_[tail] = val;
        tail_.store(next, memory_order_release);
        return true;
    }

    optional<T> pop() {
        size_t head = head_.load(memory_order_relaxed);
        if (head == tail_.load(memory_order_acquire)) {
            return nullopt;
        }
        T val = buf_[head];
        head_.store((head + 1) & mask_, memory_order_release);
        return val;
    }

private:
    vector<T> buf_;
    size_t mask_;
    atomic<size_t> head_;
    char pad[64 - sizeof(size_t)];
    atomic<size_t> tail_;
};

int main() {
    CircularBuffer<int> buffer(3);

    cout << "capacity = "
         << buffer.capacity()
         << endl;

    cout << "empty = "
         << buffer.empty()
         << endl;


    // push
    cout << "\nPush 10, 20, 30\n";

    buffer.push(10);
    buffer.push(20);
    buffer.push(30);


    cout << "size = "
         << buffer.size()
         << endl;

    cout << "front = "
         << buffer.front()
         << endl;


    // 测试满
    try {
        buffer.push(40);
    }
    catch (const exception& e) {
        cout << "push error: "
             << e.what()
             << endl;
    }


    // pop
    cout << "\nPop elements:\n";

    while (!buffer.empty()) {
        cout << buffer.pop().value_or(-1) << endl;
    }


    // 测试空
    try {
        buffer.pop();
    }
    catch (const exception& e) {
        cout << "pop error: "
             << e.what()
             << endl;
    }


    // 测试循环覆盖逻辑
    cout << "\nTest circular behavior:\n";

    buffer.push(1);
    buffer.push(2);

    cout << "pop: "
         << buffer.pop().value_or(-1)
         << endl;


    buffer.push(3);
    buffer.push(4);


    while (!buffer.empty()) {
        cout << buffer.pop().value_or(-1) << " ";
    }

    cout << endl;


    return 0;
}