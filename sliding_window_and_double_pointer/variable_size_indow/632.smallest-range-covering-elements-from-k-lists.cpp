/*
 * @lc app=leetcode id=632 lang=cpp
 *
 * [632] Smallest Range Covering Elements from K Lists
 *
 * https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/description/
 *
 * algorithms
 * Hard (69.79%)
 * Likes:    4248
 * Dislikes: 96
 * Total Accepted:    221.2K
 * Total Submissions: 316.8K
 * Testcase Example:  '[[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]'
 *
 * You have k lists of sorted integers in non-decreasing order. Find the
 * smallest range that includes at least one number from each of the k lists.
 * 
 * We define the range [a, b] is smaller than range [c, d] if b - a < d - c or
 * a < c if b - a == d - c.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
 * Output: [20,24]
 * Explanation: 
 * List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
 * List 2: [0, 9, 12, 20], 20 is in range [20,24].
 * List 3: [5, 18, 22, 30], 22 is in range [20,24].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
 * Output: [1,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * nums.length == k
 * 1 <= k <= 3500
 * 1 <= nums[i].length <= 50
 * -10^5 <= nums[i][j] <= 10^5
 * nums[i] is sorted in non-decreasing order.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, int>> all_data;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums[i].size(); j++) {
                all_data.emplace_back(nums[i][j], i);
            }
        }
        sort(all_data.begin(), all_data.end());

        int left = 0;
        int ans_l = all_data[0].first;
        int ans_r = all_data.back().first;
        int empty = nums.size();
        vector<int> freq(empty);
        for (const auto& [r, i] : all_data) {
            if (freq[i] == 0) {
                --empty;
            }
            ++freq[i];
            while (empty == 0) {
                auto &[l, j] = all_data[left];
                if (r - l < ans_r - ans_l) {
                    ans_l = l;
                    ans_r = r;
                }
                if (--freq[j] == 0) {
                    ++empty;
                }
                ++left;
            }
        }
        return {ans_l, ans_r};
    }
};
// @lc code=end

