#include <utility>      // std::exchange, std::forward
#include <memory>       // std::default_delete

// ── MyUniquePtr<T, Deleter> ───────────────────────────────────────────────
template<typename T, typename Deleter = std::default_delete<T>>
class MyUniquePtr {
public:
    MyUniquePtr(T* ptr = nullptr, Deleter deleter = Deleter{})
        : ptr_(ptr), deleter_(std::move(deleter)) {}

    ~MyUniquePtr() {
        if (ptr_) deleter_(ptr_);
    }

    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    MyUniquePtr(MyUniquePtr&& other)
        : ptr_(std::exchange(other.ptr_, nullptr))
        , deleter_(std::move(other.deleter_)) {}

    MyUniquePtr& operator=(MyUniquePtr&& other) {
        if (this != &other) {
            if (ptr_) deleter_(ptr_);
            ptr_ = std::exchange(other.ptr_, nullptr);
            deleter_ = std::move(other.deleter_);
        }
        return *this;
    }

    T* get() const noexcept { return ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T& operator*() const { return *ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }

    void reset(T* ptr = nullptr) noexcept {
        if (ptr_) deleter_(ptr_);
        ptr_= ptr;
    }

private:
    T* ptr_;
    Deleter deleter_;
};

// make_unique（C++14 风格）
template<typename T, typename... Args>
MyUniquePtr<T> makeUnique(Args... args) {
    return MyUniquePtr<T>(new T(std::forward<Args>(args)...));
}

#include <iostream>
#include <string>

// 测试对象
class Test {
public:
    explicit Test(int id, std::string name)
        : id_(id), name_(std::move(name)) {
        std::cout << "Test ctor: " << id_ << " " << name_ << "\n";
    }

    ~Test() {
        std::cout << "Test dtor: " << id_ << " " << name_ << "\n";
    }

    void print() const {
        std::cout << "Test print: "
                  << id_ << " "
                  << name_ << "\n";
    }

private:
    int id_;
    std::string name_;
};


int main() {

    std::cout << "===== 1. basic construction =====\n";

    {
        MyUniquePtr<Test> ptr(new Test(1, "Alice"));

        if (ptr) {
            ptr->print();
            (*ptr).print();
        }

        std::cout << "raw pointer: "
                  << ptr.get()
                  << "\n";
    } 
    // 自动析构


    std::cout << "\n===== 2. move construction =====\n";

    {
        MyUniquePtr<Test> ptr1(new Test(2, "Bob"));

        MyUniquePtr<Test> ptr2(std::move(ptr1));

        std::cout << "ptr1: "
                  << (ptr1 ? "not null" : "null")
                  << "\n";

        std::cout << "ptr2: "
                  << (ptr2 ? "not null" : "null")
                  << "\n";

        ptr2->print();
    }


    std::cout << "\n===== 3. move assignment =====\n";

    {
        MyUniquePtr<Test> ptr1(new Test(3, "Carol"));
        MyUniquePtr<Test> ptr2(new Test(4, "David"));

        ptr2 = std::move(ptr1);

        std::cout << "ptr1 after move: "
                  << (ptr1 ? "not null" : "null")
                  << "\n";

        std::cout << "ptr2 after move: "
                  << (ptr2 ? "not null" : "null")
                  << "\n";

        ptr2->print();
    }


    std::cout << "\n===== 4. makeUnique =====\n";

    {
        auto ptr = makeUnique<Test>(5, "Emma");

        ptr->print();
    }


    std::cout << "\n===== 5. release =====\n";

    {
        MyUniquePtr<Test> ptr(new Test(6, "Frank"));

        Test* raw = ptr.release();

        std::cout << "after release: "
                  << (ptr ? "not null" : "null")
                  << "\n";

        raw->print();

        delete raw;   // release 后调用方负责释放
    }


    std::cout << "\n===== 6. reset =====\n";

    {
        MyUniquePtr<Test> ptr(new Test(7, "Grace"));

        ptr.reset(new Test(8, "Helen"));

        ptr->print();

        ptr.reset();

        std::cout << "after reset nullptr: "
                  << (ptr ? "not null" : "null")
                  << "\n";
    }


    std::cout << "\n===== end =====\n";

    return 0;
}