/*
 * @lc app=leetcode id=1546 lang=cpp
 *
 * [1546] Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
 *
 * https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/description/
 *
 * algorithms
 * Medium (48.15%)
 * Likes:    1106
 * Dislikes: 28
 * Total Accepted:    33.5K
 * Total Submissions: 69.3K
 * Testcase Example:  '[1,1,1,1,1]\n2'
 *
 * Given an array nums and an integer target, return the maximum number of
 * non-empty non-overlapping subarrays such that the sum of values in each
 * subarray is equal to target.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,1,1,1], target = 2
 * Output: 2
 * Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum
 * equals to target(2).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-1,3,5,1,4,2,-9], target = 6
 * Output: 2
 * Explanation: There are 3 subarrays with sum equal to 6.
 * ([5,1], [4,2], [3,5,1,4,2,-9]) but only the first 2 are non-overlapping.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 0 <= target <= 10^6
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
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        int ans = 0, sum = 0, r = -1;
        unordered_map<int, int> pre;
        pre[0] = -1;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (pre.contains(sum - target)) {
                if (pre[sum - target] + 1 > r) {
                    ans++;
                    r = i;
                }
            }
            pre[sum] = i;
        }
        return ans;
    }
};
// @lc code=end

