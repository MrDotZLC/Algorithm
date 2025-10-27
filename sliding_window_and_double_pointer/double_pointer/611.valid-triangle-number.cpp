/*
 * @lc app=leetcode id=611 lang=cpp
 *
 * [611] Valid Triangle Number
 *
 * https://leetcode.com/problems/valid-triangle-number/description/
 *
 * algorithms
 * Medium (52.49%)
 * Likes:    3945
 * Dislikes: 227
 * Total Accepted:    233K
 * Total Submissions: 443.4K
 * Testcase Example:  '[2,2,3,4]'
 *
 * Given an integer array nums, return the number of triplets chosen from the
 * array that can make triangles if we take them as side lengths of a
 * triangle.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,2,3,4]
 * Output: 3
 * Explanation: Valid combinations are: 
 * 2,3,4 (using the first 2)
 * 2,3,4 (using the second 2)
 * 2,2,3
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,2,3,4]
 * Output: 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 1000
 * 0 <= nums[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (int k = nums.size() - 1; k > 1; k--) {
            int c = nums[k];
            if (nums[0] + nums[1] > c) {
                ans += (k - 1) * k * (k + 1) / 6;
                break;
            }
            if (nums[k - 2] + nums[k - 1] <= c) {
                continue;
            }
            int l = 0, r = k - 1;
            while (l < r) {
                int a = nums[l], b = nums[r];
                if (a + b > c) {
                    ans += r - l;
                    r--;
                } else {
                    l++;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

