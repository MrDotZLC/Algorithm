/*
 * @lc app=leetcode id=300 lang=cpp
 *
 * [300] Longest Increasing Subsequence
 *
 * https://leetcode.com/problems/longest-increasing-subsequence/description/
 *
 * algorithms
 * Medium (58.05%)
 * Likes:    22336
 * Dislikes: 495
 * Total Accepted:    2.4M
 * Total Submissions: 4.1M
 * Testcase Example:  '[10,9,2,5,3,7,101,18]'
 *
 * Given an integer array nums, return the length of the longest strictly
 * increasing subsequence.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore
 * the length is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,0,3,2,3]
 * Output: 4
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [7,7,7,7,7,7,7]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2500
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 * 
 * Follow up: Can you come up with an algorithm that runs in O(n log(n)) time
 * complexity?
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 递归+记忆化搜索
    int lengthOfLIS1(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> memo(n, -1);
        auto dfs = [&](auto &dfs, int i) -> int {
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    res = max(res, dfs(dfs, j));
                }
            }
            return ++res;
        };
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(dfs, i));
        }
        return ans;
    }
    
    // DP递推
    int lengthOfLIS2(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> f(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    f[i] = max(f[i], f[j]);
                }
            }
            ans = max(ans, ++f[i]);
        }
        return ans;
    }

    // 贪心
    int lengthOfLIS3(vector<int>& nums) {
        int n = nums.size();
        vector<int> g;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = ranges::lower_bound(g, x);
            if (it == g.end()) {
                g.push_back(x);
            } else {
                *it = x;
            }
        }
        return g.size();
    }

    // 贪心+原地修改
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), end = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = lower_bound(nums.begin(), nums.begin() + end, x);
            if (it - nums.begin() == end) {
                nums[end++] = x;
            } else {
                *it = x;
            }
        }
        return end;
    }
};
// @lc code=end

