/*
 * @lc app=leetcode id=962 lang=cpp
 *
 * [962] Maximum Width Ramp
 *
 * https://leetcode.com/problems/maximum-width-ramp/description/
 *
 * algorithms
 * Medium (55.75%)
 * Likes:    2801
 * Dislikes: 95
 * Total Accepted:    198.8K
 * Total Submissions: 356.4K
 * Testcase Example:  '[6,0,8,2,1,5]'
 *
 * A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i]
 * <= nums[j]. The width of such a ramp is j - i.
 * 
 * Given an integer array nums, return the maximum width of a ramp in nums. If
 * there is no ramp in nums, return 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [6,0,8,2,1,5]
 * Output: 4
 * Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1]
 * = 0 and nums[5] = 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [9,8,1,0,1,9,4,0,4,1]
 * Output: 7
 * Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2]
 * = 1 and nums[9] = 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 5 * 10^4
 * 0 <= nums[i] <= 5 * 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int ans = 0, n = nums.size();
        vector<int> stk;
        for (int i = 0; i < n; i++) {
            if (stk.empty() || nums[i] < nums[stk.back()]) {
                stk.push_back(i);
            }
        }
        for (int j = n - 1; j >= 0; j--) {
            while (!stk.empty() && nums[j] >= nums[stk.back()]) {
                ans = max(ans, j - stk.back());
                stk.pop_back();
            }
        }
        return ans;
    }
};
// @lc code=end

