/*
 * @lc app=leetcode id=421 lang=cpp
 *
 * [421] Maximum XOR of Two Numbers in an Array
 *
 * https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/description/
 *
 * algorithms
 * Medium (53.34%)
 * Likes:    5850
 * Dislikes: 418
 * Total Accepted:    206.6K
 * Total Submissions: 387.3K
 * Testcase Example:  '[3,10,5,25,2,8]'
 *
 * Given an integer array nums, return the maximum result of nums[i] XOR
 * nums[j], where 0 <= i <= j < n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,10,5,25,2,8]
 * Output: 28
 * Explanation: The maximum result is 5 XOR 25 = 28.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
 * Output: 127
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^5
 * 0 <= nums[i] <= 2^31 - 1
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 位运算+字典树思路
    int findMaximumXOR(vector<int>& nums) {
        // int high_bit = __lg(ranges::max(nums));
        int high_bit = bit_width((unsigned)ranges::max(nums)) - 1;
        int ans = 0, mask = 0;
        unordered_set<int> seen;
        for (int i = high_bit; i >= 0; i--) {
            seen.clear();
            mask |= 1 << i;
            int new_ans = ans | (1 << i);
            for (int x : nums) {
                x &= mask;
                if (seen.contains(new_ans ^ x)) {
                    ans = new_ans;
                    break;
                }
                seen.insert(x);
            }
        }
        return ans;
    }
};
// @lc code=end

