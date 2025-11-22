/*
 * @lc app=leetcode id=600 lang=cpp
 *
 * [600] Non-negative Integers without Consecutive Ones
 *
 * https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/description/
 *
 * algorithms
 * Hard (40.42%)
 * Likes:    1602
 * Dislikes: 137
 * Total Accepted:    48.3K
 * Total Submissions: 117.4K
 * Testcase Example:  '5'
 *
 * Given a positive integer n, return the number of the integers in the range
 * [0, n] whose binary representations do not contain consecutive ones.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 5
 * Output: 5
 * Explanation:
 * Here are the non-negative integers <= 5 with their corresponding binary
 * representations:
 * 0 : 0
 * 1 : 1
 * 2 : 10
 * 3 : 11
 * 4 : 100
 * 5 : 101
 * Among them, only integer 3 disobeys the rule (two consecutive ones) and the
 * other 5 satisfy the rule. 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 2
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^9
 * 
 * 
 */
#include <vector>
#include <array>
#include <string>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 数位DP
 * 对每个可能的数位和进行DP，分别求得方案数，返回最大方案数
 * f(i,pre,high_limit)表示第i到m数位且前一位pre的无连续1方案数
 * f(i,pre,high_limit)=f(i+1,false,high_limit&&hi==0) + !pre ? f(i+1,true,high_limit&&hi==1) : 0,
 * m=bit_width(n)
 * 
 * 边界：i=0，f=1
 * 入口：f(m+1,false,true)
 */
class Solution {
public:
    int findIntegers(int n) {
        int m = bit_width((unsigned) n);
        vector<array<int, 2>> memo(m, {-1, -1});
        auto dfs = [&](this auto &&dfs, int i, bool pre, bool high_limit) -> int {
            if (i < 0) {
                return 1;
            }
            if (!high_limit && memo[i][pre] != -1) {
                return memo[i][pre];
            }
            int hi = high_limit ? n >> i & 1 : 1;
            int res = dfs(i - 1, false, high_limit && hi == 0); // 选0，有限高且hi为0
            if (!pre && hi == 1) { // 选1
                res += dfs(i - 1, true, high_limit); // 有限高且hi为1
            }
            if (!high_limit) {
                memo[i][pre] = res;
            }
            return res;
        };
        return dfs(m + 1, false, true); // 高位到低位
    }
};
// @lc code=end

