/*
 * @lc app=leetcode id=2342 lang=cpp
 *
 * [2342] Max Sum of a Pair With Equal Sum of Digits
 *
 * https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/description/
 *
 * algorithms
 * Medium (65.98%)
 * Likes:    1394
 * Dislikes: 46
 * Total Accepted:    242.1K
 * Total Submissions: 367.1K
 * Testcase Example:  '[18,43,36,13,7]'
 *
 * You are given a 0-indexed array nums consisting of positive integers. You
 * can choose two indices i and j, such that i != j, and the sum of digits of
 * the number nums[i] is equal to that of nums[j].
 * 
 * Return the maximum value of nums[i] + nums[j] that you can obtain over all
 * possible indices i and j that satisfy the conditions. If no such pair of
 * indices exists, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [18,43,36,13,7]
 * Output: 54
 * Explanation: The pairs (i, j) that satisfy the conditions are:
 * - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18
 * + 36 = 54.
 * - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43
 * + 7 = 50.
 * So the maximum sum that we can obtain is 54.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [10,12,19,14]
 * Output: -1
 * Explanation: There are no two numbers that satisfy the conditions, so we
 * return -1.
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
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int ans = -1;
        unordered_map<int, int> idx;
        for (int j = 0; j < nums.size(); j++) {
            int x = nums[j];
            int bit_sum = 0;
            while (x > 0) {
                bit_sum += x % 10;
                x /= 10;
            }
            if (idx.contains(bit_sum)) {
                ans = max(ans, nums[j] + idx[bit_sum]);
            }
            idx[bit_sum] = max(idx[bit_sum], nums[j]);
        }
        return ans;
    }
};
// @lc code=end

