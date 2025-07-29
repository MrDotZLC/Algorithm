/*
 * @lc app=leetcode id=18 lang=cpp
 *
 * [18] 4Sum
 *
 * https://leetcode.com/problems/4sum/description/
 *
 * algorithms
 * Medium (38.46%)
 * Likes:    12228
 * Dislikes: 1477
 * Total Accepted:    1.4M
 * Total Submissions: 3.5M
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * Given an array nums of n integers, return an array of all the unique
 * quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
 * 
 * 
 * 0 <= a, b, c, d < n
 * a, b, c, and d are distinct.
 * nums[a] + nums[b] + nums[c] + nums[d] == target
 * 
 * 
 * You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,0,-1,0,-2,2], target = 0
 * Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,2,2,2,2], target = 8
 * Output: [[2,2,2,2]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 200
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
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
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 3; i++) {
            long long x = nums[i];
            if (i && x == nums[i - 1]) continue; // skip repeat
            if (x + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break; // pruning
            if (x + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue; // pruning

            for (int j = i + 1; j < n - 2; j++) {
                long long y = nums[j];
                if (j > i + 1 && y == nums[j - 1]) continue; // skip repeat
                if (x + y + nums[j + 1] + nums[j + 2] > target) break; // pruning
                if (x + y + nums[n - 2] + nums[n - 1] < target) continue; // pruning

                int l = j + 1, r = n - 1;
                while (l < r) {
                    long long sum = x + y + nums[l] + nums[r];
                    if (sum > target) {
                        r--;
                    } else if (sum < target) {
                        l++;
                    } else {
                        // if (l == j + 1 || nums[l] != nums[l - 1]) {
                        //     ans.push_back({x, y, nums[l], nums[r]});
                        // }
                        // l++;
                        // r--;
                        ans.push_back({(int)x, (int)y, nums[l], nums[r]});
                        for (l++; l < r && nums[l] == nums[l - 1]; l++);
                        for (r--; l < r && nums[r] == nums[r + 1]; r--);
                    }
                }
            }
        }
        return ans;
    }
};
// @lc code=end

