/*
 * @lc app=leetcode id=2376 lang=cpp
 *
 * [2376] Count Special Integers
 *
 * https://leetcode.com/problems/count-special-integers/description/
 *
 * algorithms
 * Hard (40.07%)
 * Likes:    618
 * Dislikes: 35
 * Total Accepted:    15.9K
 * Total Submissions: 38.8K
 * Testcase Example:  '20'
 *
 * We call a positive integer special if all of its digits are distinct.
 * 
 * Given a positive integer n, return the number of special integers that
 * belong to the interval [1, n].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 20
 * Output: 19
 * Explanation: All the integers from 1 to 20, except 11, are special. Thus,
 * there are 19 special integers.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5
 * Output: 5
 * Explanation: All the integers from 1 to 5 are special.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 135
 * Output: 110
 * Explanation: There are 110 integers from 1 to 135 that are special.
 * Some of the integers that are not special are: 22, 114, and 131.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 2 * 10^9
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 数位DP
 * 从高位到低位计算，考虑每个数位的下界与上界，枚举边界范围内的数值并累加方案数
 * 需要考虑边界限制和前导零限制！
 * f(i,mask)表示第i数位在已用数字情况为mask时的方案数
 * f(i,mask)=sum{f(i+1,mask|1<<j)}, j∈[low,high]&&mask&(1<<j)==0
 * 边界：i=len(n)-1, f=1
 * 入口：f(0,0)
 */
class Solution {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int m = s.length();

        vector<vector<int>> memo(m, vector<int>(1 << 10, -1));
        auto dfs = [&](this auto &&dfs, int i, int mask, bool is_limit, bool is_num) -> int {
            if (i == m) {
                return is_num;
            }
            if (!is_limit && is_num && memo[i][mask] != -1) {
                return memo[i][mask];
            }
            int res = 0;
            // 有前导零，可直接不选
            if (!is_num) {
                res = dfs(i + 1, mask, false, false);
            }
            int lo = is_num ? 0 : 1;
            int hi = is_limit ? s[i] - '0' : 9;
            for (int d = lo; d <= hi; d++) {
                if ((mask & 1 << d) == 0) {
                    res += dfs(i + 1, mask | 1 << d, is_limit && d == hi, true);
                }
            }
            if (!is_limit && is_num) {
                memo[i][mask] = res;
            }
            return res;
        };
        return dfs(0, 0, true, false);
    }
};
// @lc code=end

