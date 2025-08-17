/*
 * @lc app=leetcode id=2560 lang=cpp
 *
 * [2560] House Robber IV
 *
 * https://leetcode.com/problems/house-robber-iv/description/
 *
 * algorithms
 * Medium (65.12%)
 * Likes:    1649
 * Dislikes: 95
 * Total Accepted:    132.5K
 * Total Submissions: 203.6K
 * Testcase Example:  '[2,3,5,9]\n2'
 *
 * There are several consecutive houses along a street, each of which has some
 * money inside. There is also a robber, who wants to steal money from the
 * homes, but he refuses to steal from adjacent homes.
 * 
 * The capability of the robber is the maximum amount of money he steals from
 * one house of all the houses he robbed.
 * 
 * You are given an integer array nums representing how much money is stashed
 * in each house. More formally, the i^th house from the left has nums[i]
 * dollars.
 * 
 * You are also given an integer k, representing the minimum number of houses
 * the robber will steal from. It is always possible to steal at least k
 * houses.
 * 
 * Return the minimum capability of the robber out of all the possible ways to
 * steal at least k houses.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,5,9], k = 2
 * Output: 5
 * Explanation: 
 * There are three ways to rob at least 2 houses:
 * - Rob the houses at indices 0 and 2. Capability is max(nums[0], nums[2]) =
 * 5.
 * - Rob the houses at indices 0 and 3. Capability is max(nums[0], nums[3]) =
 * 9.
 * - Rob the houses at indices 1 and 3. Capability is max(nums[1], nums[3]) =
 * 9.
 * Therefore, we return min(5, 9, 9) = 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,7,9,3,1], k = 2
 * Output: 2
 * Explanation: There are 7 ways to rob the houses. The way which leads to
 * minimum capability is to rob the house at index 0 and 4. Return max(nums[0],
 * nums[4]) = 2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= (nums.length + 1)/2
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int L = 0, R = *max_element(nums.begin(), nums.end());
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(nums, k, mid) ? L : R) = mid;
        }
        return R;
    }

    // greedy
    bool check1(vector<int>& nums, int k, int target) {
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= target) {
                cnt++;
                i++;
            }
            if (cnt < k) {
                return true;
            }
        }
        return false;
    }

    // dp: fi = max(fi-1, fi-2 + 1)
    bool check(vector<int>& nums, int k, int target) {
        int f0 = 0, f1 = 0;
        for (int x : nums) {
            if (x > target) {
                f0 = f1;
            } else {
                int temp = f1;
                f1 = max(f1, f0 + 1);
                f0 = temp;
            }
        }
        return f1 < k;
    }
};
// @lc code=end

