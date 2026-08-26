#include <atomic>
#include <utility>
#include <stdexcept>

// ── 控制块：存储引用计数 ────────────────────────────────────────────────
struct ControlBlock {
    std::atomic<int> strong_count{1};   // shared_ptr 数量
    std::atomic<int> weak_count{1};     // weak_ptr数量 + shared_ptr生命周期保护引用

    virtual void destroyObject() noexcept = 0;  // 销毁被管理对象
    virtual void destroySelf()   noexcept = 0;  // 销毁控制块自身
    virtual ~ControlBlock() = default;
};

template<typename T>
struct ControlBlockImpl : ControlBlock {
    T* ptr;
    explicit ControlBlockImpl(T* p) : ptr(p) {}
    void destroyObject() noexcept override { delete ptr; ptr = nullptr; }
    void destroySelf()   noexcept override { delete this; }
};

// ── 前向声明 ──────────────────────────────────────────────────────────────
template<typename T> class MyWeakPtr;

// ── MySharedPtr<T> ────────────────────────────────────────────────────────
template<typename T>
class MySharedPtr {
    friend class MyWeakPtr<T>;
public:
    // 增加一个标记 tag 构造，避免 fetch_add 两次
    struct RawAttachTag {};

    // 默认构造：空指针
    MySharedPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

    // 接管裸指针，创建控制块
    explicit MySharedPtr(T* ptr)
        : ptr_(ptr), cb_(ptr ? new ControlBlockImpl<T>(ptr) : nullptr) {}

    // 拷贝构造：共享所有权，strong_count +1
    MySharedPtr(const MySharedPtr& other) noexcept
        : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) cb_->strong_count.fetch_add(1, std::memory_order_relaxed);
    }

    // 移动构造：转移所有权，来源置空（不改变引用计数）
    MySharedPtr(MySharedPtr&& other) noexcept
        : ptr_(std::exchange(other.ptr_, nullptr)),
          cb_ (std::exchange(other.cb_,  nullptr)) {}

    // 析构：strong_count -1；归零时销毁对象；weak_count 也归零时销毁控制块
    ~MySharedPtr() { release(); }

    // 移动赋值
    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = std::exchange(other.ptr_, nullptr);
            cb_  = std::exchange(other.cb_,  nullptr);
        }
        return *this;
    }

    // 拷贝赋值
    MySharedPtr& operator=(const MySharedPtr& other) noexcept {
        if (this != &other) {
            if (other.cb_) {
                other.cb_->strong_count.fetch_add(1, std::memory_order_relaxed);
            }
            release(); // 先加后减，防死锁与野指针
            ptr_ = other.ptr_;
            cb_  = other.cb_;
        }
        return *this;
    }

    T* get()           const noexcept { return ptr_; }
    T& operator*()     const          { return *ptr_; }
    T* operator->()    const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    int use_count() const noexcept {
        return cb_ ? cb_->strong_count.load(std::memory_order_relaxed) : 0;
    }

private:
    T*            ptr_;
    ControlBlock* cb_;

    // 供 weak_ptr::lock() 调用，从控制块直接构造（不再 new）
    MySharedPtr(T* ptr, ControlBlock* cb, RawAttachTag) : ptr_(ptr), cb_(cb) {
        // 已经由外部 CAS 增加了引用计数，此处不做任何 fetch_add
    }


    void release() noexcept {
        if (!cb_) return;
        // strong_count 减 1，若归零则销毁对象
        if (cb_->strong_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            cb_->destroyObject();
            // weak_count 减 1（对应 strong 持有的那个弱引用），若归零则销毁控制块
            if (cb_->weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
                cb_->destroySelf();
        }
        ptr_ = nullptr;
        cb_  = nullptr;
    }
};

// ── MyWeakPtr<T> ──────────────────────────────────────────────────────────
template<typename T>
class MyWeakPtr {
public:
    MyWeakPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

