/*
 * @lc app=leetcode id=2597 lang=cpp
 *
 * [2597] The Number of Beautiful Subsets
 *
 * https://leetcode.com/problems/the-number-of-beautiful-subsets/description/
 *
 * algorithms
 * Medium (50.81%)
 * Likes:    1287
 * Dislikes: 176
 * Total Accepted:    127.4K
 * Total Submissions: 250.6K
 * Testcase Example:  '[2,4,6]\n2'
 *
 * You are given an array nums of positive integers and a positive integer k.
 * 
 * A subset of nums is beautiful if it does not contain two integers with an
 * absolute difference equal to k.
 * 
 * Return the number of non-empty beautiful subsets of the array nums.
 * 
 * A subset of nums is an array that can be obtained by deleting some (possibly
 * none) elements from nums. Two subsets are different if and only if the
 * chosen indices to delete are different.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,4,6], k = 2
 * Output: 4
 * Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2,
 * 6].
 * It can be proved that there are only 4 beautiful subsets in the array
 * [2,4,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1], k = 1
 * Output: 1
 * Explanation: The beautiful subset of the array nums is [1].
 * It can be proved that there is only 1 beautiful subset in the array [1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 18
 * 1 <= nums[i], k <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // backtracking
    int beautifulSubsets1(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        vector<int> path;
        function<void(int)> dfs = [&](int i) -> void {
            if (i == n) {
                if (!path.empty()) {
                    ans++;
                }
                return;
            }
            dfs(i + 1);
            auto f1 = ranges::find(path, nums[i] + k);
            auto f2 = ranges::find(path, nums[i] - k);
            if (f1 == path.end() && f2 == path.end()) {
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return ans;
    }

    // dp
    int beautifulSubsets(vector<int>& nums, int k) {
        unordered_map<int, map<int, int>> g;
        for (int i : nums) {
            g[i % k][i]++;
        }

        int ans = 1;
        for (auto &[_, cnt] : g) {
            auto it = cnt.begin();
            int f0 = 1, f1 = 1 << it->second;
            for (it++; it != cnt.end(); ++it) {
                auto &[x, c] = *it;
                // diff == k, f(i+1) = f(i) + f(i-1)*(2^c-1)
                // diff != k, f(i+1) = f(i) * 2^c
                int new_f = x - prev(it)->first == k
                                ? f1 + f0 * ((1 << c) - 1)
                                : f1 << c;
                f0 = f1;
                f1 = new_f;
            }
            ans *= f1;
        }
        return ans - 1;
    }
};
// @lc code=end

