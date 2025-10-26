/*
 * @lc app=leetcode id=1488 lang=cpp
 *
 * [1488] Avoid Flood in The City
 *
 * https://leetcode.com/problems/avoid-flood-in-the-city/description/
 *
 * algorithms
 * Medium (27.48%)
 * Likes:    2111
 * Dislikes: 601
 * Total Accepted:    126.6K
 * Total Submissions: 324.8K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Your country has 10^9 lakes. Initially, all the lakes are empty, but when it
 * rains over the n^th lake, the n^th lake becomes full of water. If it rains
 * over a lake that is full of water, there will be a flood. Your goal is to
 * avoid floods in any lake.
 * 
 * Given an integer array rains where:
 * 
 * 
 * rains[i] > 0 means there will be rains over the rains[i] lake.
 * rains[i] == 0 means there are no rains this day and you must choose one lake
 * this day and dry it.
 * 
 * 
 * Return an array ans where:
 * 
 * 
 * ans.length == rains.length
 * ans[i] == -1 if rains[i] > 0.
 * ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
 * 
 * 
 * If there are multiple valid answers return any of them. If it is impossible
 * to avoid flood return an empty array.
 * 
 * Notice that if you chose to dry a full lake, it becomes empty, but if you
 * chose to dry an empty lake, nothing changes.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: rains = [1,2,3,4]
 * Output: [-1,-1,-1,-1]
 * Explanation: After the first day full lakes are [1]
 * After the second day full lakes are [1,2]
 * After the third day full lakes are [1,2,3]
 * After the fourth day full lakes are [1,2,3,4]
 * There's no day to dry any lake and there is no flood in any lake.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: rains = [1,2,0,0,2,1]
 * Output: [-1,-1,2,1,-1,-1]
 * Explanation: After the first day full lakes are [1]
 * After the second day full lakes are [1,2]
 * After the third day, we dry lake 2. Full lakes are [1]
 * After the fourth day, we dry lake 1. There is no full lakes.
 * After the fifth day, full lakes are [2].
 * After the sixth day, full lakes are [1,2].
 * It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another
 * acceptable scenario.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: rains = [1,2,0,1,2]
 * Output: []
 * Explanation: After the second day, full lakes are  [1,2]. We have to dry one
 * lake in the third day.
 * After that, it will rain over lakes [1,2]. It's easy to prove that no matter
 * which lake you choose to dry in the 3rd day, the other one will flood.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= rains.length <= 10^5
 * 0 <= rains[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <set>
#include <unordered_map>
#include <numeric>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // 贪心+哈希表
    vector<int> avoidFlood1(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, -1);
        unordered_map<int, int> full_day; // lake -> 装满日
        set<int> dry_day; // 未被使用的抽水日
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            if (lake == 0) {
                ans[i] = 1; // 先随便选一个湖抽干
                dry_day.insert(i); // 保存抽水日
                continue;
            }
            if (full_day.contains(lake)) {
                int j = full_day[lake];
                // 必须在 j 之后，i 之前把 lake 抽干
                // 选一个最早的未被使用的抽水日，如果选晚的，可能会导致其他湖没有可用的抽水日
                auto it = dry_day.upper_bound(j);
                if (it == dry_day.end()) {
                    return {}; // 无法阻止洪水
                }
                ans[*it] = lake;
                dry_day.erase(it); // 移除已使用的抽水日
            }
            full_day[lake] = i; // 插入或更新装满日
        }
        return ans;
    }

    // 并查集
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> p(n + 1); // 并查集
        ranges::iota(p, 0); // 初始化并查集
        function<int(int)> find = [&](int x) { // 查找并查集代表元
            return x == p[x] ? x : p[x] = find(p[x]);
        };

        vector<int> ans(n, -1);
        unordered_map<int, int> full_day; // {lake -> 装满日}
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            if (lake == 0) {
                ans[i] = 1; // 先随便抽干一个湖
                continue;
            }
            if (full_day.contains(lake)) {
                int j = full_day[lake];
                int dry_day = find(j + 1);
                if (dry_day >= i) { // 来不及抽干，无法阻止洪水
                    return {};
                }
                ans[dry_day] = lake;
                p[dry_day] = find(dry_day + 1); // 删除抽干日
            }
            p[i] = i + 1; // 删除i
            full_day[lake] = i; // 更新装满日
        }
        return ans;
    }
};
// @lc code=end

