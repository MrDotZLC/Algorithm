/*
 * @lc app=leetcode id=1248 lang=cpp
 *
 * [1248] Count Number of Nice Subarrays
 *
 * https://leetcode.com/problems/count-number-of-nice-subarrays/description/
 *
 * algorithms
 * Medium (73.60%)
 * Likes:    5068
 * Dislikes: 130
 * Total Accepted:    382.7K
 * Total Submissions: 519.5K
 * Testcase Example:  '[1,1,2,1,1]\n3'
 *
 * Given an array of integers nums and an integer k. A continuous subarray is
 * called nice if there are k odd numbers on it.
 * 
 * Return the number of nice sub-arrays.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,2,1,1], k = 3
 * Output: 2
 * Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and
 * [1,2,1,1].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,4,6], k = 1
 * Output: 0
 * Explanation: There are no odd numbers in the array.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
 * Output: 16
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 50000
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= nums.length
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans = 0, l1 = 0, l2 = 0, count1 = 0, count2 = 0;
        for (int r = 0; r < nums.size(); r++) {
            count1 += nums[r] % 2;
            count2 += nums[r] % 2;

            while (l1 <= r && count1 >= k) {
                count1 -= nums[l1++] % 2;
            }
            while (l2 <= r && count2 >= k + 1) {
                count2 -= nums[l2++] % 2;
            }

            ans += (l1 - l2);
        }
        return ans;
    }
};
// @lc code=end

