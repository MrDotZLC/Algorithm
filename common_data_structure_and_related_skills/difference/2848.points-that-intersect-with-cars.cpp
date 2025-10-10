/*
 * @lc app=leetcode id=2848 lang=cpp
 *
 * [2848] Points That Intersect With Cars
 *
 * https://leetcode.com/problems/points-that-intersect-with-cars/description/
 *
 * algorithms
 * Easy (72.91%)
 * Likes:    355
 * Dislikes: 34
 * Total Accepted:    68.9K
 * Total Submissions: 94.2K
 * Testcase Example:  '[[3,6],[1,5],[4,7]]'
 *
 * You are given a 0-indexed 2D integer array nums representing the coordinates
 * of the cars parking on a number line. For any index i, nums[i] = [starti,
 * endi] where starti is the starting point of the i^th car and endi is the
 * ending point of the i^th car.
 * 
 * Return the number of integer points on the line that are covered with any
 * part of a car.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [[3,6],[1,5],[4,7]]
 * Output: 7
 * Explanation: All the points from 1 to 7 intersect at least one car,
 * therefore the answer would be 7.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [[1,3],[5,8]]
 * Output: 7
 * Explanation: Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8.
 * There are a total of 7 points, therefore the answer would be 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * nums[i].length == 2
 * 1 <= starti <= endi <= 100
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int max_end = ranges::max(nums, {}, [](const auto &a) {
            return a[1];   
        })[1];
        // int max_end = (*max_element(nums.begin(), nums.end(), [](const vector<int> &a, const vector<int> &b) {
        //     return a[1] < b[1];
        // }))[1];
        vector<int> diff(max_end + 2);
        for (auto &interval : nums) {
            diff[interval[0]]++;
            diff[interval[1] + 1]--;
        }

        int ans = 0, sum = 0;
        for (int d : diff) {
            sum += d;
            ans += sum > 0;
        }
        return ans;
    }
};
// @lc code=end

