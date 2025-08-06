/*
 * @lc app=leetcode id=2444 lang=cpp
 *
 * [2444] Count Subarrays With Fixed Bounds
 *
 * https://leetcode.com/problems/count-subarrays-with-fixed-bounds/description/
 *
 * algorithms
 * Hard (69.39%)
 * Likes:    3673
 * Dislikes: 95
 * Total Accepted:    226.1K
 * Total Submissions: 325.9K
 * Testcase Example:  '[1,3,5,2,7,5]\n1\n5'
 *
 * You are given an integer array nums and two integers minK and maxK.
 * 
 * A fixed-bound subarray of nums is a subarray that satisfies the following
 * conditions:
 * 
 * 
 * The minimum value in the subarray is equal to minK.
 * The maximum value in the subarray is equal to maxK.
 * 
 * 
 * Return the number of fixed-bound subarrays.
 * 
 * A subarray is a contiguous part of an array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
 * Output: 2
 * Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,1,1], minK = 1, maxK = 1
 * Output: 10
 * Explanation: Every subarray of nums is a fixed-bound subarray. There are 10
 * possible subarrays.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 10^5
 * 1 <= nums[i], minK, maxK <= 10^6
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
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long ans = 0;
        int l = -1, r = -1, invalid = -1;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            if (x == minK) l = i;
            if (x == maxK) r = i;
            if (x < minK || x > maxK) invalid = i;

            ans += max(min(l, r) - invalid, 0);
        }
        return ans;
    }
};
// @lc code=end

