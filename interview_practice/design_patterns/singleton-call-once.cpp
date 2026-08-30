#include <mutex>

class SingletonCallOnce {
public:
    static SingletonCallOnce& get_instance() {
        std::call_once(flag_, [] {
            instance_ = new SingletonCallOnce(); 
        });
        return *instance_;
    }

    SingletonCallOnce(const SingletonCallOnce&) = delete;
    SingletonCallOnce& operator=(const SingletonCallOnce&) = delete;
    SingletonCallOnce(SingletonCallOnce&&) = delete;
    SingletonCallOnce& operator=(SingletonCallOnce&&) = delete;
    
private:
    SingletonCallOnce() = default;
    static SingletonCallOnce* instance_;
    static std::once_flag flag_;
};