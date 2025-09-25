/*
 * @lc app=leetcode id=1755 lang=cpp
 *
 * [1755] Closest Subsequence Sum
 *
 * https://leetcode.com/problems/closest-subsequence-sum/description/
 *
 * algorithms
 * Hard (41.95%)
 * Likes:    984
 * Dislikes: 72
 * Total Accepted:    25.1K
 * Total Submissions: 59.3K
 * Testcase Example:  '[5,-7,3,5]\n6'
 *
 * You are given an integer array nums and an integer goal.
 * 
 * You want to choose a subsequence of nums such that the sum of its elements
 * is the closest possible to goal. That is, if the sum of the subsequence's
 * elements is sum, then you want to minimize the absolute difference abs(sum -
 * goal).
 * 
 * Return the minimum possible value of abs(sum - goal).
 * 
 * Note that a subsequence of an array is an array formed by removing some
 * elements (possibly all or none) of the original array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,-7,3,5], goal = 6
 * Output: 0
 * Explanation: Choose the whole array as a subsequence, with a sum of 6.
 * This is equal to the goal, so the absolute difference is 0.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [7,-9,15,-2], goal = -5
 * Output: 1
 * Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
 * The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the
 * minimum.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3], goal = -7
 * Output: 7
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 40
 * -10^7 <= nums[i] <= 10^7
 * -10^9 <= goal <= 10^9
 * 
 * 
 */
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        set<int> set;
        function<void(int, int)> dfs1 = [&](int i, int sum) {
            if (i >= n / 2) {
                set.insert(sum - goal);
                return;
            }

            dfs1(i + 1, sum);
            dfs1(i + 1, sum + nums[i]);
        };
        dfs1(0, 0);

        int ans = INT_MAX;
        function<void(int, int)> dfs2 = [&](int i, int sum) {
            if (i >= n) {
                auto it = set.lower_bound(-sum);
                if (it != set.end()) {
                    ans = min(ans, abs(*it + sum));
                }
                if (it != set.begin()) {
                    it = prev(it);
                    ans = min(ans, abs(*it + sum));
                }
                return;
            }
            dfs2(i + 1, sum);
            dfs2(i + 1, sum + nums[i]);
        };
        dfs2(n / 2, 0);
        return ans;
    }
};
// @lc code=end

