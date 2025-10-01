/*
 * @lc app=leetcode id=1590 lang=cpp
 *
 * [1590] Make Sum Divisible by P
 *
 * https://leetcode.com/problems/make-sum-divisible-by-p/description/
 *
 * algorithms
 * Medium (39.47%)
 * Likes:    2440
 * Dislikes: 171
 * Total Accepted:    143.9K
 * Total Submissions: 365.1K
 * Testcase Example:  '[3,1,4,2]\n6'
 *
 * Given an array of positive integers nums, remove the smallest subarray
 * (possibly empty) such that the sum of the remaining elements is divisible by
 * p. It is not allowed to remove the whole array.
 * 
 * Return the length of the smallest subarray that you need to remove, or -1 if
 * it's impossible.
 * 
 * A subarray is defined as a contiguous block of elements in the array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,1,4,2], p = 6
 * Output: 1
 * Explanation: The sum of the elements in nums is 10, which is not divisible
 * by 6. We can remove the subarray [4], and the sum of the remaining elements
 * is 6, which is divisible by 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [6,3,5,2], p = 9
 * Output: 2
 * Explanation: We cannot remove a single element to get a sum divisible by 9.
 * The best way is to remove the subarray [5,2], leaving us with [6,3] with sum
 * 9.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3], p = 3
 * Output: 0
 * Explanation: Here the sum is 6. which is already divisible by 3. Thus we do
 * not need to remove anything.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= p <= 10^9
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int x = reduce(nums.begin(), nums.end(), 0LL) % p;
        if (x == 0) {
            return 0; // 移除空子数组（这行可以不要）
        }

        int n = nums.size(), ans = n, s = 0;
        // 由于下面 i 是从 0 开始的，前缀和下标就要从 -1 开始了
        unordered_map<int, int> last{{s, -1}};
        for (int i = 0; i < n; i++) {
            s = (s + nums[i]) % p;
            last[s] = i;
            auto it = last.find((s - x + p) % p);
            if (it != last.end()) {
                ans = min(ans, i - it->second);
            }
        }
        return ans < n ? ans : -1;
    }
};
// @lc code=end

