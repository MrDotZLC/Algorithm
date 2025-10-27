/*
 * @lc app=leetcode id=2563 lang=cpp
 *
 * [2563] Count the Number of Fair Pairs
 *
 * https://leetcode.com/problems/count-the-number-of-fair-pairs/description/
 *
 * algorithms
 * Medium (52.88%)
 * Likes:    1974
 * Dislikes: 147
 * Total Accepted:    229.3K
 * Total Submissions: 433.8K
 * Testcase Example:  '[0,1,7,4,4,5]\n3\n6'
 *
 * Given a 0-indexed integer array nums of size n and two integers lower and
 * upper, return the number of fair pairs.
 * 
 * A pair (i, j) is fair if:
 * 
 * 
 * 0 <= i < j < n, and
 * lower <= nums[i] + nums[j] <= upper
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
 * Output: 6
 * Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and
 * (1,5).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,7,9,2,5], lower = 11, upper = 11
 * Output: 1
 * Explanation: There is a single fair pair: (2,3).
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums.length == n
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= lower <= upper <= 10^9
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // sort + loop
    long long countFairPairs1(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long ans = 0LL;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] >= lower && nums[i] + nums[j] <= upper) {
                    ans++;
                }
                if (nums[i] + nums[j] > upper) {
                    break;
                }
            }
        }
        return ans;
    }

    // sort + binary
    long long countFairPairs2(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long ans = 0LL;
        for (int j = 0; j < nums.size(); j++) {
            auto l = lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
            auto r = upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            ans += r - l;
        }
        return ans;
    }

    // triple pointer
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long ans = 0LL;
        int l = nums.size(), r = l;
        for (int j = 0; j < nums.size(); j++) {
            while (r && nums[r - 1] > upper - nums[j]) {
                r--;
            }
            while (l && nums[l - 1] >= lower - nums[j]) {
                l--;
            }
            ans += min(r, j) - min(l, j);
        }
        return ans;
    }
};
// @lc code=end

