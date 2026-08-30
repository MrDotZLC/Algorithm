#include <atomic>
#include <mutex>

class SingletonDCLP {
public:
    static SingletonDCLP* get_instance() {
        // 第一次检查：无锁
        SingletonDCLP* p = instance_.load(std::memory_order_acquire);
        if (!p) {
            std::lock_guard<std::mutex> lk(mtx_);

            // 第二次检查：加锁后确认
            p = instance_.load(std::memory_order_relaxed);
            if (!p) {
                p = new SingletonDCLP();
                instance_.store(p, std::memory_order_release);
            }
        }
        return p;
    }

    SingletonDCLP(const SingletonDCLP&) = delete;
    SingletonDCLP& operator=(const SingletonDCLP&) = delete;
    SingletonDCLP(SingletonDCLP&&) = delete;
    SingletonDCLP& operator=(SingletonDCLP&&) = delete;

private:
    SingletonDCLP() = default;
    static std::atomic<SingletonDCLP*> instance_;
    static std::mutex                  mtx_;
};
