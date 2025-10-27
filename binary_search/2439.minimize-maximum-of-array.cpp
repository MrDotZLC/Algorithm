/*
 * @lc app=leetcode id=2439 lang=cpp
 *
 * [2439] Minimize Maximum of Array
 *
 * https://leetcode.com/problems/minimize-maximum-of-array/description/
 *
 * algorithms
 * Medium (46.40%)
 * Likes:    2541
 * Dislikes: 636
 * Total Accepted:    93.6K
 * Total Submissions: 201.8K
 * Testcase Example:  '[3,7,1,6]'
 *
 * You are given a 0-indexed array nums comprising of n non-negative integers.
 * 
 * In one operation, you must:
 * 
 * 
 * Choose an integer i such that 1 <= i < n and nums[i] > 0.
 * Decrease nums[i] by 1.
 * Increase nums[i - 1] by 1.
 * 
 * 
 * Return the minimum possible value of the maximum integer of nums after
 * performing any number of operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,7,1,6]
 * Output: 5
 * Explanation:
 * One set of optimal operations is as follows:
 * 1. Choose i = 1, and nums becomes [4,6,1,6].
 * 2. Choose i = 3, and nums becomes [4,6,2,5].
 * 3. Choose i = 1, and nums becomes [5,5,2,5].
 * The maximum integer of nums is 5. It can be shown that the maximum number
 * cannot be less than 5.
 * Therefore, we return 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [10,1]
 * Output: 10
 * Explanation:
 * It is optimal to leave nums as is, and since 10 is the maximum value, we
 * return 10.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 2 <= n <= 10^5
 * 0 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // Rule
    int minimizeArrayValue1(vector<int>& nums) {
        long long ans = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            ans = max(ans, (sum + i) / (i + 1)); // (s + i + 1 - 1) / (i + 1)
        }
        return ans;
    }

    // binary
    int minimizeArrayValue(vector<int>& nums) {
        auto check = [&](int k) -> bool {
            long long temp = 0LL;
            for (int i = nums.size() - 1; i > 0; i--) {
                temp = max(nums[i] + temp - k, 0LL);
            }
            return nums[0] + temp > k;
        };

        int L = -1, R = *max_element(nums.begin(), nums.end());
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid;
        }
        return R;
    }
};
// @lc code=end

