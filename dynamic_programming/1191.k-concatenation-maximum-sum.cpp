/*
 * @lc app=leetcode id=1191 lang=cpp
 *
 * [1191] K-Concatenation Maximum Sum
 *
 * https://leetcode.com/problems/k-concatenation-maximum-sum/description/
 *
 * algorithms
 * Medium (24.33%)
 * Likes:    1494
 * Dislikes: 128
 * Total Accepted:    41.3K
 * Total Submissions: 168.2K
 * Testcase Example:  '[1,2]\n3'
 *
 * Given an integer array arr and an integer k, modify the array by repeating
 * it k times.
 * 
 * For example, if arr = [1, 2] and k = 3 then the modified array will be [1,
 * 2, 1, 2, 1, 2].
 * 
 * Return the maximum sub-array sum in the modified array. Note that the length
 * of the sub-array can be 0 and its sum in that case is 0.
 * 
 * As the answer can be very large, return the answer modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2], k = 3
 * Output: 9
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,-2,1], k = 5
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [-1,-2], k = 7
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 1 <= k <= 10^5
 * -10^4 <= arr[i] <= 10^4
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size(), MOD = 1e9 + 7;
        long long ans = 0, f = 0;
        for (int i = 0; i < (k > 2 ? 2 : k) * n; i++) {
            f = max(f, 0LL) + arr[i % n];
            ans = max(ans, f);
        }
        int s = reduce(arr.begin(), arr.end());
        // s大于0，则中间的k-2个arr一定都被包含
        // s小于0，则中间的k-2个arr一定都不被包含
        ans += 1LL * max(s, 0) * (k - 2 > 0 ? k - 2 : 0);
        return ans % MOD;
    }
};
// @lc code=end

