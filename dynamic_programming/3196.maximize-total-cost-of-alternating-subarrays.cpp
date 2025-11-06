/*
 * @lc app=leetcode id=3196 lang=cpp
 *
 * [3196] Maximize Total Cost of Alternating Subarrays
 *
 * https://leetcode.com/problems/maximize-total-cost-of-alternating-subarrays/description/
 *
 * algorithms
 * Medium (28.80%)
 * Likes:    190
 * Dislikes: 29
 * Total Accepted:    24.8K
 * Total Submissions: 84.7K
 * Testcase Example:  '[1,-2,3,4]'
 *
 * You are given an integer array nums with length n.
 * 
 * The cost of a subarray nums[l..r], where 0 <= l <= r < n, is defined as:
 * 
 * cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)^r − l
 * 
 * Your task is to split nums into subarrays such that the total cost of the
 * subarrays is maximized, ensuring each element belongs to exactly one
 * subarray.
 * 
 * Formally, if nums is split into k subarrays, where k > 1, at indices i1, i2,
 * ..., ik − 1, where 0 <= i1 < i2 < ... < ik - 1 < n - 1, then the total cost
 * will be:
 * 
 * cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)
 * 
 * Return an integer denoting the maximum total cost of the subarrays after
 * splitting the array optimally.
 * 
 * Note: If nums is not split into subarrays, i.e. k = 1, the total cost is
 * simply cost(0, n - 1).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,-2,3,4]
 * 
 * Output: 10
 * 
 * Explanation:
 * 
 * One way to maximize the total cost is by splitting [1, -2, 3, 4] into
 * subarrays [1, -2, 3] and [4]. The total cost will be (1 + 2 + 3) + 4 = 10.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,-1,1,-1]
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * One way to maximize the total cost is by splitting [1, -1, 1, -1] into
 * subarrays [1, -1] and [1, -1]. The total cost will be (1 + 1) + (1 + 1) =
 * 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [0]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * We cannot split the array further, so the answer is 0.
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: nums = [1,-1]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * Selecting the whole array gives a total cost of 1 + 1 = 2, which is the
 * maximum.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <string>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // dfs(i) = mxa(dfs(i-1)+nums[i], dfs(i-2)+nums[i-1]-nums[i])
    // 递归+记忆化搜索
    long long maximumTotalCost1(vector<int>& nums) {
        int n = nums.size();
        vector<long long> memo(n, LLONG_MIN);
        function<long long(int)> dfs = [&](int i) -> long long {
            if (i < 0) {
                return 0;
            }
            if (i == 0) {
                return nums[0];
            }
            long long &res = memo[i];
            if (res != LLONG_MIN) {
                return res;
            }
            return res = max(dfs(i - 1) + nums[i],
                             dfs(i - 2) + nums[i - 1] - nums[i]);
        };
        return dfs(n - 1);
    }

    // DP递推
    long long maximumTotalCost2(vector<int>& nums) {
        int n = nums.size();
        vector<long long> f(n + 1);
        f[1] = nums[0];
        for (int i = 1; i < n; i++) {
            f[i + 1] = max(f[i] + nums[i],
                           f[i - 1] + nums[i - 1] - nums[i]);
        }
        return f[n];
    }

    // DP递推+空间优化
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        long long f0 = 0, f1 = nums[0];
        for (int i = 1; i < n; i++) {
            long long tmp = f1;
            f1 = max(f1 + nums[i],
                           f0 + nums[i - 1] - nums[i]);
            f0 = tmp;
        }
        return f1;
    }
};
// @lc code=end

