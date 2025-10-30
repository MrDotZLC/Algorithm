/*
 * @lc app=leetcode id=377 lang=cpp
 *
 * [377] Combination Sum IV
 *
 * https://leetcode.com/problems/combination-sum-iv/description/
 *
 * algorithms
 * Medium (54.68%)
 * Likes:    7689
 * Dislikes: 696
 * Total Accepted:    575.5K
 * Total Submissions: 1.1M
 * Testcase Example:  '[1,2,3]\n4'
 *
 * Given an array of distinct integers nums and a target integer target, return
 * the number of possible combinations that add up to target.
 * 
 * The test cases are generated so that the answer can fit in a 32-bit
 * integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3], target = 4
 * Output: 7
 * Explanation:
 * The possible combination ways are:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 * Note that different sequences are counted as different combinations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [9], target = 3
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 200
 * 1 <= nums[i] <= 1000
 * All the elements of nums are unique.
 * 1 <= target <= 1000
 * 
 * 
 * 
 * Follow up: What if negative numbers are allowed in the given array? How does
 * it change the problem? What limitation we need to add to the question to
 * allow negative numbers?
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP
    int combinationSum4_1(vector<int>& nums, int target) {
        vector<int> memo(target + 1, -1);
        auto dfs = [&](auto &dfs, int remaining) -> int {
            if (remaining == 0) {
                return 1;
            }
            int &ans = memo[remaining]; // 这是个引用，用于更新memo[remaining]
            if (ans != -1) {
                return ans;
            }
            ans = 0;
            for (int x : nums) {
                if (x <= remaining) {
                    ans += dfs(dfs, remaining - x);
                }
            }
            return ans;
        };  
        return dfs(dfs, target);
    }

    // 递推
    int combinationSum4(vector<int>& nums, int target) {
        vector<__int128_t> f(target + 1);
        f[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int x : nums) {
                if (x <= i) {
                    f[i] += f[i - x];
                }
            }
        }
        return (int)f[target];
    }
};
// @lc code=end

