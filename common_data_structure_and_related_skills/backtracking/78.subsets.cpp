/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (81.10%)
 * Likes:    18626
 * Dislikes: 325
 * Total Accepted:    2.7M
 * Total Submissions: 3.3M
 * Testcase Example:  '[1,2,3]'
 *
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 * 
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0]
 * Output: [[],[0]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 思考角度：选或不选
    vector<vector<int>> subsets1(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> sub;
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans.push_back(sub);
                return;
            }
            // 不选
            dfs(dfs, i + 1);

            // 选
            sub.push_back(nums[i]);
            dfs(dfs, i + 1);
            sub.pop_back(); // 恢复现场
        };

        dfs(dfs, 0);
        return ans;
    }

    // 思考角度：枚举选哪个
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> sub;
        auto dfs = [&](auto &dfs, int i) -> void {
            ans.push_back(sub);
            for (int j = i; j < n; j++) {
                sub.push_back(nums[j]);
                dfs(dfs, j + 1);
                sub.pop_back();
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

