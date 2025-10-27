/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (43.04%)
 * Likes:    28598
 * Dislikes: 1729
 * Total Accepted:    3.8M
 * Total Submissions: 8.8M
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * There is an integer array nums sorted in ascending order (with distinct
 * values).
 * 
 * Prior to being passed to your function, nums is possibly left rotated at an
 * unknown index k (1 <= k < nums.length) such that the resulting array is
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]
 * (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices
 * and become [4,5,6,7,0,1,2].
 * 
 * Given the array nums after the possible rotation and an integer target,
 * return the index of target if it is in nums, or -1 if it is not in nums.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5000
 * -10^4 <= nums[i] <= 10^4
 * All values of nums are unique.
 * nums is an ascending array that is possibly rotated.
 * -10^4 <= target <= 10^4
 * 
 * 
 */
#include <vector>
using namespace std; 
// @lc code=start
class Solution {
public:
    int search1(vector<int>& nums, int target) {
        int L = -1, R = nums.size() - 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (nums[mid] > nums.back() ? L : R) = mid;
        }
        int l = 0 ,r = nums.size() - 1;
        if (target > nums.back()) {
            r = R - 1;
        } else {
            l = R;
        }
        auto ans = lower_bound(nums.begin() + l, nums.begin() + r + 1, target);
        return (*ans != target) ? -1 : ans - nums.begin();
    }

    int search2(vector<int>& nums, int target) {
        int L = -1, R = nums.size() - 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            int x = nums[mid];
            if (x > nums.back() && target <= nums.back()) {
                L = mid;
            } else if (x < nums.back() && target > nums.back()) {
                R = mid;
            } else if (x >= target) {
                R = mid;
            } else {
                L = mid;
            }
        }
        return nums[R] == target ? R : -1;
    }

    int search(vector<int>& nums, int target) {
        auto check = [&](int i) -> bool {
            int x = nums[i];
            if (x > nums.back()) {
                return target > nums.back() && target <= x;
            }
            return target > nums.back() || target <= x;
        };

        int L = -1, R = nums.size() - 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? R : L) = mid;
        }
        return nums[R] == target ? R : -1;
    }
};
// @lc code=end

