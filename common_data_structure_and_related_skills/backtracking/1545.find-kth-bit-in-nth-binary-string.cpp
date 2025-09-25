/*
 * @lc app=leetcode id=1545 lang=cpp
 *
 * [1545] Find Kth Bit in Nth Binary String
 *
 * https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/description/
 *
 * algorithms
 * Medium (70.18%)
 * Likes:    1505
 * Dislikes: 96
 * Total Accepted:    165.1K
 * Total Submissions: 235.3K
 * Testcase Example:  '3\n1'
 *
 * Given two positive integers n and k, the binary string Sn is formed as
 * follows:
 * 
 * 
 * S1 = "0"
 * Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
 * 
 * 
 * Where + denotes the concatenation operation, reverse(x) returns the reversed
 * string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1
 * changes to 0).
 * 
 * For example, the first four strings in the above sequence are:
 * 
 * 
 * S1 = "0"
 * S2 = "011"
 * S3 = "0111001"
 * S4 = "011100110110001"
 * 
 * 
 * Return the k^th bit in Sn. It is guaranteed that k is valid for the given
 * n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, k = 1
 * Output: "0"
 * Explanation: S3 is "0111001".
 * The 1^st bit is "0".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 4, k = 11
 * Output: "1"
 * Explanation: S4 is "011100110110001".
 * The 11^th bit is "1".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 20
 * 1 <= k <= 2^n - 1
 * 
 * 
 */
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    char findKthBit1(int n, int k) {
        if (n == 1) {
            return '0';
        }
        if (k == (1 << (n - 1))) {
            return '1';
        }
        if (k < (1 << (n - 1))) {
            return findKthBit(n - 1, k);
        }
        char ans = findKthBit(n - 1, (1 << n) - k);
        return '0' + (ans - '0' + 1) % 2;
    }

    char findKthBit(int n, int k) {
        int invert_num = 0;
        for (int i = n; i > 0; i--) {
            if (k > 1 && k == (1 << (i - 1))) {
                return '1' - (invert_num) % 2;
            }
            if (k > (1 << (i - 1))) {
                invert_num++;
                k = (1 << i) - k;
            }
        }

        return '0' + (invert_num) % 2;
    }
};
// @lc code=end

