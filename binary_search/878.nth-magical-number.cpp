/*
 * @lc app=leetcode id=878 lang=cpp
 *
 * [878] Nth Magical Number
 *
 * https://leetcode.com/problems/nth-magical-number/description/
 *
 * algorithms
 * Hard (35.88%)
 * Likes:    1320
 * Dislikes: 168
 * Total Accepted:    45.9K
 * Total Submissions: 127.9K
 * Testcase Example:  '1\n2\n3'
 *
 * A positive integer is magical if it is divisible by either a or b.
 * 
 * Given the three integers n, a, and b, return the n^th magical number. Since
 * the answer may be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1, a = 2, b = 3
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 4, a = 2, b = 3
 * Output: 6
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^9
 * 2 <= a, b <= 4 * 10^4
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        const int MOD = 1e9 + 7;
        auto gcd = [&](int a, int b) -> int { // 最大公约数
            while (a != 0) {
                int temp = a;
                a = b % a;
                b = temp;
            }
            return b;
        };

        long long lcm = (long long)(a * b) / gcd(a, b); // 最小公倍数std::lcm(a, b)
        long long L = min(a, b) + n - 1 - 1;
        long long R = 1LL * min(a, b) * n;
        while (L + 1 < R) {
            long long mid = L + (R - L) / 2;
            (mid / a + mid / b - mid / lcm < n ? L : R) = mid; 
        }
        return R % MOD;
    }
};
// @lc code=end

