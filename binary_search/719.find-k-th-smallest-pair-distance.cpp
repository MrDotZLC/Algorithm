/*
 * @lc app=leetcode id=719 lang=cpp
 *
 * [719] Find K-th Smallest Pair Distance
 *
 * https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
 *
 * algorithms
 * Hard (45.87%)
 * Likes:    3859
 * Dislikes: 123
 * Total Accepted:    201.1K
 * Total Submissions: 437.9K
 * Testcase Example:  '[1,3,1]\n1'
 *
 * The distance of a pair of integers a and b is defined as the absolute
 * difference between a and b.
 * 
 * Given an integer array nums and an integer k, return the k^th smallest
 * distance among all the pairs nums[i] and nums[j] where 0 <= i < j <
 * nums.length.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,1], k = 1
 * Output: 0
 * Explanation: Here are all the pairs:
 * (1,3) -> 2
 * (1,1) -> 0
 * (3,1) -> 2
 * Then the 1^st smallest distance pair is (1,1), and its distance is 0.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,1], k = 2
 * Output: 0
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,6,1], k = 3
 * Output: 5
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 2 <= n <= 10^4
 * 0 <= nums[i] <= 10^6
 * 1 <= k <= n * (n - 1) / 2
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        ranges::sort(nums);
        auto check = [&](int t) -> bool {
            int cnt = 0, i = 0;
            for (int j = 0; j < nums.size(); j++) {
                while (nums[j] - nums[i] > t) {
                    i++;
                }
                cnt += j - i;
            }
            return cnt < k;
        };

        int L = -1;
        int R = nums.back() - nums[0];
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid; 
        }
        return R;
    }
};
// @lc code=end

