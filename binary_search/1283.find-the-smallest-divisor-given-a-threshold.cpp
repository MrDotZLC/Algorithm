/*
 * @lc app=leetcode id=1283 lang=cpp
 *
 * [1283] Find the Smallest Divisor Given a Threshold
 *
 * https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/
 *
 * algorithms
 * Medium (64.04%)
 * Likes:    3334
 * Dislikes: 220
 * Total Accepted:    346.2K
 * Total Submissions: 538.8K
 * Testcase Example:  '[1,2,5,9]\n6'
 *
 * Given an array of integers nums and an integer threshold, we will choose a
 * positive integer divisor, divide all the array by it, and sum the division's
 * result. Find the smallest divisor such that the result mentioned above is
 * less than or equal to threshold.
 * 
 * Each result of the division is rounded to the nearest integer greater than
 * or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).
 * 
 * The test cases are generated so that there will be an answer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,5,9], threshold = 6
 * Output: 5
 * Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
 * If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5
 * the sum will be 5 (1+1+1+2). 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [44,22,33,11,1], threshold = 5
 * Output: 44
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^4
 * 1 <= nums[i] <= 10^6
 * nums.length <= threshold <= 10^6
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        auto divisor_sum = [&](int mid) -> bool {
            long sum = 0L; 
            for(int i : nums) {
                sum += (i + mid - 1) / mid;
                if (sum > threshold) {
                    return true;
                }
            }
            return sum > threshold;
        };

        int L = 0, R = *max_element(nums.begin(), nums.end());
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            if (divisor_sum(mid)) {
                L = mid;
            } else {
                R = mid;
            }
        }
        return R;
    }
};
// @lc code=end

