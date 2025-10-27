/*
 * @lc app=leetcode id=1524 lang=cpp
 *
 * [1524] Number of Sub-arrays With Odd Sum
 *
 * https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/
 *
 * algorithms
 * Medium (55.99%)
 * Likes:    2044
 * Dislikes: 99
 * Total Accepted:    169.8K
 * Total Submissions: 303.8K
 * Testcase Example:  '[1,3,5]'
 *
 * Given an array of integers arr, return the number of subarrays with an odd
 * sum.
 * 
 * Since the answer can be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,3,5]
 * Output: 4
 * Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
 * All sub-arrays sum are [1,4,9,3,8,5].
 * Odd sums are [1,9,3,5] so the answer is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [2,4,6]
 * Output: 0
 * Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
 * All sub-arrays sum are [2,6,12,4,10,6].
 * All sub-arrays have even sum and the answer is 0.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [1,2,3,4,5,6,7]
 * Output: 16
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 100
 * 
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        long long ans = 0;
        int sum = 0, MOD = 1'000'000'007;
        unordered_map<int, int> cnt(2);
        cnt[0] = 1;
        for (int x : arr) {
            sum += x;
            ans += cnt[sum % 2 ? 0 : 1];
            cnt[sum % 2]++;
        }
        return ans % MOD;
    }
};
// @lc code=end

