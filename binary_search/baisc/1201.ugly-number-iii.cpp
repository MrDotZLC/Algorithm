/*
 * @lc app=leetcode id=1201 lang=cpp
 *
 * [1201] Ugly Number III
 *
 * https://leetcode.com/problems/ugly-number-iii/description/
 *
 * algorithms
 * Medium (30.55%)
 * Likes:    1295
 * Dislikes: 515
 * Total Accepted:    39.6K
 * Total Submissions: 129.2K
 * Testcase Example:  '3\n2\n3\n5'
 *
 * An ugly number is a positive integer that is divisible by a, b, or c.
 * 
 * Given four integers n, a, b, and c, return the n^th ugly number.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, a = 2, b = 3, c = 5
 * Output: 4
 * Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3^rd is
 * 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 4, a = 2, b = 3, c = 4
 * Output: 6
 * Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4^th is
 * 6.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 5, a = 2, b = 11, c = 13
 * Output: 10
 * Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5^th is
 * 10.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n, a, b, c <= 10^9
 * 1 <= a * b * c <= 10^18
 * It is guaranteed that the result will be in range [1, 2 * 10^9].
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        long long lcm_ab = lcm(1LL * a, b);
        long long lcm_bc = lcm(1LL * b, c);
        long long lcm_ac = lcm(1LL * a, c);
        long long lcm_abc = lcm(lcm_ab, c);

        auto check = [&] (long long x) -> bool {
            return x / a + x / b + x / c 
                    - x / lcm_ab - x / lcm_bc - x / lcm_ac
                    + x / lcm_abc < n;
        };

        long long L = 1LL * ranges::min({a, b, c}) + n - 2;
        long long R = 1LL * ranges::min({a, b, c}) * n;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid; 
        }
        return R;
    }
};
// @lc code=end

