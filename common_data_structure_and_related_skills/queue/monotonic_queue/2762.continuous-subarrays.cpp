/*
 * @lc app=leetcode id=2762 lang=cpp
 *
 * [2762] Continuous Subarrays
 *
 * https://leetcode.com/problems/continuous-subarrays/description/
 *
 * algorithms
 * Medium (58.00%)
 * Likes:    1471
 * Dislikes: 96
 * Total Accepted:    115K
 * Total Submissions: 198.5K
 * Testcase Example:  '[5,4,2,4]'
 *
 * You are given a 0-indexed integer array nums. A subarray of nums is called
 * continuous if:
 * 
 * 
 * Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of
 * indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.
 * 
 * 
 * Return the total number of continuous subarrays.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,4,2,4]
 * Output: 8
 * Explanation: 
 * Continuous subarray of size 1: [5], [4], [2], [4].
 * Continuous subarray of size 2: [5,4], [4,2], [2,4].
 * Continuous subarray of size 3: [4,2,4].
 * There are no subarrys of size 4.
 * Total continuous subarrays = 4 + 3 + 1 = 8.
 * It can be shown that there are no more continuous subarrays.
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: 6
 * Explanation: 
 * Continuous subarray of size 1: [1], [2], [3].
 * Continuous subarray of size 2: [1,2], [2,3].
 * Continuous subarray of size 3: [1,2,3].
 * Total continuous subarrays = 3 + 2 + 1 = 6.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
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
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size(), left = 0;
        long long ans = 0;
        deque<int> mx, mn;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (!mx.empty() && nums[mx.back()] < x) {
                mx.pop_back();
            }
            mx.push_back(i);
            while (!mn.empty() && nums[mn.back()] > x) {
                mn.pop_back();
            }
            mn.push_back(i);

            while (nums[mx.front()] - nums[mn.front()] > 2) {
                left++;
                if (mx.front() < left) {
                    mx.pop_front();
                }
                if (mn.front() < left) {
                    mn.pop_front();
                }
            }
            ans += i - left + 1;
        }
        return ans;
    }
};
// @lc code=end

