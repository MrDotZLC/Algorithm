/*
 * @lc app=leetcode id=2104 lang=cpp
 *
 * [2104] Sum of Subarray Ranges
 *
 * https://leetcode.com/problems/sum-of-subarray-ranges/description/
 *
 * algorithms
 * Medium (60.08%)
 * Likes:    2850
 * Dislikes: 141
 * Total Accepted:    189.5K
 * Total Submissions: 314.7K
 * Testcase Example:  '[1,2,3]'
 *
 * You are given an integer array nums. The range of a subarray of nums is the
 * difference between the largest and smallest element in the subarray.
 * 
 * Return the sum of all subarray ranges of nums.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: 4
 * Explanation: The 6 subarrays of nums are the following:
 * [1], range = largest - smallest = 1 - 1 = 0 
 * [2], range = 2 - 2 = 0
 * [3], range = 3 - 3 = 0
 * [1,2], range = 2 - 1 = 1
 * [2,3], range = 3 - 2 = 1
 * [1,2,3], range = 3 - 1 = 2
 * So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,3,3]
 * Output: 4
 * Explanation: The 6 subarrays of nums are the following:
 * [1], range = largest - smallest = 1 - 1 = 0
 * [3], range = 3 - 3 = 0
 * [3], range = 3 - 3 = 0
 * [1,3], range = 3 - 1 = 2
 * [3,3], range = 3 - 3 = 0
 * [1,3,3], range = 3 - 1 = 2
 * So the sum of all ranges is 0 + 0 + 0 + 2 + 0 + 2 = 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [4,-2,-3,4,1]
 * Output: 59
 * Explanation: The sum of all subarray ranges of nums is 59.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 1000
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 * 
 * Follow-up: Could you find a solution with O(n) time complexity?
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        vector<int> stk = {-1};
        for (int r = 0; r <= n; r++) {
            while (stk.size() > 1 && (r == n || nums[stk.back()] > nums[r])) { // 最小值
                int i = stk.back();
                stk.pop_back();
                ans -= 1LL * nums[i] * (r - i) * (i - stk.back());
            }
            stk.push_back(r);
        }
        stk = {-1};
        for (int r = 0; r <= n; r++) {
             while (stk.size() > 1 && (r == n || nums[stk.back()] <= nums[r])) { // 最大值
                int i = stk.back();
                stk.pop_back();
                ans += 1LL * nums[i] * (r - i) * (i - stk.back());
            }
            stk.push_back(r);
        }
        return ans;
    }
};
// @lc code=end

