/*
 * @lc app=leetcode id=2367 lang=cpp
 *
 * [2367] Number of Arithmetic Triplets
 *
 * https://leetcode.com/problems/number-of-arithmetic-triplets/description/
 *
 * algorithms
 * Easy (85.06%)
 * Likes:    1359
 * Dislikes: 94
 * Total Accepted:    164.6K
 * Total Submissions: 193.5K
 * Testcase Example:  '[0,1,4,6,7,10]\n3'
 *
 * You are given a 0-indexed, strictly increasing integer array nums and a
 * positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the
 * following conditions are met:
 * 
 * 
 * i < j < k,
 * nums[j] - nums[i] == diff, and
 * nums[k] - nums[j] == diff.
 * 
 * 
 * Return the number of unique arithmetic triplets.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [0,1,4,6,7,10], diff = 3
 * Output: 2
 * Explanation:
 * (1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
 * (2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 ==
 * 3. 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,5,6,7,8,9], diff = 2
 * Output: 2
 * Explanation:
 * (0, 2, 4) is an arithmetic triplet because both 8 - 6 == 2 and 6 - 4 == 2.
 * (1, 3, 5) is an arithmetic triplet because both 9 - 7 == 2 and 7 - 5 ==
 * 2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 200
 * 0 <= nums[i] <= 200
 * 1 <= diff <= 50
 * nums is strictly increasing.
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
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                if (nums[j] - nums[i] < diff) continue;
                if (nums[j] - nums[i] > diff) break; // 因为是递增数组，后面的只会更大
                for (int k = j + 1; k < n; k++) {
                    if (nums[k] - nums[j] < diff) continue;
                    if (nums[k] - nums[j] > diff) break;
                    ans++;
                    break;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

