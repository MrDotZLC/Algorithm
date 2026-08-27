#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// 给定 $n$ 个区间 $[l_i, r_i]$，找出所有被 **至少 $k$ 个区间覆盖** 的点（或连续区间段）。
// 输入区间为整数闭区间 [l, r]
// 差分数组解法，O(n \log n)
vector<pair<int, int>> 
kCoverageIntervals(const vector<pair<int, int>>& intervals, int k) {
    // 差分数组：l 处 +1，r 处 -1
    // 扫描线扫过时，前缀和就是被覆盖的区间数
    vector<pair<int, int>> res;
    vector<pair<int, int>> events;
    events.reserve(2 * intervals.size());

    for (auto& [l, r] : intervals) {
        events.emplace_back(l, 1);
        events.emplace_back(r + 1, -1);
    }

    // 按左边界排序，相同左边界的区间，优先大区间遍历，保证端点计数正确
    sort(events.begin(), events.end(), [](const auto& a, const auto& b){
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    });

    int coverage = 0;
    int seq_start_pos = -1; // 默认未开始

    for (const auto& [pos, delta] : events) {
        int pre_coverage = coverage;
        coverage += delta;

        if (pre_coverage < k && coverage >= k) {
            seq_start_pos = pos;
        }
        if (pre_coverage >= k && coverage < k) {
            res.emplace_back(seq_start_pos, pos - 1);
        }
    }

    return res;
}

int main() {
    // 测试用例1：基本覆盖
    vector<pair<int, int>> intervals1 = {{1, 5}, {2, 6}, {3, 7}, {4, 8}};
    auto res1 = kCoverageIntervals(intervals1, 3);
    cout << "测试1：至少3个区间覆盖的点：" << endl;
    for (auto& [l, r] : res1) {
        cout << "[" << l << ", " << r << "]" << endl;
    }
    // 预期输出：[4, 5] (点4和5被3个区间覆盖)
    
    cout << endl;
    
    // 测试用例2：多个不连续段
    vector<pair<int, int>> intervals2 = {{1, 3}, {2, 4}, {3, 5}, {6, 8}, {7, 9}};
    auto res2 = kCoverageIntervals(intervals2, 2);
    cout << "测试2：至少2个区间覆盖的点：" << endl;
    for (auto& [l, r] : res2) {
        cout << "[" << l << ", " << r << "]" << endl;
    }
    // 预期输出：[2, 3] 和 [3, 4] 和 [7, 8]
    // 注意：点3被3个区间覆盖，但作为连续段会合并为[2,4]? 实际看合并逻辑
    
    cout << endl;
    
    // 测试用例3：单个区间
    vector<pair<int, int>> intervals3 = {{1, 10}};
    auto res3 = kCoverageIntervals(intervals3, 2);
    cout << "测试3：至少2个区间覆盖的点：" << endl;
    for (auto& [l, r] : res3) {
        cout << "[" << l << ", " << r << "]" << endl;
    }
    // 预期输出：空 (没有点被2个区间覆盖)
    
    cout << endl;
    
    // 测试用例4：边界值测试
    vector<pair<int, int>> intervals4 = {{1, 1}, {1, 2}, {2, 3}};
    auto res4 = kCoverageIntervals(intervals4, 2);
    cout << "测试4：至少2个区间覆盖的点：" << endl;
    for (auto& [l, r] : res4) {
        cout << "[" << l << ", " << r << "]" << endl;
    }
    // 预期输出：[1, 1] 和 [2, 2]
    
    return 0;
}
