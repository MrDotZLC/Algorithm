/*
 * @lc app=leetcode id=1438 lang=cpp
 *
 * [1438] Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
 *
 * https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/
 *
 * algorithms
 * Medium (56.82%)
 * Likes:    4397
 * Dislikes: 221
 * Total Accepted:    289.2K
 * Total Submissions: 507.1K
 * Testcase Example:  '[8,2,4,7]\n4'
 *
 * Given an array of integers nums and an integer limit, return the size of the
 * longest non-empty subarray such that the absolute difference between any two
 * elements of this subarray is less than or equal to limit.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [8,2,4,7], limit = 4
 * Output: 2 
 * Explanation: All subarrays are: 
 * [8] with maximum absolute diff |8-8| = 0 <= 4.
 * [8,2] with maximum absolute diff |8-2| = 6 > 4. 
 * [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
 * [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
 * [2] with maximum absolute diff |2-2| = 0 <= 4.
 * [2,4] with maximum absolute diff |2-4| = 2 <= 4.
 * [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
 * [4] with maximum absolute diff |4-4| = 0 <= 4.
 * [4,7] with maximum absolute diff |4-7| = 3 <= 4.
 * [7] with maximum absolute diff |7-7| = 0 <= 4. 
 * Therefore, the size of the longest subarray is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [10,1,2,4,7,2], limit = 5
 * Output: 4 
 * Explanation: The subarray [2,4,7,2] is the longest since the maximum
 * absolute diff is |2-7| = 5 <= 5.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [4,2,2,2,4,4,2,2], limit = 0
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 0 <= limit <= 10^9
 * 
 * 
 */
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size(), ans = 0, l = 0;
        deque<int> mx, mn;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            
            // 入
            while (!mx.empty() && nums[mx.back()] < x) {
                mx.pop_back();
            }
            mx.push_back(i);

            while (!mn.empty() && nums[mn.back()] > x) {
                mn.pop_back();
            }
            mn.push_back(i);

            // 出
            while (nums[mx.front()] - nums[mn.front()] > limit) {
                l++;
                if (mx.front() < l) {
                    mx.pop_front();
                }
                if (mn.front() < l) {
                    mn.pop_front();
                }
            }

            ans = max(ans, i - l + 1);
        }
        return ans;
    }
};
// @lc code=end

