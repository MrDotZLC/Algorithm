/*
 * @lc app=leetcode id=491 lang=cpp
 *
 * [491] Non-decreasing Subsequences
 *
 * https://leetcode.com/problems/non-decreasing-subsequences/description/
 *
 * algorithms
 * Medium (61.79%)
 * Likes:    3782
 * Dislikes: 237
 * Total Accepted:    197.6K
 * Total Submissions: 318.7K
 * Testcase Example:  '[4,6,7,7]'
 *
 * Given an integer array nums, return all the different possible
 * non-decreasing subsequences of the given array with at least two elements.
 * You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,6,7,7]
 * Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,4,3,2,1]
 * Output: [[4,4]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 15
 * -100 <= nums[i] <= 100
 * 
 * 
 */
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> findSubsequences1(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                if (path.size() > 1) {
                    ans.insert(path);
                }
                return;
            }

            int x = nums[i];
            if (path.size() == 0 || x >= path.back()) {
                path.push_back(x);
                dfs(dfs, i + 1);
                path.pop_back();
            }

            dfs(dfs, i + 1);
        };
        dfs(dfs, 0);
        return vector<vector<int>>(ans.begin(), ans.end());
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i) -> void {
            if (path.size() > 1) {
                ans.insert(path);
            }

            for (int j = i; j < n; j++) {
                if (path.empty() || nums[j] >= path.back()) {
                    path.push_back(nums[j]);
                    dfs(dfs, j + 1);
                    path.pop_back();
                }
            }
        };
        dfs(dfs, 0);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};
// @lc code=end

