/*
 * @lc app=leetcode id=1655 lang=cpp
 *
 * [1655] Distribute Repeating Integers
 *
 * https://leetcode.com/problems/distribute-repeating-integers/description/
 *
 * algorithms
 * Hard (39.79%)
 * Likes:    462
 * Dislikes: 31
 * Total Accepted:    20.2K
 * Total Submissions: 50.2K
 * Testcase Example:  '[1,2,3,4]\n[2]'
 *
 * You are given an array of n integers, nums, where there are at most 50
 * unique values in the array. You are also given an array of m customer order
 * quantities, quantity, where quantity[i] is the amount of integers the i^th
 * customer ordered. Determine if it is possible to distribute nums such
 * that:
 * 
 * 
 * The i^th customer gets exactly quantity[i] integers,
 * The integers the i^th customer gets are all equal, and
 * Every customer is satisfied.
 * 
 * 
 * Return true if it is possible to distribute nums according to the above
 * conditions.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4], quantity = [2]
 * Output: false
 * Explanation: The 0^th customer cannot be given two different integers.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,3], quantity = [2]
 * Output: true
 * Explanation: The 0^th customer is given [3,3]. The integers [1,2] are not
 * used.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,1,2,2], quantity = [2,2]
 * Output: true
 * Explanation: The 0^th customer is given [1,1], and the 1st customer is given
 * [2,2].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 1 <= n <= 10^5
 * 1 <= nums[i] <= 1000
 * m == quantity.length
 * 1 <= m <= 10
 * 1 <= quantity[i] <= 10^5
 * There are at most 50 unique values in nums.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * @brief
 * 子集型状压 DP
 * 对 nums 进行计数统计，考虑前 i 个数能否满足子集 j 的用户
 * 从前 0 个数开始，如果满足 j ，则 i+1 个数一样满足
 * 如果不满足，则遍历j的子集 sub ，当前商品数量 c 满足 sub 需要的数量
 * 且 i 满足 sub 的补集，即前 i+1 个数能满足子集 j 的需求
 *
 *  f(i,j) 表示前 i 个数能否满足下标集合 j 的需求
 *  f(i,j) = f(i+1,j),  f(i,j)=true || f(i,j)=false &&
 * sum(sub)<=num(c) && f(i,sub)=true
 * 边界：j=0 f=true
 * 入口：f(n,(1<<m)-1), n为nums不同数的个数, m为顾客个数
 */
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> cnt;
        for (int x : nums) {
            cnt[x]++;
        }
        int n = cnt.size(), m = 1 << quantity.size();
        vector<int> sum(m);
        for (int i = 0; i < quantity.size(); i++) {
            int bit = 1 << i;
            for (int j = 0; j < bit; j++) {
                sum[j | bit] = sum[j] + quantity[i];
            }
        }
        vector<vector<bool>> f(n + 1, vector<bool>(m));
        f[0][0] = true;
        int i = 0;
        for (auto &[_, c] : cnt) {
            f[i + 1][0] = true;
            for (int j = 0; j < m; j++) {
                if (f[i][j]) {
                    f[i + 1][j] = true;
                    continue;
                }
                for (int sub = j; sub; sub = (sub - 1) & j) {
                    if (sum[sub] <= c && f[i][j ^ sub]) {
                        f[i + 1][j] = true;
                        break;
                    }
                }
            }
            i++;
        }
        return f[n][m - 1];
    }
};
// @lc code=end

