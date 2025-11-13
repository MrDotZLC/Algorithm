/*
 * @lc app=leetcode id=1027 lang=cpp
 *
 * [1027] Longest Arithmetic Subsequence
 *
 * https://leetcode.com/problems/longest-arithmetic-subsequence/description/
 *
 * algorithms
 * Medium (49.55%)
 * Likes:    4868
 * Dislikes: 218
 * Total Accepted:    205.2K
 * Total Submissions: 413K
 * Testcase Example:  '[3,6,9,12]'
 *
 * Given an array nums of integers, return the length of the longest arithmetic
 * subsequence in nums.
 * 
 * Note that:
 * 
 * 
 * A subsequence is an array that can be derived from another array by deleting
 * some or no elements without changing the order of the remaining
 * elements.
 * A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value
 * (for 0 <= i < seq.length - 1).
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,6,9,12]
 * Output: 4
 * Explanation:  The whole array is an arithmetic sequence with steps of length
 * = 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [9,4,7,2,10]
 * Output: 3
 * Explanation:  The longest arithmetic subsequence is [4,7,10].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [20,1,15,3,10,5,8]
 * Output: 4
 * Explanation:  The longest arithmetic subsequence is [20,15,10,5].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 1000
 * 0 <= nums[i] <= 500
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 枚举元素：记忆化搜索
    int longestArithSeqLength1(vector<int>& nums) {
        int ans = 0, n = nums.size();
        unordered_map<int, int> max_len[n];
        auto dfs = [&](this auto &&dfs, int i) -> void {
            if (!max_len[i].empty()) {
                return ;
            }
            for (int j = i - 1; j >= 0; j--) {
                int d = nums[i] - nums[j];
                if (!max_len[i].count(d)) {
                    dfs(j);
                    auto it = max_len[j].find(d);
                    max_len[i][d] = it == max_len[j].end() ? 2 : it->second + 1;
                    ans = max(ans, max_len[i][d]);
                }
            }
        };
        for (int i = 0; i < n; i++) {
            dfs(i);
        }
        return ans;
    }

    // 枚举元素：DP
    int longestArithSeqLength2(vector<int>& nums) {
        int ans = 0, n = nums.size();
        unordered_map<int, int> f[n];
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                int d = nums[i] - nums[j];
                if (!f[i].count(d)) {
                    auto it = f[j].find(d);
                    f[i][d] = it == f[j].end() ? 2 : it->second + 1;
                    ans = max(ans, f[i][d]);
                }
            }
        }
        return ans;
    }

    // 枚举元素：DP + 常数优化
    int longestArithSeqLength3(vector<int>& nums) {
        int ans = 0, n = nums.size();
        auto [mn, mx] = minmax_element(nums.begin(), nums.end());
        int m = mx - mn;
        vector f(n, vector<int>(m + 1));
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                int d = nums[i] - nums[j] + m;
                if (f[i][d] == 0) {
                    f[i][d] = f[j][d] + 1;
                    ans = max(ans, f[i][d]);
                }
            }
        }
        return ans + 1;
    }

    // 枚举公差：DP
    int longestArithSeqLength(vector<int>& nums) {
        int ans = 0;
        int m = ranges::max(nums);
        for (int d = -m; d <= m; d++) {
            vector<int> f(m + 1);
            for (int x : nums) {
                f[x] = 0 <= x - d && x - d <= m ? f[x - d] + 1 : 1;
                ans = max(ans, f[x]);
            }
        }
        return ans;
    }
};
// @lc code=end

