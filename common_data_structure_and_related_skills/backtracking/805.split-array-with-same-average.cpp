/*
 * @lc app=leetcode id=805 lang=cpp
 *
 * [805] Split Array With Same Average
 *
 * https://leetcode.com/problems/split-array-with-same-average/description/
 *
 * algorithms
 * Hard (26.10%)
 * Likes:    1325
 * Dislikes: 140
 * Total Accepted:    43.7K
 * Total Submissions: 166K
 * Testcase Example:  '[1,2,3,4,5,6,7,8]'
 *
 * You are given an integer array nums.
 * 
 * You should move each element of nums into one of the two arrays A and B such
 * that A and B are non-empty, and average(A) == average(B).
 * 
 * Return true if it is possible to achieve that and false otherwise.
 * 
 * Note that for an array arr, average(arr) is the sum of all the elements of
 * arr over the length of arr.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5,6,7,8]
 * Output: true
 * Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both
 * of them have an average of 4.5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,1]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 30
 * 0 <= nums[i] <= 10^4
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
    bool splitArraySameAverage(vector<int>& nums) {
        ranges::sort(nums);
        int total = reduce(nums.begin(), nums.end(), 0, plus());
        int n = nums.size();
        auto dfs = [&](auto &dfs, int i, int sum, int size, int k) -> bool {
            if (size == k) {
                return n * sum == size * total;
            }

            for (int j = i; j < n; j++) {
                if (j > i && nums[j] == nums[j - 1]) {
                    continue;
                }

                int target_sum = ((size + 1) * total) / n;
                if (sum + nums[j] > target_sum) { // 剪枝：子集和过大
                    continue;
                }

                if (dfs(dfs, j + 1, sum + nums[j], size + 1, k)) {
                    return true;
                }
            }
            return false;
        };
        for (int k = 1; k <= n/2; k++) {
            if ((total * k) % n != 0) continue;  // 不能整除，剪掉
            if (dfs(dfs, 0, 0, 0, k)) return true;
        }
        return false;
    }
};
// @lc code=end

