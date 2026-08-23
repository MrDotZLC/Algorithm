#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <thread>
#include <iostream>

using namespace std;

template<typename T>
class BoundedMPMCQueue {
public:
    BoundedMPMCQueue(int cap) : cap_(cap) {}

    // 生产者调用：阻塞到有空位
    void push(T val) {
        unique_lock<mutex> lk(mtx_);
        not_full_.wait(
            lk, [this] { return q_.size() < cap_ || stopped; });
        if (stopped) return;
        q_.push(move(val));
        // 通知一个正在等待的线程，不通知全部，防止惊群效应
        not_empty_.notify_one();
    }
    
    // 消费者调用：阻塞直到有数据；返回 nullopt 表示已关闭且队列为空
    optional<T> pop() {
        unique_lock<mutex> lk(mtx_);   
        not_empty_.wait(lk, [this]{
            return !q_.empty() || stopped;
        });
        if (q_.empty()) {
            return nullopt;
        }
        T val = q_.front();
        q_.pop();
        not_full_.notify_one();
        return val;
    }

    void stop() {
        {
            lock_guard<mutex> lk(mtx_);
            stopped = true;
        }
        not_full_.notify_all();
        not_empty_.notify_all();
    }

private:
    queue<T>            q_;
    size_t              cap_;
    bool                stopped = false;
    mutex               mtx_;
    condition_variable  not_full_;
    condition_variable  not_empty_;
};


int main() {
    BoundedMPMCQueue<int> bq(4);

    thread producer([&]{
        for (int i = 0; i < 10; ++i) {
            bq.push(i);
            cout << "[Producer] pushed " << i << "\n";
        }
        bq.stop();
    });

    thread consumer([&]{
        while (auto val = bq.pop()) {
            std::cout << "[Consumer] got " << *val << "\n";
        }
    });

    producer.join();
    consumer.join();
}