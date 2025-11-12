/*
 * @lc app=leetcode id=2708 lang=cpp
 *
 * [2708] Maximum Strength of a Group
 *
 * https://leetcode.com/problems/maximum-strength-of-a-group/description/
 *
 * algorithms
 * Medium (24.88%)
 * Likes:    380
 * Dislikes: 65
 * Total Accepted:    36.1K
 * Total Submissions: 143.4K
 * Testcase Example:  '[3,-1,-5,2,5,-9]'
 *
 * You are given a 0-indexed integer array nums representing the score of
 * students in an exam. The teacher would like to form one non-empty group of
 * students with maximal strength, where the strength of a group of students of
 * indices i0, i1, i2, ... , ik is defined as nums[i0] * nums[i1] * nums[i2] *
 * ... * nums[ik​].
 * 
 * Return the maximum strength of a group the teacher can create.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,-1,-5,2,5,-9]
 * Output: 1350
 * Explanation: One way to form a group of maximal strength is to group the
 * students at indices [0,2,3,4,5]. Their strength is 3 * (-5) * 2 * 5 * (-9) =
 * 1350, which we can show is optimal.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-4,-5,-4]
 * Output: 20
 * Explanation: Group the students at indices [0, 1] . Then, we’ll have a
 * resulting strength of 20. We cannot achieve greater strength.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 13
 * -9 <= x <= 9
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // 二分
    long long maxStrength1(vector<int> &nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        ranges::sort(nums);
        auto it = ranges::lower_bound(nums, 0);
        int cnt = it - nums.begin();
        // cout << c_p << " " << prev(it) << " " << prev(prev(it))
        //      << endl;
        long long ans = reduce(nums.begin(), cnt % 2 ? prev(it) : it,
                               1LL, multiplies<long long>());
        cnt -= (cnt % 2);
        it = ranges::upper_bound(nums, 0);
        ans = reduce(it, nums.end(), ans, multiplies<long long>());
        return cnt + (nums.end() - it) == 0 ? 0 : ans;
    }

    // DP+空间优化
    long long maxStrength(vector<int> &nums) {
        int n = nums.size();
        long long f0 = nums[0], f1 = nums[0];
        for (int i = 1; i < n; i++) {
            long long x = nums[i];
            long long new_f0 = min({f0, x, f0 * x, f1 * x});
            f1 = max({f1, x, f0 * x, f1 * x});
            f0 = new_f0;
        }
        return f1;
    }
};
// @lc code=end

