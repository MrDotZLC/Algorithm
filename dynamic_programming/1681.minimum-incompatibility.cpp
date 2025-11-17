/*
 * @lc app=leetcode id=1681 lang=cpp
 *
 * [1681] Minimum Incompatibility
 *
 * https://leetcode.com/problems/minimum-incompatibility/description/
 *
 * algorithms
 * Hard (39.93%)
 * Likes:    293
 * Dislikes: 101
 * Total Accepted:    10.5K
 * Total Submissions: 26K
 * Testcase Example:  '[1,2,1,4]\n2'
 *
 * You are given an integer array nums​​​ and an integer k. You are asked to
 * distribute this array into k subsets of equal size such that there are no
 * two equal elements in the same subset.
 * 
 * A subset's incompatibility is the difference between the maximum and minimum
 * elements in that array.
 * 
 * Return the minimum possible sum of incompatibilities of the k subsets after
 * distributing the array optimally, or return -1 if it is not possible.
 * 
 * A subset is a group integers that appear in the array with no particular
 * order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,1,4], k = 2
 * Output: 4
 * Explanation: The optimal distribution of subsets is [1,2] and [1,4].
 * The incompatibility is (2-1) + (4-1) = 4.
 * Note that [1,1] and [2,4] would result in a smaller sum, but the first
 * subset contains 2 equal elements.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [6,3,8,1,3,1,2,2], k = 4
 * Output: 6
 * Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8], and
 * [1,3].
 * The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [5,3,3,6,3,3], k = 3
 * Output: -1
 * Explanation: It is impossible to distribute nums into 3 subsets where no two
 * elements are equal in the same subset.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 16
 * nums.length is divisible by k
 * 1 <= nums[i] <= nums.length
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bit>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) {
            if (++cnt[x] > k) {
                return -1;
            }
        }

        int n = nums.size(), size = n / k, m = 1 << n;
        ranges::sort(nums);
        vector<vector<int>> memo(m, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int mask, int pre) -> int {
            if (mask == 0) {
                return 0;
            }
            int &res = memo[mask][pre];
            if (res != -1) {
                return res;
            }
            res = INT_MAX / 2;
            if (popcount((unsigned)mask) % size == 0) {
                unsigned int lowbit = mask & -mask; // 默认选择最低位作为第一个数
                return res = dfs(mask ^ lowbit, __builtin_ctz(lowbit)); // 位数-1对应数组下标
                // return res = dfs(mask ^ lowbit, 32 - __builtin_clz(lowbit) - 1); // 位数-1对应数组下标
            }
            int last = nums[pre];
            for (int k = pre + 1; k < n; k++) {
                if (mask >> k & 1 && nums[k] != last) {
                    last = nums[k];
                    res = min(res, dfs(mask ^ (1 << k), k) + last - nums[pre]);
                }
            }
            return res;
        };
        return dfs(m - 2, 0); // 默认把最低位分配给第一个组        
    }
};
// @lc code=end

