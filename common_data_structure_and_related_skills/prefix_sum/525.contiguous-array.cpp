/*
 * @lc app=leetcode id=525 lang=cpp
 *
 * [525] Contiguous Array
 *
 * https://leetcode.com/problems/contiguous-array/description/
 *
 * algorithms
 * Medium (49.56%)
 * Likes:    8507
 * Dislikes: 437
 * Total Accepted:    598.4K
 * Total Submissions: 1.2M
 * Testcase Example:  '[0,1]'
 *
 * Given a binary array nums, return the maximum length of a contiguous
 * subarray with an equal number of 0 and 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [0,1]
 * Output: 2
 * Explanation: [0, 1] is the longest contiguous subarray with an equal number
 * of 0 and 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,0]
 * Output: 2
 * Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal
 * number of 0 and 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [0,1,1,1,1,1,0,0,0]
 * Output: 6
 * Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal
 * number of 0 and 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums[i] is either 0 or 1.
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
    int findMaxLength(vector<int>& nums) {
        int ans = 0, sum = 0;
        unordered_map<int, int> idx = {{0, -1}};
        for (int i = 0; i < nums.size(); i++) {
            nums[i] == 0 ? --sum : ++sum;
            if (idx.contains(sum)) {
                ans = max(ans, i - idx[sum]);
            }
            if (!idx.contains(sum)) {
                idx[sum] = i;
            }
        }
        return ans;
    }
};
// @lc code=end

