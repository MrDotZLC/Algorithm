/*
 * @lc app=leetcode id=2334 lang=cpp
 *
 * [2334] Subarray With Elements Greater Than Varying Threshold
 *
 * https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/description/
 *
 * algorithms
 * Hard (44.63%)
 * Likes:    604
 * Dislikes: 11
 * Total Accepted:    16.8K
 * Total Submissions: 37.5K
 * Testcase Example:  '[1,3,4,3,1]\n6'
 *
 * You are given an integer array nums and an integer threshold.
 * 
 * Find any subarray of nums of length k such that every element in the
 * subarray is greater than threshold / k.
 * 
 * Return the size of any such subarray. If there is no such subarray, return
 * -1.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,4,3,1], threshold = 6
 * Output: 3
 * Explanation: The subarray [3,4,3] has a size of 3, and every element is
 * greater than 6 / 3 = 2.
 * Note that this is the only valid subarray.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [6,5,6,5,8], threshold = 7
 * Output: 1
 * Explanation: The subarray [8] has a size of 1, and 8 > 7 / 1 = 7. So 1 is
 * returned.
 * Note that the subarray [6,5] has a size of 2, and every element is greater
 * than 7 / 2 = 3.5. 
 * Similarly, the subarrays [6,5,6], [6,5,6,5], [6,5,6,5,8] also satisfy the
 * given conditions.
 * Therefore, 2, 3, 4, or 5 may also be returned.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i], threshold <= 10^9
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        nums.push_back(-1);
        int n = nums.size();
        vector<int> stk = {-1};

        // 枚举范围内最小值nums[i]，找到左右更小值作为开区间范围，即栈中弹出大于右值的下标i
        // 栈中下个值即左值，右-左-1=k
        for (int r = 0; r < n; r++) {
            while (stk.size() > 1 && nums[stk.back()] > nums[r]) { // 右侧最大值
                int i = stk.back();
                stk.pop_back();
                int k = r - stk.back() - 1;
                if (k * nums[i] > threshold) {
                    return k;
                }
            }
            stk.push_back(r);
        }
        return -1;
    }
};
// @lc code=end

