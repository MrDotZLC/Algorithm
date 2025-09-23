/*
 * @lc app=leetcode id=47 lang=cpp
 *
 * [47] Permutations II
 *
 * https://leetcode.com/problems/permutations-ii/description/
 *
 * algorithms
 * Medium (61.80%)
 * Likes:    8955
 * Dislikes: 158
 * Total Accepted:    1.2M
 * Total Submissions: 1.9M
 * Testcase Example:  '[1,1,2]'
 *
 * Given a collection of numbers, nums, that might contain duplicates, return
 * all possible unique permutations in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,2]
 * Output:
 * [[1,1,2],
 * ⁠[1,2,1],
 * ⁠[2,1,1]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 8
 * -10 <= nums[i] <= 10
 * 
 * 
 */
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path(n), on_path(n);

        function<void(int)> dfs = [&](int i) -> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }

            for (int j = 0; j < n; j++) {
                if (on_path[j] || j > 0 && nums[j] == nums[j - 1] && !on_path[j - 1]) {
                    continue;
                }
                path[i] = nums[j];
                on_path[j] = 1;
                dfs(i + 1);
                on_path[j] = 0;
            }
        };
        dfs(0);
        return ans;
    }
};
// @lc code=end

