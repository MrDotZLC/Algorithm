/*
 * @lc app=leetcode id=2305 lang=cpp
 *
 * [2305] Fair Distribution of Cookies
 *
 * https://leetcode.com/problems/fair-distribution-of-cookies/description/
 *
 * algorithms
 * Medium (69.44%)
 * Likes:    2714
 * Dislikes: 125
 * Total Accepted:    115.9K
 * Total Submissions: 166.2K
 * Testcase Example:  '[8,15,10,20,8]\n2'
 *
 * You are given an integer array cookies, where cookies[i] denotes the number
 * of cookies in the i^th bag. You are also given an integer k that denotes the
 * number of children to distribute all the bags of cookies to. All the cookies
 * in the same bag must go to the same child and cannot be split up.
 * 
 * The unfairness of a distribution is defined as the maximum total cookies
 * obtained by a single child in the distribution.
 * 
 * Return the minimum unfairness of all distributions.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: cookies = [8,15,10,20,8], k = 2
 * Output: 31
 * Explanation: One optimal distribution is [8,15,8] and [10,20]
 * - The 1^st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31
 * cookies.
 * - The 2^nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
 * The unfairness of the distribution is max(31,30) = 31.
 * It can be shown that there is no distribution with an unfairness less than
 * 31.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: cookies = [6,1,3,2,2,4,1,2], k = 3
 * Output: 7
 * Explanation: One optimal distribution is [6,1], [3,2,2], and [4,1,2]
 * - The 1^st child receives [6,1] which has a total of 6 + 1 = 7 cookies.
 * - The 2^nd child receives [3,2,2] which has a total of 3 + 2 + 2 = 7
 * cookies.
 * - The 3^rd child receives [4,1,2] which has a total of 4 + 1 + 2 = 7
 * cookies.
 * The unfairness of the distribution is max(7,7,7) = 7.
 * It can be shown that there is no distribution with an unfairness less than
 * 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= cookies.length <= 8
 * 1 <= cookies[i] <= 10^5
 * 2 <= k <= cookies.length
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 子集状压DP
    int distributeCookies1(vector<int>& cookies, int k) {
        int n = cookies.size(), m = 1 << n;
        // 每种方案的饼干数
        vector<int> sum(m);
        // 枚举所有方案
        for (int i = 0; i < m; i++) {
            // 如果第j个零食包在方案中，则将其饼干数累加到sum[i]
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    sum[i] += cookies[j];
                }
            }
        }

        vector<vector<int>> f(k, vector<int>(m));
        f[0] = sum; // 第一个孩子一共有2^n个方案，正好就是sum
        for (int i = 1; i < k; i++) { // 考虑前i个孩子
            for (int j = 0; j < m; j++) { // 枚举饼干组合的方案
                // 考虑f[i]的方案是从f[i-1]得来
                // 枚举第i个孩子方案，即j的子集
                f[i][j] = INT_MAX;
                for (int s = j; s; s = (s - 1) & j) { // 枚举集合j的子集
                    f[i][j] = min(f[i][j], max(f[i - 1][j ^ s], sum[s]));
                }
            }
        }
        return f[k - 1][m - 1];
    }

    // 子集状压DP+空间优化+剪枝
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size(), m = 1 << n;
        // 每种方案的饼干数
        vector<int> sum(m);
        // 枚举所有方案
        for (int i = 0; i < m; i++) {
            // 如果第j个零食包在方案中，则将其饼干数累加到sum[i]
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    sum[i] += cookies[j];
                }
            }
        }

        vector<int> f(sum);
        for (int i = 1; i < k; i++) { // 考虑前i个孩子
            for (int j = m - 1; j; j--) { // 枚举饼干组合的方案
                // 考虑f[i]的方案是从f[i-1]得来
                // 枚举第i个孩子方案，即j的子集
                for (int s = j; s; s = (s - 1) & j) { // 枚举集合j的子集
                    f[j] = min(f[j], max(f[j ^ s], sum[s]));
                }
            }
        }
        return f[m - 1];
    }
};
// @lc code=end

