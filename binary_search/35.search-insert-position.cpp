/*
 * @lc app=leetcode id=35 lang=cpp
 *
 * [35] Search Insert Position
 *
 * https://leetcode.com/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (49.26%)
 * Likes:    17746
 * Dislikes: 844
 * Total Accepted:    4M
 * Total Submissions: 8.1M
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be if
 * it were inserted in order.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^4
 * -10^4 <= nums[i] <= 10^4
 * nums contains distinct values sorted in ascending order.
 * -10^4 <= target <= 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums, target);
    }

    int lower_bound(vector<int>& nums, int target) {
        int L = 0, R = nums.size();
        while (L < R) {
            int mid = L + (R - L) / 2;
            if (nums[mid] < target) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        return R;
    }
};
// @lc code=end

