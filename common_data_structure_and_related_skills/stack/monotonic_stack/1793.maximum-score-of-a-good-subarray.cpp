/*
 * @lc app=leetcode id=1793 lang=cpp
 *
 * [1793] Maximum Score of a Good Subarray
 *
 * https://leetcode.com/problems/maximum-score-of-a-good-subarray/description/
 *
 * algorithms
 * Hard (64.27%)
 * Likes:    1947
 * Dislikes: 50
 * Total Accepted:    84K
 * Total Submissions: 130.6K
 * Testcase Example:  '[1,4,3,7,4,5]\n3'
 *
 * You are given an array of integers nums (0-indexed) and an integer k.
 * 
 * The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ...,
 * nums[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j.
 * 
 * Return the maximum possible score of a good subarray.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,4,3,7,4,5], k = 3
 * Output: 15
 * Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) *
 * (5-1+1) = 3 * 5 = 15. 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,5,4,5,4,1,1,1], k = 0
 * Output: 20
 * Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) *
 * (4-0+1) = 4 * 5 = 20.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 2 * 10^4
 * 0 <= k < nums.length
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // double pointer
    int maximumScore1(vector<int>& nums, int k) {
        int ans = nums[k], l = k, r = k, n = nums.size(), min_h = nums[k];

        for (int i = 0; i < n - 1; i++) {
            if (r == n - 1 || l && nums[l - 1] > nums[r + 1]) {
                min_h = min(min_h, nums[--l]);
            } else {
                min_h = min(min_h, nums[++r]);
            }
            ans = max(ans, min_h * (r - l + 1));
        }
        return ans;
    }

    // monotonic stack
    int maximumScore(vector<int>& nums, int k) {
        nums.push_back(-1);
        int n = nums.size();
        // i右侧小于等于height[i]，哪怕有重复元素，
        // 其中一个元素一定不会算漏，如此就能一次循环得到左右两边的最小下标
        // 如：13531，第一个3会算漏得3*2，第二个则不会得3*3
        vector<int> stk;
        stk.push_back(-1);
        int ans = nums[k];

        for (int r = 0; r < n; r++) {
            int h = nums[r];
            while (stk.size() > 1 && h <= nums[stk.back()]) {
                int i = stk.back(); // 矩形高
                stk.pop_back();
                int l = stk.back();
                if (l < k && k < r) {
                    ans = max(ans, nums[i] * (r - l - 1)); // 宽度为r-1-(l+1)+1=r-l-1;
                }
            }
            stk.push_back(r);
        }

        return ans;
    }
};
// @lc code=end

