/*
 * @lc app=leetcode id=3267 lang=cpp
 *
 * [3267] Count Almost Equal Pairs II
 *
 * https://leetcode.com/problems/count-almost-equal-pairs-ii/description/
 *
 * algorithms
 * Hard (26.70%)
 * Likes:    81
 * Dislikes: 22
 * Total Accepted:    8.7K
 * Total Submissions: 32.7K
 * Testcase Example:  '[1023,2310,2130,213]'
 *
 * Attention: In this version, the number of operations that can be performed,
 * has been increased to twice.
 * 
 * You are given an array nums consisting of positive integers.
 * 
 * We call two integers x and y almost equal if both integers can become equal
 * after performing the following operation at most twice:
 * 
 * 
 * Choose either x or y and swap any two digits within the chosen number.
 * 
 * 
 * Return the number of indices i and j in nums where i < j such that nums[i]
 * and nums[j] are almost equal.
 * 
 * Note that it is allowed for an integer to have leading zeros after
 * performing an operation.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1023,2310,2130,213]
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The almost equal pairs of elements are:
 * 
 * 
 * 1023 and 2310. By swapping the digits 1 and 2, and then the digits 0 and 3
 * in 1023, you get 2310.
 * 1023 and 213. By swapping the digits 1 and 0, and then the digits 1 and 2 in
 * 1023, you get 0213, which is 213.
 * 2310 and 213. By swapping the digits 2 and 0, and then the digits 3 and 2 in
 * 2310, you get 0213, which is 213.
 * 2310 and 2130. By swapping the digits 3 and 1 in 2310, you get 2130.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,10,100]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The almost equal pairs of elements are:
 * 
 * 
 * 1 and 10. By swapping the digits 1 and 0 in 10, you get 01 which is 1.
 * 1 and 100. By swapping the second 0 with the digit 1 in 100, you get 001,
 * which is 1.
 * 10 and 100. By swapping the first 0 with the digit 1 in 100, you get 010,
 * which is 10.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 5000
 * 1 <= nums[i] < 10^7
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <algorithm>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    int countPairs(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();

        // 找出最大位数
        int m = 0;
        for (int x : nums) {
            m = max(m, (int)to_string(x).size());
        }

        // 预计算 10 的幂
        vector<int> POW10(m, 1);
        for (int i = 1; i < m; i++) {
            POW10[i] = POW10[i - 1] * 10;
        }

        unordered_map<int, bitset<5000>> num_to_idx; // 数值 -> bitset
        for (int p = 0; p < n; p++) {
            int x = nums[p];
            unordered_set<int> st;
            st.insert(x);

            // 转为每位数字，补前导零
            string sx = to_string(x);
            sx = string(m - sx.size(), '0') + sx; // 补前导零
            reverse(sx.begin(), sx.end()); // 低位到高位

            vector<int> a(m);
            for (int i = 0; i < m; i++) {
                a[i] = sx[i] - '0';
            }

            // 枚举交换一次的情况
            for (int i = 0; i < m; i++) {
                for (int j = i + 1; j < m; j++) {
                    if (a[i] == a[j]) continue;
                    int val = x + (a[j] - a[i]) * (POW10[i] - POW10[j]);
                    st.insert(val);
                }
            }

            bitset<5000> idx; // 用于累加前面可以匹配的数
            for (int v : st) { // Meet int the middle
                idx |= num_to_idx[v];  // 前面哪些数能变成 v
                num_to_idx[v].set(p);  // 把当前 p 标记为能变成 v
            }

            ans += idx.count(); // 累加匹配数量
        }

        return ans;
    }
};
// @lc code=end

