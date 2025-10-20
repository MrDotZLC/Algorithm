/* 
    LCR 184. 设计自助结算系统

    中等
    相关标签
    premium lock icon
    相关企业
    请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：

    get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
    add(value)：将价格为 value 的商品加入待结算商品队列的尾部
    remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
    注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)

    

    示例 1：

    输入: 
    ["Checkout","add","add","get_max","remove","get_max"]
    [[],[4],[7],[],[],[]]

    输出: [null,null,null,7,4,7]
    示例 2：

    输入: 
    ["Checkout","remove","get_max"]
    [[],[],[]]

    输出: [null,-1,-1]
    

    提示：

    1 <= get_max, add, remove 的总操作数 <= 10000
    1 <= value <= 10^5
*/
#include <deque>
using namespace std;

class Checkout {
public:
    Checkout() {
        
    }
    
    int get_max() {
        return _max_values.empty() ? -1 : _max_values.front();
    }
    
    void add(int value) {
        _values.push_back(value);
        while (!_max_values.empty() && _max_values.back() <= value) {
            _max_values.pop_back();
        }
        _max_values.push_back(value);
    }
    
    int remove() {
        if (_values.empty()) {
            return -1;
        }
        int ans = _values.front();
        if (_max_values.front() == ans) {
            _max_values.pop_front();
        }
        _values.pop_front();
        return ans;
    }
private:
    deque<int> _values;
    deque<int> _max_values;
};

/**
 * Your Checkout object will be instantiated and called as such:
 * Checkout* obj = new Checkout();
 * int param_1 = obj->get_max();
 * obj->add(value);
 * int param_3 = obj->remove();
 */