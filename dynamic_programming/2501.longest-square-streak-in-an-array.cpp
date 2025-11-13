/*
 * @lc app=leetcode id=2501 lang=cpp
 *
 * [2501] Longest Square Streak in an Array
 *
 * https://leetcode.com/problems/longest-square-streak-in-an-array/description/
 *
 * algorithms
 * Medium (53.07%)
 * Likes:    1006
 * Dislikes: 33
 * Total Accepted:    154.3K
 * Total Submissions: 290.6K
 * Testcase Example:  '[4,3,6,16,8,2]'
 *
 * You are given an integer array nums. A subsequence of nums is called a
 * square streak if:
 * 
 * 
 * The length of the subsequence is at least 2, and
 * after sorting the subsequence, each element (except the first element) is
 * the square of the previous number.
 * 
 * 
 * Return the length of the longest square streak in nums, or return -1 if
 * there is no square streak.
 * 
 * A subsequence is an array that can be derived from another array by deleting
 * some or no elements without changing the order of the remaining elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,3,6,16,8,2]
 * Output: 3
 * Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes
 * [2,4,16].
 * - 4 = 2 * 2.
 * - 16 = 4 * 4.
 * Therefore, [4,16,2] is a square streak.
 * It can be shown that every subsequence of length 4 is not a square streak.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,3,5,6,7]
 * Output: -1
 * Explanation: There is no square streak in nums so return -1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 10^5
 * 2 <= nums[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化搜索
    int longestSquareStreak1(vector<int>& nums) {
        int mx = ranges::max(nums);
        unordered_set<long long> set(nums.begin(), nums.end());
        vector<int> memo(mx + 1);
        auto dfs = [&](auto &dfs, long long x) -> int {
            if (!set.contains(x)) {
                return 0;
            }
            int &res = memo[x];
            if (res) {
                return res;
            }
            return res = dfs(dfs, x * x) + 1;
        };
        int ans = 0;
        for (int x : nums) {
            ans = max(ans, dfs(dfs, x));
        }
        return ans < 2 ? -1 : ans;
    }

    // DP
    int longestSquareStreak(vector<int>& nums) {
        int mx = ranges::max(nums);
        vector<int> f(mx + 1);
        for (int x : nums) {
            f[x] = 1;
        }
        int ans = 0;

        for (int i = 2; i <= mx; i++) {
            int square = i * i;
            if ((long long) i * i > mx) {
                break;
            }
            if (f[i] == 0 || f[square] == 0) {
                continue;
            }
            f[square] = max(f[square], f[i] + 1);
            ans = max(ans, f[square]);
        }
        return ans < 2 ? -1 : ans;
    }
};
// @lc code=end

