/*
 * @lc app=leetcode id=219 lang=cpp
 *
 * [219] Contains Duplicate II
 *
 * https://leetcode.com/problems/contains-duplicate-ii/description/
 *
 * algorithms
 * Easy (49.30%)
 * Likes:    7026
 * Dislikes: 3268
 * Total Accepted:    1.5M
 * Total Submissions: 3M
 * Testcase Example:  '[1,2,3,1]\n3'
 *
 * Given an integer array nums and an integer k, return true if there are two
 * distinct indices i and j in the array such that nums[i] == nums[j] and abs(i
 * - j) <= k.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 0 <= k <= 10^5
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool containsNearbyDuplicate1(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> idx;
        for (int j = 0; j < nums.size(); j++) {
            for (int i = idx[nums[j]].size() - 1; i >= 0; i--) {
                if (j - idx[nums[j]][i] <= k) {
                    return true;
                }
            }
            idx[nums[j]].push_back(j);;
        }
        return false;
    }

    bool containsNearbyDuplicate2(vector<int>& nums, int k) {
        unordered_map<int, int> idx;
        for (int j = 0; j < nums.size(); j++) {
            if (idx[nums[j]] && j - (idx[nums[j]] - 1) <= k) {
                return true;
            }
            idx[nums[j]] = j + 1;
        }
        return false;
    }

    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> idx;
        for (int j = 0; j < nums.size(); j++) {
            if (!idx.insert(nums[j]).second) {
                return true;
            }
            if (j >= k) {
                idx.erase(nums[j - k]);
            }
        }
        return false;
    }
};
// @lc code=end

