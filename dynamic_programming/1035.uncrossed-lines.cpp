/*
 * @lc app=leetcode id=1035 lang=cpp
 *
 * [1035] Uncrossed Lines
 *
 * https://leetcode.com/problems/uncrossed-lines/description/
 *
 * algorithms
 * Medium (64.45%)
 * Likes:    3943
 * Dislikes: 62
 * Total Accepted:    187.3K
 * Total Submissions: 289.2K
 * Testcase Example:  '[1,4,2]\n[1,2,4]'
 *
 * You are given two integer arrays nums1 and nums2. We write the integers of
 * nums1 and nums2 (in the order they are given) on two separate horizontal
 * lines.
 * 
 * We may draw connecting lines: a straight line connecting two numbers
 * nums1[i] and nums2[j] such that:
 * 
 * 
 * nums1[i] == nums2[j], and
 * the line we draw does not intersect any other connecting (non-horizontal)
 * line.
 * 
 * 
 * Note that a connecting line cannot intersect even at the endpoints (i.e.,
 * each number can only belong to one connecting line).
 * 
 * Return the maximum number of connecting lines we can draw in this way.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,4,2], nums2 = [1,2,4]
 * Output: 2
 * Explanation: We can draw 2 uncrossed lines as in the diagram.
 * We cannot draw 3 uncrossed lines, because the line from nums1[1] = 4 to
 * nums2[2] = 4 will intersect the line from nums1[2]=2 to nums2[1]=2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
 * Output: 3
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
 * Output: 2
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 500
 * 1 <= nums1[i], nums2[j] <= 2000
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int maxUncrossedLines1(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector memo(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return 0;
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            if (nums1[i] == nums2[j]) {
                return ans = dfs(dfs, i - 1, j - 1) + 1; 
            }
            return ans = max(dfs(dfs, i - 1, j), dfs(dfs, i, j - 1));
        };
        return dfs(dfs, n - 1, m - 1);
    }

    // DP递推+空间优化
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> f(m + 1);
        for (int x : nums1) {
            for (int j = 0, pre = 0; j < m; j++) {
                int tmp = f[j + 1];
                f[j + 1] = x == nums2[j] ? pre + 1 : max(f[j], f[j + 1]);
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

