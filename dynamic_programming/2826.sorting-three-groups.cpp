/*
 * @lc app=leetcode id=2826 lang=cpp
 *
 * [2826] Sorting Three Groups
 *
 * https://leetcode.com/problems/sorting-three-groups/description/
 *
 * algorithms
 * Medium (41.97%)
 * Likes:    520
 * Dislikes: 91
 * Total Accepted:    24.9K
 * Total Submissions: 58.6K
 * Testcase Example:  '[2,1,3,2,1]'
 *
 * You are given an integer array nums. Each element in nums is 1, 2 or 3. In
 * each operation, you can remove an element from nums. Return the minimum
 * number of operations to make nums non-decreasing.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,1,3,2,1]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * One of the optimal solutions is to remove nums[0], nums[2] and nums[3].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,3,2,1,3,3]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * One of the optimal solutions is to remove nums[1] and nums[2].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,2,2,2,3,3]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * nums is already non-decreasing.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 3
 * 
 * 
 * 
 * Follow-up: Can you come up with an algorithm that runs in O(n) time
 * complexity?
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 总长度 - 最长非递减序列长度

    // 递归记忆化搜索
    int minimumOperations1(vector<int>& nums) {
        int n = nums.size();
        vector<int> memo(n, -1);
        auto dfs = [&](auto &dfs, int i) -> int {
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] <= nums[i]) {
                    res = max(res, dfs(dfs, j));
                }
            }
            return ++res;
        };
        int ans = 0;
        for (int j = 0; j < n; j++) {
            ans = max(ans, dfs(dfs, j));
        }
        return n - ans;
    }

    // DP递推
    int minimumOperations2(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> f(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] <= nums[i]) {
                    f[i] = max(f[i], f[j]);
                }
            }
            ans = max(ans, ++f[i]);
        }
        return n - ans;
    }

    // 贪心+二分
    int minimumOperations3(vector<int>& nums) {
        int n = nums.size();
        vector<int> g;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = ranges::upper_bound(g, x);
            if (it == g.end()) {
                g.push_back(x);
            } else {
                *it = x;
            }
        }
        return n - g.size();
    }
    
    // 贪心+二分
    int minimumOperations(vector<int>& nums) {
        int n = nums.size(), end = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = upper_bound(nums.begin(), nums.begin() + end, x);
            if (it - nums.begin() == end) {
                nums[end++] = x;
            } else {
                *it = x;
            }
        }
        return n - end;
    }
};
// @lc code=end

