#include <vector>
#include <stdexcept>
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

    T pop() {
        if (empty()) {
            throw runtime_error("CircularBuffer is empty");
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
        cout << buffer.pop() << endl;
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
         << buffer.pop()
         << endl;


    buffer.push(3);
    buffer.push(4);


    while (!buffer.empty()) {
        cout << buffer.pop() << " ";
    }

    cout << endl;


    return 0;
}