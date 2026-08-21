#include <list>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    explicit LRUCache(size_t capacity) : cap_(capacity) {}

    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return -1;
        }

        // 将命中节点移到链表头部（表示最近访问）
        move_to_front(it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->second = value;
            move_to_front(it->second);
            return;
        }

        if (map_.size() >= cap_) {
            auto lru = prev(list_.end());     // 尾部节点
            map_.erase(lru->first);
            list_.erase(lru);
        }

        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }

private:
    using KV = pair<int, int>;
    using Iter = list<KV>::iterator; // 使用迭代器，管理生命周期更方便

    size_t cap_;
    list<KV> list_;                 // 头部最新，尾部最旧
    unordered_map<int, Iter> map_;  // key--链表节点迭代器

    void move_to_front(Iter it) {
        list_.splice(list_.begin(), list_, it);
    }
};
