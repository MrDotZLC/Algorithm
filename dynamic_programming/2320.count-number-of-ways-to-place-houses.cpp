/*
 * @lc app=leetcode id=2320 lang=cpp
 *
 * [2320] Count Number of Ways to Place Houses
 *
 * https://leetcode.com/problems/count-number-of-ways-to-place-houses/description/
 *
 * algorithms
 * Medium (42.96%)
 * Likes:    629
 * Dislikes: 201
 * Total Accepted:    33.9K
 * Total Submissions: 78.2K
 * Testcase Example:  '1'
 *
 * There is a street with n * 2 plots, where there are n plots on each side of
 * the street. The plots on each side are numbered from 1 to n. On each plot, a
 * house can be placed.
 * 
 * Return the number of ways houses can be placed such that no two houses are
 * adjacent to each other on the same side of the street. Since the answer may
 * be very large, return it modulo 10^9 + 7.
 * 
 * Note that if a house is placed on the i^th plot on one side of the street, a
 * house can also be placed on the i^th plot on the other side of the
 * street.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1
 * Output: 4
 * Explanation: 
 * Possible arrangements:
 * 1. All plots are empty.
 * 2. A house is placed on one side of the street.
 * 3. A house is placed on the other side of the street.
 * 4. Two houses are placed, one on each side of the street.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2
 * Output: 9
 * Explanation: The 9 possible arrangements are shown in the diagram above.
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
using namespace std;
// @lc code=start
const int MOD = 1e9 + 7;
const int MX = 1e4;
int f[MX + 1] = {1, 2};

int init = []() {
    for (int i = 2; i <= MX; i++) {
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    }
    return 0;
}();


class Solution {
public:
    int countHousePlacements(int n) {
        return (1LL * f[n] * f[n]) % MOD; 
    }
};
// @lc code=end

