/*
 * @lc app=leetcode id=3371 lang=cpp
 *
 * [3371] Identify the Largest Outlier in an Array
 *
 * https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/description/
 *
 * algorithms
 * Medium (35.84%)
 * Likes:    210
 * Dislikes: 29
 * Total Accepted:    50K
 * Total Submissions: 138.9K
 * Testcase Example:  '[2,3,5,10]'
 *
 * You are given an integer array nums. This array contains n elements, where
 * exactly n - 2 elements are special numbers. One of the remaining two
 * elements is the sum of these special numbers, and the other is an outlier.
 * 
 * An outlier is defined as a number that is neither one of the original
 * special numbers nor the element representing the sum of those numbers.
 * 
 * Note that special numbers, the sum element, and the outlier must have
 * distinct indices, but may share the same value.
 * 
 * Return the largest potential outlier in nums.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,5,10]
 * 
 * Output: 10
 * 
 * Explanation:
 * 
 * The special numbers could be 2 and 3, thus making their sum 5 and the
 * outlier 10.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-2,-1,-3,-6,4]
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The special numbers could be -2, -1, and -3, thus making their sum -6 and
 * the outlier 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,1,1,1,1,5,5]
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * The special numbers could be 1, 1, 1, 1, and 1, thus making their sum 5 and
 * the other 5 as the outlier.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 10^5
 * -1000 <= nums[i] <= 1000
 * The input is generated such that at least one potential outlier exists in
 * nums.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        int ans = INT_MIN, n = nums.size(), total = 0;
        unordered_map<int, int> cnt;
        while (--n >= 0) {
            total += nums[n];
            cnt[nums[n]]++;
        }
        for (int i = 0; i < nums.size(); i++) {
            int double_sum = total - nums[i];
            if (double_sum % 2 != 0 || i > 0 && nums[i - 1] == nums[i]) {
                continue;
            }
            int t =  double_sum / 2;
            auto it = cnt.find(t);
            if (it != cnt.end() && (t != nums[i] || it->second > 1)) {
                ans = max(ans, nums[i]);
            }
        }
        return ans;
    }
};
// @lc code=end

