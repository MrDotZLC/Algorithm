/*
 * @lc app=leetcode id=3427 lang=cpp
 *
 * [3427] Sum of Variable Length Subarrays
 *
 * https://leetcode.com/problems/sum-of-variable-length-subarrays/description/
 *
 * algorithms
 * Easy (85.19%)
 * Likes:    88
 * Dislikes: 26
 * Total Accepted:    48.7K
 * Total Submissions: 57.2K
 * Testcase Example:  '[2,3,1]'
 *
 * You are given an integer array nums of size n. For each index i where 0 <= i
 * < n, define a subarray nums[start ... i] where start = max(0, i - nums[i]).
 * 
 * Return the total sum of all elements from the subarray defined for each
 * index in the array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,1]
 * 
 * Output: 11
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * i
 * Subarray
 * Sum
 * 
 * 
 * 0
 * nums[0] = [2]
 * 2
 * 
 * 
 * 1
 * nums[0 ... 1] = [2, 3]
 * 5
 * 
 * 
 * 2
 * nums[1 ... 2] = [3, 1]
 * 4
 * 
 * 
 * Total Sum
 * 
 * 11
 * 
 * 
 * 
 * 
 * The total sum is 11. Hence, 11 is the output.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,1,1,2]
 * 
 * Output: 13
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * i
 * Subarray
 * Sum
 * 
 * 
 * 0
 * nums[0] = [3]
 * 3
 * 
 * 
 * 1
 * nums[0 ... 1] = [3, 1]
 * 4
 * 
 * 
 * 2
 * nums[1 ... 2] = [1, 1]
 * 2
 * 
 * 
 * 3
 * nums[1 ... 3] = [1, 1, 2]
 * 4
 * 
 * 
 * Total Sum
 * 
 * 13
 * 
 * 
 * 
 * 
 * The total sum is 13. Hence, 13 is the output.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n == nums.length <= 100
 * 1 <= nums[i] <= 1000
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // presum
    int subarraySum1(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(n + 1);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + nums[i];
            ans += s[i + 1] - s[max(i - nums[i], 0)];
        }
        return ans;
    }

    // diff
    int subarraySum(vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n + 1);
        int ans = 0, sd = 0; // 元素i被使用的次数
        for (int i = 0; i < n; i++) {
            diff[max(i - nums[i], 0)]++;
            diff[i + 1]--;
        }
        for (int i = 0; i < n; i++) {
            sd += diff[i];
            ans += sd * nums[i];
        }
        return ans;
    }
};
// @lc code=end

