/*
 * @lc app=leetcode id=1006 lang=cpp
 *
 * [1006] Clumsy Factorial
 *
 * https://leetcode.com/problems/clumsy-factorial/description/
 *
 * algorithms
 * Medium (59.55%)
 * Likes:    423
 * Dislikes: 364
 * Total Accepted:    42.6K
 * Total Submissions: 71.1K
 * Testcase Example:  '4'
 *
 * The factorial of a positive integer n is the product of all positive
 * integers less than or equal to n.
 * 
 * 
 * For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.
 * 
 * 
 * We make a clumsy factorial using the integers in decreasing order by
 * swapping out the multiply operations for a fixed rotation of operations with
 * multiply '*', divide '/', add '+', and subtract '-' in this order.
 * 
 * 
 * For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
 * 
 * 
 * However, these operations are still applied using the usual order of
 * operations of arithmetic. We do all multiplication and division steps before
 * any addition or subtraction steps, and multiplication and division steps are
 * processed left to right.
 * 
 * Additionally, the division that we use is floor division such that 10 * 9 /
 * 8 = 90 / 8 = 11.
 * 
 * Given an integer n, return the clumsy factorial of n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4
 * Output: 7
 * Explanation: 7 = 4 * 3 / 2 + 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 10
 * Output: 12
 * Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^4
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int clumsy(int n) {
        int idx = 0;
        vector<long long> st;
        while (n) {
            if (st.empty()) {
                st.push_back(n);
            } else {
                int op = idx % 4;
                switch (op) {
                    case 1:
                        st.back() *= n;
                        break;
                    case 2:
                        st.back() /= n;
                        break;
                    case 3:
                        st.back() += n;
                        break;
                    case 0:
                        st.push_back(-n);
                        break;
                }
            }
            idx++;
            n--;
        }
        return reduce(st.begin(), st.end(), 0LL);
    }
};
// @lc code=end

