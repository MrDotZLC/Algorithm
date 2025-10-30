/*
 * @lc app=leetcode id=494 lang=cpp
 *
 * [494] Target Sum
 *
 * https://leetcode.com/problems/target-sum/description/
 *
 * algorithms
 * Medium (50.96%)
 * Likes:    12084
 * Dislikes: 406
 * Total Accepted:    969.6K
 * Total Submissions: 1.9M
 * Testcase Example:  '[1,1,1,1,1]\n3'
 *
 * You are given an integer array nums and an integer target.
 * 
 * You want to build an expression out of nums by adding one of the symbols '+'
 * and '-' before each integer in nums and then concatenate all the
 * integers.
 * 
 * 
 * For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1
 * and concatenate them to build the expression "+2-1".
 * 
 * 
 * Return the number of different expressions that you can build, which
 * evaluates to target.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,1,1,1], target = 3
 * Output: 5
 * Explanation: There are 5 ways to assign symbols to make the sum of nums be
 * target 3.
 * -1 + 1 + 1 + 1 + 1 = 3
 * +1 - 1 + 1 + 1 + 1 = 3
 * +1 + 1 - 1 + 1 + 1 = 3
 * +1 + 1 + 1 - 1 + 1 = 3
 * +1 + 1 + 1 + 1 - 1 = 3
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1], target = 1
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 20
 * 0 <= nums[i] <= 1000
 * 0 <= sum(nums[i]) <= 1000
 * -1000 <= target <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    // half enum折半枚举
    int findTargetSumWays1(vector<int>& nums, int target) {
        int s = reduce(nums.begin(), nums.end()) - abs(target);
        if (s < 0 || s % 2) {
            return 0;
        }

        int m = s / 2;
        int k = nums.size() / 2;

        auto cnt1 = sub_set({nums.begin(), nums.begin() + k});
        auto cnt2 = sub_set({nums.begin() + k, nums.end()});

        int ans = 0;
        for (auto &[x, c1] : cnt1) {
            ans += c1 * cnt2[m - x];
        }
        return ans;
    }

    // 78. 子集（二进制枚举）
    unordered_map<int, int> sub_set(const vector<int> &nums) {
        unordered_map<int, int> cnt;
        int n = nums.size();
        for (int i = 0; i < (1 << n); i++) {
            int s = 0;
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    s += nums[j];
                }
            }
            cnt[s]++;
        }
        return cnt;
    }

    // dp递推+空间优化
    int findTargetSumWays2(vector<int>& nums, int target) {
        int s = reduce(nums.begin(), nums.end()) - abs(target);
        if (s < 0 || s % 2) {
            return 0;
        }

        int m = s / 2;
        vector<int> f(m + 1);
        f[0] = 1;
        for (int x : nums) {
            for (int c = m; c >= x; c--) { // 从大到小才不会重复计算
                f[c] += f[c - x];
            }
        }        
        return f[m];
    }

    // dp递推+空间优化+剪枝
    int findTargetSumWays(vector<int>& nums, int target) {
        int s = reduce(nums.begin(), nums.end()) - abs(target);
        if (s < 0 || s % 2) {
            return 0;
        }

        s /= 2;
        vector<int> f(s + 1);
        f[0] = 1;
        int s2 = 0;
        for (int x : nums) {
            s2 = min(s2 + x, s);
            for (int c = s2; c >= x; c--) { // 从大到小才不会重复计算
                f[c] += f[c - x];
            }
        }        
        return f[s];
    }
};
// @lc code=end

