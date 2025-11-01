/*
 * @lc app=leetcode id=1458 lang=cpp
 *
 * [1458] Max Dot Product of Two Subsequences
 *
 * https://leetcode.com/problems/max-dot-product-of-two-subsequences/description/
 *
 * algorithms
 * Hard (62.36%)
 * Likes:    1699
 * Dislikes: 33
 * Total Accepted:    84.4K
 * Total Submissions: 135.3K
 * Testcase Example:  '[2,1,-2,5]\n[3,0,-6]'
 *
 * Given two arrays nums1 and nums2.
 * 
 * Return the maximum dot product between non-empty subsequences of nums1 and
 * nums2 with the same length.
 * 
 * A subsequence of a array is a new array which is formed from the original
 * array by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, [2,3,5] is a
 * subsequence of [1,2,3,4,5] while [1,5,3] is not).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
 * Output: 18
 * Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from
 * nums2.
 * Their dot product is (2*3 + (-2)*(-6)) = 18.
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [3,-2], nums2 = [2,-6,7]
 * Output: 21
 * Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
 * Their dot product is (3*7) = 21.
 * 
 * Example 3:
 * 
 * 
 * Input: nums1 = [-1,-1], nums2 = [1,1]
 * Output: -1
 * Explanation: Take subsequence [-1] from nums1 and subsequence [1] from
 * nums2.
 * Their dot product is -1.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 500
 * -1000 <= nums1[i], nums2[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int maxDotProduct1(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector memo(n, vector<int>(m, INT_MIN));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return INT_MIN / 2;
            }
            int &ans = memo[i][j];
            if (ans != INT_MIN) {
                return ans;
            }
            int v = nums1[i] * nums2[j];
            return ans =
                       max({dfs(dfs, i - 1, j - 1) + v, v,
                            dfs(dfs, i - 1, j), dfs(dfs, i, j - 1)});
        };
        return dfs(dfs, n - 1, m - 1);
    }

    // DP递推+空间优化
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> f(m + 1, INT_MIN / 2);
        for (int x : nums1) {
            for (int j = 0, pre = 0; j < m; j++) {
                int tmp = f[j + 1];
                int v = x * nums2[j];
                f[j + 1] = max({f[j], f[j + 1], v, pre + v});
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

