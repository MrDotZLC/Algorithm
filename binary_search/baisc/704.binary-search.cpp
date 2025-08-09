/*
 * @lc app=leetcode id=704 lang=cpp
 *
 * [704] Binary Search
 *
 * https://leetcode.com/problems/binary-search/description/
 *
 * algorithms
 * Easy (59.72%)
 * Likes:    12788
 * Dislikes: 282
 * Total Accepted:    3.3M
 * Total Submissions: 5.6M
 * Testcase Example:  '[-1,0,3,5,9,12]\n9'
 *
 * Given an array of integers nums which is sorted in ascending order, and an
 * integer target, write a function to search target in nums. If target exists,
 * then return its index. Otherwise, return -1.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^4
 * -10^4 < nums[i], target < 10^4
 * All the integers in nums are unique.
 * nums is sorted in ascending order.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int search = lower_bound(nums, target);
        if (search == nums.size() || nums[search] != target) {
            return -1;
        }
        return search;
    }

    int lower_bound(vector<int>& nums, int target) {
        int L = -1, R = nums.size();
        while (L + 1 < R) { // LR不可以重合，会越界
            int mid = L + (R - L) / 2; // 防溢出
            if (nums[mid] < target) {
                L = mid;
            } else {
                R = mid;
            }
        }
        return R; // L + 1 = R
    }
};
// @lc code=end

