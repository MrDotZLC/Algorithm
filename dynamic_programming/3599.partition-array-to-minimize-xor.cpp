/*
 * @lc app=leetcode id=3599 lang=cpp
 *
 * [3599] Partition Array to Minimize XOR
 *
 * https://leetcode.com/problems/partition-array-to-minimize-xor/description/
 *
 * algorithms
 * Medium (39.57%)
 * Likes:    104
 * Dislikes: 6
 * Total Accepted:    13.4K
 * Total Submissions: 33K
 * Testcase Example:  '[1,2,3]\n2'
 *
 * You are given an integer array nums and an integer k.
 * 
 * Your task is to partition nums into k non-empty subarrays. For each
 * subarray, compute the bitwise XOR of all its elements.
 * 
 * Return the minimum possible value of the maximum XOR among these k
 * subarrays.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3], k = 2
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * The optimal partition is [1] and [2, 3].
 * 
 * 
 * XOR of the first subarray is 1.
 * XOR of the second subarray is 2 XOR 3 = 1.
 * 
 * 
 * The maximum XOR among the subarrays is 1, which is the minimum possible.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,3,3,2], k = 3
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * The optimal partition is [2], [3, 3], and [2].
 * 
 * 
 * XOR of the first subarray is 2.
 * XOR of the second subarray is 3 XOR 3 = 0.
 * XOR of the third subarray is 2.
 * 
 * 
 * The maximum XOR among the subarrays is 2, which is the minimum possible.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,1,2,3,1], k = 2
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * The optimal partition is [1, 1] and [2, 3, 1].
 * 
 * 
 * XOR of the first subarray is 1 XOR 1 = 0.
 * XOR of the second subarray is 2 XOR 3 XOR 1 = 0.
 * 
 * 
 * The maximum XOR among the subarrays is 0, which is the minimum possible.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 250
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= n
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP+记忆化
    int minXor1(vector<int>& nums, int k) {
        int n = nums.size();
        vector f(k + 1, vector<int>(n + 1, INT_MAX));
        f[0][0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = i; j <= n - (k - i); j++) {
                int xor_sum = 0;
                for (int l = j - 1; l >= i - 1; l--) {
                    xor_sum ^= nums[l];
                    f[i][j] = min(f[i][j], max(f[i - 1][l], xor_sum));
                }
            }
        }
        return f[k][n];
    }

    // DP+记忆化+空间优化
    int minXor(vector<int>& nums, int k) {
        int n = nums.size();
        vector f(n + 1, INT_MAX);
        f[0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = n - (k - i); j >= i; j--) {
                int xor_sum = 0;
                f[j] = INT_MAX; // 会在最外层循环时重复使用
                for (int l = j - 1; l >= i - 1; l--) {
                    xor_sum ^= nums[l];
                    f[j] = min(f[j], max(f[l], xor_sum));
                }
            }
        }
        return f[n];
    }
};
// @lc code=end

