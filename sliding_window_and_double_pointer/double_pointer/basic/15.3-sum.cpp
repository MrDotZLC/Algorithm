/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * algorithms
 * Medium (37.29%)
 * Likes:    33481
 * Dislikes: 3142
 * Total Accepted:    4.9M
 * Total Submissions: 13.2M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * Given an integer array nums, return all the triplets [nums[i], nums[j],
 * nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
 * nums[k] == 0.
 * 
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation: 
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not
 * matter.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum up to 0.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums up to 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 3000
 * -10^5 <= nums[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
// @lc code=start
class Solution {
public:
    // 1. exhaustion: O(n^2), O(n)
    vector<vector<int>> threeSum2(vector<int>& nums) {
        vector<vector<int>> ans;
        set<vector<int>> filter;
        map<pair<int, int>, int> freq;
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                int target = 0 - (nums[i] + nums[j]);
                freq[{i, j}] = target;
            }
        }

        
        for (int i = 0; i < nums.size(); i++) {
            for (auto &[pos, target] : freq) {
                if (i != pos.first && i != pos.second && nums[i] == target) {
                    int x = min({nums[pos.first], nums[pos.second], nums[i]});
                    int z = max({nums[pos.first], nums[pos.second], nums[i]});
                    int y = 0 - (x + z);
                    vector<int> tmp = {x, y, z};
                    if (filter.insert(tmp).second) {
                        ans.push_back(tmp);
                    }
                }
            }
        }

        return ans;
    }

    // double pointer
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; i++) {
            int x = nums[i];
            if (i && x == nums[i - 1]) continue; // skip repeat
            if (x + nums[i + 1] + nums[i + 2] > 0) break; // pruning
            if (x + nums[n - 2] + nums[n - 1] < 0) continue; // pruning
            int l = i + 1, r = n - 1;
            while (l < r) { // double pointer
                int s = x + nums[l] + nums[r];
                if (s > 0) {
                    r--;
                } else if (s < 0) {
                    l++;
                } else {
                    ans.push_back({x, nums[l], nums[r]});
                    for (l++; l < r && nums[l] == nums[l - 1]; l++); // skip repeat
                    for (r--; l < r && nums[r] == nums[r + 1]; r--); // skip repeat
                    // if (l == i + 1 || nums[l] != nums[l - 1]) {
                    //     ans.push_back({x, nums[l], nums[r]});
                    // }
                    // l++;
                    // r--;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

