/*
 * @lc app=leetcode id=907 lang=cpp
 *
 * [907] Sum of Subarray Minimums
 *
 * https://leetcode.com/problems/sum-of-subarray-minimums/description/
 *
 * algorithms
 * Medium (37.75%)
 * Likes:    8934
 * Dislikes: 710
 * Total Accepted:    394.5K
 * Total Submissions: 1M
 * Testcase Example:  '[3,1,2,4]'
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over
 * every (contiguous) subarray of arr. Since the answer may be large, return
 * the answer modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [3,1,2,4]
 * Output: 17
 * Explanation: 
 * Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4],
 * [3,1,2,4]. 
 * Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 * Sum is 17.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [11,81,94,43,3]
 * Output: 444
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 3 * 10^4
 * 1 <= arr[i] <= 3 * 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int MOD = 1e9 + 7;
        arr.push_back(-1); 
        int n = arr.size();
        vector<int> stk;
        stk.push_back(-1);
        long long ans = 0;
        for (int r = 0; r < n; r++) {
            int h_r = arr[r];
            while (stk.size() > 1 && arr[stk.back()] >= h_r) {
                int i = stk.back();
                stk.pop_back();
                int l = stk.back();
                ans += (long long) arr[i] * (i - l) * (r - i);
            }
            stk.push_back(r);
        }
        return ans % MOD;
    }
};
// @lc code=end

