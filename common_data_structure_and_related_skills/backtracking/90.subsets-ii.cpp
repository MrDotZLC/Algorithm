/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 *
 * https://leetcode.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (59.75%)
 * Likes:    10601
 * Dislikes: 388
 * Total Accepted:    1.3M
 * Total Submissions: 2.2M
 * Testcase Example:  '[1,2,2]'
 *
 * Given an integer array nums that may contain duplicates, return all possible
 * subsets (the power set).
 * 
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 * 
 * 
 * Example 1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 选哪个
    vector<vector<int>> subsetsWithDup1(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i) -> void {
            ans.push_back(path);

            for (int j = i; j < n; j++) {
                if (j > i && nums[j] == nums[j - 1]) {
                    continue;
                }
                path.push_back(nums[j]);
                dfs(dfs, j + 1);
                path.pop_back();
            }
        };
        dfs(dfs, 0);
        return ans;
    }

    // 选或不选
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }

            // 选
            int x = nums[i];
            path.push_back(x);
            dfs(dfs, i + 1);
            path.pop_back();

            // 不选，则后续相同也不选
            i++;
            while (i < n && x == nums[i]) {
                i++;
            }
            dfs(dfs, i);
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

