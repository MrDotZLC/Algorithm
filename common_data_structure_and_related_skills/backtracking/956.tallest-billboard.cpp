/*
 * @lc app=leetcode id=956 lang=cpp
 *
 * [956] Tallest Billboard
 *
 * https://leetcode.com/problems/tallest-billboard/description/
 *
 * algorithms
 * Hard (51.86%)
 * Likes:    2438
 * Dislikes: 61
 * Total Accepted:    66.7K
 * Total Submissions: 128.7K
 * Testcase Example:  '[1,2,3,6]'
 *
 * You are installing a billboard and want it to have the largest height. The
 * billboard will have two steel supports, one on each side. Each steel support
 * must be an equal height.
 * 
 * You are given a collection of rods that can be welded together. For example,
 * if you have rods of lengths 1, 2, and 3, you can weld them together to make
 * a support of length 6.
 * 
 * Return the largest possible height of your billboard installation. If you
 * cannot support the billboard, return 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: rods = [1,2,3,6]
 * Output: 6
 * Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the
 * same sum = 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: rods = [1,2,3,4,5,6]
 * Output: 10
 * Explanation: We have two disjoint subsets {2,3,5} and {4,6}, which have the
 * same sum = 10.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: rods = [1,2]
 * Output: 0
 * Explanation: The billboard cannot be supported, so we return 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= rods.length <= 20
 * 1 <= rods[i] <= 1000
 * sum(rods[i]) <= 5000
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        unordered_map<int, int> ml, mr; // key为左-右，即差值，value为左钢架的高度，
        ml[0] = 0; // 还没有添加钢筋，两钢架差值为0，左高度为0
        mr[0] = 0;

        // 参数列表：左边界，右边界，两钢架的高度差，左钢架高度，高度差与左高度的映射
        auto dfs = [&](this auto &&dfs, int l, int r, int diff, int l_height, unordered_map<int, int> &m) -> void {
            if (l > r) {
                m[diff] = max(m[diff], l_height);
                return;
            }

            dfs(l + 1, r, diff + rods[l], l_height + rods[l], m); // 钢筋加到左边
            dfs(l + 1, r, diff - rods[l], l_height, m); // 钢筋加到右边
            dfs(l + 1, r, diff, l_height, m); // 废弃
        };
        dfs(0, n / 2, 0, 0, ml); // 遍历前半边
        dfs(n / 2 + 1, n - 1, 0, 0, mr); // 遍历后半边

        int ans = 0;
        for (auto &[diff, l_height] : ml) { // 遍历前半边的高度差和左高度
            if (mr.count(-diff)) { // 右半边存在负高度差和对应的右高度
                // 两半边高度差的和为0，即左半边（左比右高diff）加上右半边（右比左高diff）
                // 相加后，两钢架高度相等
                ans = max(ans, l_height + mr[-diff]);
            }
        }
        return ans;
    }
};
// @lc code=end

