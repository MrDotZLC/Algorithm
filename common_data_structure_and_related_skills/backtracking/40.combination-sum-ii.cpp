/*
 * @lc app=leetcode id=40 lang=cpp
 *
 * [40] Combination Sum II
 *
 * https://leetcode.com/problems/combination-sum-ii/description/
 *
 * algorithms
 * Medium (57.87%)
 * Likes:    11872
 * Dislikes: 366
 * Total Accepted:    1.5M
 * Total Submissions: 2.6M
 * Testcase Example:  '[10,1,2,7,6,1,5]\n8'
 *
 * Given a collection of candidate numbers (candidates) and a target number
 * (target), find all unique combinations in candidates where the candidate
 * numbers sum to target.
 * 
 * Each number in candidates may only be used once in the combination.
 * 
 * Note: The solution set must not contain duplicate combinations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: 
 * [
 * [1,1,6],
 * [1,2,5],
 * [1,7],
 * [2,6]
 * ]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: candidates = [2,5,2,1,2], target = 5
 * Output: 
 * [
 * [1,2,2],
 * [5]
 * ]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= candidates.length <= 100
 * 1 <= candidates[i] <= 50
 * 1 <= target <= 30
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> combinationSum21(vector<int>& candidates, int target) {
        ranges::sort(candidates);
        int n = candidates.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i, int sum) -> void {
            if (i == n) {
                if (sum == target) {
                    ans.push_back(path);
                }
                return;
            }

            if (sum > target) {
                return;
            }

            int x = candidates[i];
            path.push_back(x);
            dfs(dfs, i + 1, sum + x);
            path.pop_back();

            i++;
            while (i < n && x == candidates[i]) {
                i++;
            }
            dfs(dfs, i, sum);
        };
        dfs(dfs, 0, 0);
        return ans;
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        ranges::sort(candidates);
        int n = candidates.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](auto &dfs, int i, int sum) -> void {
            if (sum == target) {
                ans.push_back(path);
                return;
            }

            if (sum > target) {
                return;
            }

            for (int j = i; j < n; j++) {
                if (j > i && candidates[j] == candidates[j - 1]) {
                    continue;
                }
                path.push_back(candidates[j]);
                dfs(dfs, j + 1, sum + candidates[j]);
                path.pop_back();
            }
        };
        dfs(dfs, 0, 0);
        return ans;
    }
};
// @lc code=end

