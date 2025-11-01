/*
 * @lc app=leetcode id=718 lang=cpp
 *
 * [718] Maximum Length of Repeated Subarray
 *
 * https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/
 *
 * algorithms
 * Medium (51.04%)
 * Likes:    7021
 * Dislikes: 180
 * Total Accepted:    350.2K
 * Total Submissions: 684.6K
 * Testcase Example:  '[1,2,3,2,1]\n[3,2,1,4,7]'
 *
 * Given two integer arrays nums1 and nums2, return the maximum length of a
 * subarray that appears in both arrays.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
 * Output: 3
 * Explanation: The repeated subarray with maximum length is [3,2,1].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
 * Output: 5
 * Explanation: The repeated subarray with maximum length is [0,0,0,0,0].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 1000
 * 0 <= nums1[i], nums2[i] <= 100
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归：连续限制，枚举以(i, j)为结尾的最长公共子数组
    int findLength1(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), ans = 0;
        vector memo(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            if (nums1[i] == nums2[j]) {
                res = dfs(dfs, i - 1, j - 1) + 1;
            }
            return res;
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, dfs(dfs, i, j));
            }
        }
        return ans;
    }

    // DP递推
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), ans = 0;
        vector f(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (nums1[i] == nums2[j]) {
                    f[i + 1][j + 1] = f[i][j] + 1;
                    ans = max(ans, f[i + 1][j + 1]);
                }
            }
        }
        return ans;
    }
};
// @lc code=end

