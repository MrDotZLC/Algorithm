/*
 * @lc app=leetcode id=560 lang=cpp
 *
 * [560] Subarray Sum Equals K
 *
 * https://leetcode.com/problems/subarray-sum-equals-k/description/
 *
 * algorithms
 * Medium (45.69%)
 * Likes:    24001
 * Dislikes: 792
 * Total Accepted:    2M
 * Total Submissions: 4.4M
 * Testcase Example:  '[1,1,1]\n2'
 *
 * Given an array of integers nums and an integer k, return the total number of
 * subarrays whose sum equals to k.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 * Example 2:
 * Input: nums = [1,2,3], k = 3
 * Output: 2
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * -1000 <= nums[i] <= 1000
 * -10^7 <= k <= 10^7
 * 
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0, sum = 0;
        unordered_map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++) {
            cnt[sum]++;
            sum += nums[i];
            ans += cnt[sum - k]; // sum-t = k, t = sum-k
        }
        return ans;
    }
};
// @lc code=end

