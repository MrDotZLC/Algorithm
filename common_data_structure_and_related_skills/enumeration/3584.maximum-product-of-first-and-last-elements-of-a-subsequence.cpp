/*
 * @lc app=leetcode id=3584 lang=cpp
 *
 * [3584] Maximum Product of First and Last Elements of a Subsequence
 *
 * https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/description/
 *
 * algorithms
 * Medium (30.12%)
 * Likes:    101
 * Dislikes: 1
 * Total Accepted:    18K
 * Total Submissions: 59.3K
 * Testcase Example:  '[-1,-9,2,3,-2,-3,1]\n1'
 *
 * You are given an integer array nums and an integer m.
 * 
 * Return the maximum product of the first and last elements of any subsequence
 * of nums of size m.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
 * 
 * Output: 81
 * 
 * Explanation:
 * 
 * The subsequence [-9] has the largest product of the first and last elements:
 * -9 * -9 = 81. Therefore, the answer is 81.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,3,-5,5,6,-4], m = 3
 * 
 * Output: 20
 * 
 * Explanation:
 * 
 * The subsequence [-5, 6, -4] has the largest product of the first and last
 * elements.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,-1,2,-6,5,2,-5,7], m = 2
 * 
 * Output: 35
 * 
 * Explanation:
 * 
 * The subsequence [5, 7] has the largest product of the first and last
 * elements.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^5 <= nums[i] <= 10^5
 * 1 <= m <= nums.length
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long ans = LLONG_MIN;
        int mn = nums[0], mx = nums[0];
        for (int i = m - 1; i < nums.size(); i++) {
            mn = min(mn, nums[i - m + 1]);
            mx = max(mx, nums[i - m + 1]);
            int x = nums[i];
            ans = max(ans, m == 1 ? 1LL * x * x
                                  : 1LL * x * (x > 0 ? mx : mn));
        }
        return ans;
    }
};
// @lc code=end

