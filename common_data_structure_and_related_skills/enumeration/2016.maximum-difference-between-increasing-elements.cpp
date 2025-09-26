/*
 * @lc app=leetcode id=2016 lang=cpp
 *
 * [2016] Maximum Difference Between Increasing Elements
 *
 * https://leetcode.com/problems/maximum-difference-between-increasing-elements/description/
 *
 * algorithms
 * Easy (66.20%)
 * Likes:    1480
 * Dislikes: 44
 * Total Accepted:    268.6K
 * Total Submissions: 404.8K
 * Testcase Example:  '[7,1,5,4]'
 *
 * Given a 0-indexed integer array nums of size n, find the maximum difference
 * between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j
 * < n and nums[i] < nums[j].
 * 
 * Return the maximum difference. If no such i and j exists, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [7,1,5,4]
 * Output: 4
 * Explanation:
 * The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 -
 * 1 = 4.
 * Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 =
 * 6, but i > j, so it is not valid.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [9,4,3,2]
 * Output: -1
 * Explanation:
 * There is no i and j such that i < j and nums[i] < nums[j].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,5,2,10]
 * Output: 9
 * Explanation:
 * The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 -
 * 1 = 9.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 2 <= n <= 1000
 * 1 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int ans = -1, mn = nums[0];
        for (int j = 1; j < nums.size(); j++) {
            int x = nums[j];
            ans = max(ans, x - mn ? x - mn : -1);
            mn = min(mn, x);
        }
        return ans;
    }
};
// @lc code=end

