/*
 * @lc app=leetcode id=1879 lang=cpp
 *
 * [1879] Minimum XOR Sum of Two Arrays
 *
 * https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/description/
 *
 * algorithms
 * Hard (49.27%)
 * Likes:    709
 * Dislikes: 13
 * Total Accepted:    18.9K
 * Total Submissions: 37.9K
 * Testcase Example:  '[1,2]\n[2,3]'
 *
 * You are given two integer arrays nums1 and nums2 of length n.
 * 
 * The XOR sum of the two integer arrays is (nums1[0] XOR nums2[0]) + (nums1[1]
 * XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1]) (0-indexed).
 * 
 * 
 * For example, the XOR sum of [1,2,3] and [3,2,1] is equal to (1 XOR 3) + (2
 * XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4.
 * 
 * 
 * Rearrange the elements of nums2 such that the resulting XOR sum is
 * minimized.
 * 
 * Return the XOR sum after the rearrangement.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,2], nums2 = [2,3]
 * Output: 2
 * Explanation: Rearrange nums2 so that it becomes [3,2].
 * The XOR sum is (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2.
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [1,0,3], nums2 = [5,3,4]
 * Output: 8
 * Explanation: Rearrange nums2 so that it becomes [5,4,3]. 
 * The XOR sum is (1 XOR 5) + (0 XOR 4) + (3 XOR 3) = 4 + 4 + 0 = 8.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums1.length
 * n == nums2.length
 * 1 <= n <= 14
 * 0 <= nums1[i], nums2[i] <= 10^7
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 状压DP
 * f(i)表示未选中的下标集合为i的最小异或和
 * f(i)=min(f(i^1<<j)+nums1[j]^nums2[j])
 * 边界：i=∅，f=0
 * 入口：i=U，U∈[0,n-1]
 */
class Solution {
public:
    // 记忆化递归
    int minimumXORSum1(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> memo(1 << n, INT_MAX);
        auto dfs = [&](auto &dfs, int i) -> int {
            if (i == 0) {
                return 0;
            }
            int &res = memo[i];
            if (res != INT_MAX) {
                return res;
            }
            int d = n - popcount((unsigned) i);
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    res = min(res, dfs(dfs, i ^ 1 << j) +
                                       (nums1[d] ^ nums2[j]));
                }
            }
            return res;
        };
        return dfs(dfs, (1 << n) - 1);
    }

    // DP
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> f(1 << n, INT_MAX);
        f[0] = 0;
        for (int i = 1; i < 1 << n; i++) {
            int d = n - popcount((unsigned) i);
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    f[i] = min(f[i],
                               f[i ^ 1 << j] + (nums1[d] ^ nums2[j]));
                }
            }
        }
        return f.back();
    }
};
// @lc code=end