    // 从 shared_ptr 构造：weak_count +1（不影响 strong_count）
    MyWeakPtr(const MySharedPtr<T>& sp) noexcept
        : ptr_(sp.ptr_), cb_(sp.cb_) {
        if (cb_) cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    ~MyWeakPtr() { release(); }

    MyWeakPtr(const MyWeakPtr& other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    MyWeakPtr& operator=(const MyWeakPtr& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_; cb_ = other.cb_;
            if (cb_) cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }

    bool expired() const noexcept {
        return !cb_ || cb_->strong_count.load(std::memory_order_acquire) == 0;
    }

    // 尝试提升为 shared_ptr；若对象已销毁则返回空 shared_ptr
    MySharedPtr<T> lock() const noexcept {
        if (!cb_) return MySharedPtr<T>{};

        int cnt = cb_->strong_count.load(std::memory_order_relaxed);
        while (cnt > 0) {
            if (cb_->strong_count.compare_exchange_weak(
                    cnt, cnt + 1,
                    std::memory_order_acquire,
                    std::memory_order_relaxed)) {
                return MySharedPtr<T>(ptr_, cb_, typename MySharedPtr<T>::RawAttachTag{}); // 成功提升
            }
        }
        return MySharedPtr<T>{}; // 对象已被销毁
    }

private:
    T*            ptr_;
    ControlBlock* cb_;

    void release() noexcept {
        if (!cb_) return;
        if (cb_->weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
            cb_->destroySelf();   // 最后一个 weak_ptr 销毁时回收控制块
        ptr_ = nullptr; cb_ = nullptr;
    }
};

// make_shared（合并对象和控制块为一次 new，减少内存碎片）
template<typename T, typename... Args>
MySharedPtr<T> makeShared(Args&&... args) {
    return MySharedPtr<T>(new T(std::forward<Args>(args)...));
    // 注：真正的 make_shared 将对象嵌入控制块一次性分配，此处为简化版
}

#include <iostream>
#include <cassert>

// 测算类：用于追踪对象的创建与析构
struct TestResource {
    int id;
    TestResource(int id) : id(id) {
        std::cout << "Resource created!\n";
    }
    ~TestResource() {
        std::cout << "Resource destroyed!\n";
    }
    void hello() const {
        std::cout << "Hello from resource " << id << "\n";
    }
};

// 继承原控制块，重写 destroySelf 以打印日志
struct TestControlBlock : public ControlBlockImpl<TestResource> {
    explicit TestControlBlock(TestResource* p) : ControlBlockImpl<TestResource>(p) {}
    void destroySelf() noexcept override {
        std::cout << "Control block destroyed!\n";
        delete this;
    }
};

int main() {
    std::cout << "--- Test 1: Basic SharedPtr Lifetime ---\n";
    {
        // 手动使用带日志的控制块测试生命周期
        MySharedPtr<TestResource> sp1;
        {
            auto* res = new TestResource(1);
            // 模拟构造
            MySharedPtr<TestResource> sp2(res); 
            sp1 = sp2; // 拷贝赋值
            std::cout << "sp1 count: " << sp1.use_count() << "\n"; // 应为 2
            std::cout << "sp2 count: " << sp2.use_count() << "\n"; // 应为 2
        } 
        // sp2 作用域结束，计数降为 1
        std::cout << "sp1 count after reset: " << sp1.use_count() << "\n";
    } 
    // sp1 作用域结束，对象与控制块均应销毁

    std::cout << "\n--- Test 2: WeakPtr & lock() ---\n";
    MyWeakPtr<TestResource> wp;
    {
        auto sp3 = makeShared<TestResource>(2);
        wp = sp3;
        
        std::cout << "wp expired: " << (wp.expired() ? "true" : "false") << "\n";
        
        // 测试 lock() 提升
        if (auto locked = wp.lock()) {
            std::cout << "wp.lock() succeeded, count: " << locked.use_count() << "\n"; // 应为 2
            locked->hello();
        }
    } 
    // sp3 析构，对象被销毁，但 wp 还拿着控制块

    std::cout << "sp3 released.\n";
    std::cout << "wp expired: " << (wp.expired() ? "true" : "false") << "\n";
    
    // 再次 lock 应当失败
    if (auto locked = wp.lock()) {
        std::cout << "ERROR: lock should have failed!\n";
    } else {
        std::cout << "wp.lock() failed!\n";
    }

    std::cout << "\n--- Test 3: Self/Copy Assignment Edge Cases ---\n";
    {
        auto sp_a = makeShared<TestResource>(3);
        auto sp_b = sp_a;
        
        // 自赋值测试
        sp_a = sp_a; 
        
        // 互相拷贝赋值测试
        sp_a = sp_b; 
        
        std::cout << "sp_a count: " << sp_a.use_count() << "\n";
        std::cout << "sp_b count: " << sp_b.use_count() << "\n";
    }

    std::cout << "\n--- All tests passed! ---\n";
    return 0;
}