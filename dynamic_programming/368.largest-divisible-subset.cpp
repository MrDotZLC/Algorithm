/*
 * @lc app=leetcode id=368 lang=cpp
 *
 * [368] Largest Divisible Subset
 *
 * https://leetcode.com/problems/largest-divisible-subset/description/
 *
 * algorithms
 * Medium (48.94%)
 * Likes:    6762
 * Dislikes: 325
 * Total Accepted:    473.3K
 * Total Submissions: 962.9K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a set of distinct positive integers nums, return the largest subset
 * answer such that every pair (answer[i], answer[j]) of elements in this
 * subset satisfies:
 * 
 * 
 * answer[i] % answer[j] == 0, or
 * answer[j] % answer[i] == 0
 * 
 * 
 * If there are multiple solutions, return any of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: [1,2]
 * Explanation: [1,3] is also accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,4,8]
 * Output: [1,2,4,8]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 2 * 10^9
 * All the integers in nums are unique.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 递归+记忆化搜索
    vector<int> largestDivisibleSubset1(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<int> memo(n), from(n, -1); // 记忆化和子集大小，最小来源下标

        auto dfs = [&](auto &dfs, int i) -> int {
            int &res = memo[i];
            if (res) {
                return res;
            }
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j]) {
                    continue;
                }
                int f = dfs(dfs, j);
                if (f > res) {
                    res = f;
                    from[i] = f;
                }
            }
            return ++res;
        };
        int max_f = 0, max_i = 0;
        for (int i = 0; i < n; i++) {
            int f = dfs(dfs, i);
            if (f > max_f) {
                max_f = f;
                max_i = i;
            }
        }
        vector<int> ans;
        for (int i = max_i; i >= 0; i = from[i]) {
            ans.push_back(nums[i]);
        }
        return ans;
    }

    // DP递推
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<int> f(n), from(n, -1); // 记忆化和子集大小，最小来源下标
        int max_i = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && f[j] > f[i]) {
                    f[i] = f[j];
                    from[i] = j;
                }
            }
            f[i]++;
            if (f[i] > f[max_i]) {
                max_i = i;
            }
        }
        vector<int> ans;
        for (int i = max_i; i >= 0; i = from[i]) {
            ans.push_back(nums[i]);
        }
        return ans;
    }
};
// @lc code=end

