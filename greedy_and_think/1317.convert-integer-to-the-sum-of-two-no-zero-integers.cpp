/*
 * @lc app=leetcode id=1317 lang=cpp
 *
 * [1317] Convert Integer to the Sum of Two No-Zero Integers
 *
 * https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description/
 *
 * algorithms
 * Easy (54.22%)
 * Likes:    440
 * Dislikes: 319
 * Total Accepted:    60.7K
 * Total Submissions: 111.7K
 * Testcase Example:  '2'
 *
 * No-Zero integer is a positive integer that does not contain any 0 in its
 * decimal representation.
 * 
 * Given an integer n, return a list of two integers [a, b] where:
 * 
 * 
 * a and b are No-Zero integers.
 * a + b = n
 * 
 * 
 * The test cases are generated so that there is at least one valid solution.
 * If there are many valid solutions, you can return any of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2
 * Output: [1,1]
 * Explanation: Let a = 1 and b = 1.
 * Both a and b are no-zero integers, and a + b = 2 = n.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 11
 * Output: [2,9]
 * Explanation: Let a = 2 and b = 9.
 * Both a and b are no-zero integers, and a + b = 11 = n.
 * Note that there are other valid answers as [8, 3] that can be accepted.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int a = 0;
        int base = 1;
        for (int x = n; x > 1; x /= 10) {
            int d = x % 10;
            if (d <= 1) {
                d += 10;
                x -= 10;
            }
            a += (d / 2) * base;
            base *= 10;
        }
        return {a, n - a};
    }
};
// @lc code=end

