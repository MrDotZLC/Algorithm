/*
 * @lc app=leetcode id=668 lang=cpp
 *
 * [668] Kth Smallest Number in Multiplication Table
 *
 * https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/description/
 *
 * algorithms
 * Hard (52.99%)
 * Likes:    2231
 * Dislikes: 60
 * Total Accepted:    77.2K
 * Total Submissions: 145.3K
 * Testcase Example:  '3\n3\n5'
 *
 * Nearly everyone has used the Multiplication Table. The multiplication table
 * of size m x n is an integer matrix mat where mat[i][j] == i * j
 * (1-indexed).
 * 
 * Given three integers m, n, and k, return the k^th smallest element in the m
 * x n multiplication table.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 3, n = 3, k = 5
 * Output: 3
 * Explanation: The 5^th smallest number is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 2, n = 3, k = 6
 * Output: 6
 * Explanation: The 6^th smallest number is 6.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 3 * 10^4
 * 1 <= k <= m * n
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto check1 = [&](int t) {
            int cnt = 0;
            for (int i = 1; i <= m; i++) {
                cnt += min(t / i, n);
            }
            if (cnt < k) {
                return true;
            }
            return false;
        };

        // When (t / i) >= n, the possible values of i are in [1, t / n]
        // We can handle this range directly to reduce unnecessary iterations.
        auto check = [&](int t) {
            int cnt = t / n * n;
            for (int i = t / n + 1; i <= m; i++) {
                cnt += t / i;
            }
            if (cnt < k) {
                return true;
            }
            return false;
        };

        int L = 0, R = m * n;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid; 
        }
        return R;
    }
};
// @lc code=end
