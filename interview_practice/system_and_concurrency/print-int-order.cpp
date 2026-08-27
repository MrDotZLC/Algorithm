#include <vector>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <semaphore>
#include <thread>
#include <iostream>
using namespace std;

void print_in_order(int N, int M) {
    mutex mtx;
    condition_variable cv;
    int turn = 0;           // 当前应执行的线程编号
    int current = 1;        // 下一个要打印的数字

    vector<thread> threads;
    for (int id = 0; id < N; ++id) {
        threads.emplace_back([&, id]{
            while (true) {
                unique_lock<mutex> lk(mtx);
                // 直到轮到自己且还有数字可打印
                cv.wait(lk, [&]{ return id == turn || current > M; });
                if (current > M) break;
                cout << "Thread-" << id << " prints " << current++ << "\n";
                turn = (turn + 1) % N;  // 令牌传给在一个线程
                cv.notify_all();        // 唤醒所有线程，让下一个线程执行
            }
        });
    }

    for (auto& t : threads) t.join();
}

// 每个线程有自己的信号量，形成环形"接力棒"
// thread[i] 完成后 release thread[(i+1)%N] 的信号量
void print_in_order_semaphore(int N, int M) {
    // 初始化：thread-0 的优先级为 1（先行），其余为 0
    vector<unique_ptr<counting_semaphore<1>>> sems;
    sems.reserve(N);
    for (int i = 0; i < N; ++i) {
        sems.emplace_back(make_unique<counting_semaphore<1>>(i == 0 ? 1 : 0));
    }

    int current = 1; // 共享计数器
    vector<thread> ts;

    for (int id = 0; id < N; ++id) {
        ts.emplace_back([&, id] {
            while (true) {
                sems[id]->acquire();  // 等待被唤醒
                if (current > M) {
                    sems[(id + 1) % N]->release(); // 唤醒下个线程
                    break;
                }
                cout << "Thread-" << id << " prints " << current++ << "\n";
                sems[(id + 1) % N]->release(); // 唤醒下个线程
            }
        });
    }

    for (auto& t : ts) t.join(); 
}

int main() {
    print_in_order(2, 5);

    print_in_order_semaphore(6, 5);
}