/*
 * @lc app=leetcode id=152 lang=cpp
 *
 * [152] Maximum Product Subarray
 *
 * https://leetcode.com/problems/maximum-product-subarray/description/
 *
 * algorithms
 * Medium (35.10%)
 * Likes:    19941
 * Dislikes: 806
 * Total Accepted:    1.8M
 * Total Submissions: 5.1M
 * Testcase Example:  '[2,3,-2,4]'
 *
 * Given an integer array nums, find a subarray that has the largest product,
 * and return the product.
 * 
 * The test cases are generated so that the answer will fit in a 32-bit
 * integer.
 * 
 * Note that the product of an array with a single element is the value of that
 * element.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * -10 <= nums[i] <= 10
 * The product of any subarray of nums is guaranteed to fit in a 32-bit
 * integer.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN, max_f = 1, min_f = 1;
        for (int x : nums) {
            int mx = max_f;
            max_f = max({x, min_f * x, max_f * x});
            min_f = min({x, min_f * x, mx * x});
            ans = max(ans, max_f);
        }
        return ans;
    }
};
// @lc code=end

