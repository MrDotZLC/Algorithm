/*
 * @lc app=leetcode id=930 lang=cpp
 *
 * [930] Binary Subarrays With Sum
 *
 * https://leetcode.com/problems/binary-subarrays-with-sum/description/
 *
 * algorithms
 * Medium (66.52%)
 * Likes:    4449
 * Dislikes: 151
 * Total Accepted:    398.7K
 * Total Submissions: 598.6K
 * Testcase Example:  '[1,0,1,0,1]\n2'
 *
 * Given a binary array nums and an integer goal, return the number of
 * non-empty subarrays with a sum goal.
 * 
 * A subarray is a contiguous part of the array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 * Explanation: The 4 subarrays are bolded and underlined below:
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,0,0,0,0], goal = 0
 * Output: 15
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 3 * 10^4
 * nums[i] is either 0 or 1.
 * 0 <= goal <= nums.length
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    // sum(i, j) = k, three pointers.
    int numSubarraysWithSum1(vector<int>& nums, int goal) {
        int ans = 0, l1 = 0, l2 = 0, sum1 = 0, sum2 = 0;
        for (int r = 0; r < nums.size(); r++) {
            sum1 += nums[r];
            sum2 += nums[r];

            while (l1 <= r && sum1 >= goal) {
                sum1 -= nums[l1++];
            }
            while (l2 <= r && sum2 >= goal + 1) {
                sum2 -= nums[l2++];
            }

            ans += (l1 - l2);
        }
        return ans;
    }

    // prefix + hash
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int ans = 0, sum = 0;
        unordered_map<int, int> freq;

        for (int r = 0; r < nums.size(); r++) {
            freq[sum]++;
            sum += nums[r];
            ans += freq[sum - goal];
        }
        return ans;
    }
};
// @lc code=end

