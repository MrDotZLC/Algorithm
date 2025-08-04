/*
 * @lc app=leetcode id=1537 lang=cpp
 *
 * [1537] Get the Maximum Score
 *
 * https://leetcode.com/problems/get-the-maximum-score/description/
 *
 * algorithms
 * Hard (40.13%)
 * Likes:    1039
 * Dislikes: 54
 * Total Accepted:    32.4K
 * Total Submissions: 80.7K
 * Testcase Example:  '[2,4,5,8,10]\n[4,6,8,9]'
 *
 * You are given two sorted arrays of distinct integers nums1 and nums2.
 * 
 * A valid path is defined as follows:
 * 
 * 
 * Choose array nums1 or nums2 to traverse (from index-0).
 * Traverse the current array from left to right.
 * If you are reading any value that is present in nums1 and nums2 you are
 * allowed to change your path to the other array. (Only one repeated value is
 * considered in the valid path).
 * 
 * 
 * The score is defined as the sum of unique values in a valid path.
 * 
 * Return the maximum score you can obtain of all possible valid paths. Since
 * the answer may be too large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
 * Output: 30
 * Explanation: Valid paths:
 * [2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],  (starting from nums1)
 * [4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]    (starting from nums2)
 * The maximum is obtained with the path in green [2,4,6,8,10].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [1,3,5,7,9], nums2 = [3,5,100]
 * Output: 109
 * Explanation: Maximum sum is obtained with the path [1,3,5,100].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums1 = [1,2,3,4,5], nums2 = [6,7,8,9,10]
 * Output: 40
 * Explanation: There are no common elements between nums1 and nums2.
 * Maximum sum is obtained with the path [6,7,8,9,10].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 10^5
 * 1 <= nums1[i], nums2[i] <= 10^7
 * nums1 and nums2 are strictly increasing.
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
    int MOD = 1e9 + 7;
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        long ans = 0L;
        
        int i = 0, j = 0;
        long sum1 = 0L, sum2 = 0L;
        // loop nums1
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] > nums2[j]) {
                sum2 += nums2[j++];
            } else if(nums1[i] < nums2[j]) {
                sum1 += nums1[i++];
            } else {
                ans += max(sum1, sum2);
                sum1 = nums1[i++];
                sum2 = nums2[j++];
            }
        }

        while (i < nums1.size()) {
            sum1 += nums1[i++];
        }

        while (j < nums2.size()) {
            sum2 += nums2[j++];
        }

        ans += max(sum1, sum2);
        return ans % MOD;
    }
};
// @lc code=end

