/*
 * @lc app=leetcode id=902 lang=cpp
 *
 * [902] Numbers At Most N Given Digit Set
 *
 * https://leetcode.com/problems/numbers-at-most-n-given-digit-set/description/
 *
 * algorithms
 * Hard (43.50%)
 * Likes:    1447
 * Dislikes: 98
 * Total Accepted:    52K
 * Total Submissions: 117.9K
 * Testcase Example:  '["1","3","5","7"]\n100'
 *
 * Given an array of digits which is sorted in non-decreasing order. You can
 * write numbers using each digits[i] as many times as we want. For example, if
 * digits = ['1','3','5'], we may write numbers such as '13', '551', and
 * '1351315'.
 * 
 * Return the number of positive integers that can be generated that are less
 * than or equal to a given integer n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: digits = ["1","3","5","7"], n = 100
 * Output: 20
 * Explanation: 
 * The 20 numbers that can be written are:
 * 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75,
 * 77.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: digits = ["1","4","9"], n = 1000000000
 * Output: 29523
 * Explanation: 
 * We can write 3 one digit numbers, 9 two digit numbers, 27 three digit
 * numbers,
 * 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 * 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit
 * numbers.
 * In total, this is 29523 integers that can be written using the digits
 * array.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: digits = ["7"], n = 8
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= digits.length <= 9
 * digits[i].length == 1
 * digits[i] is a digit from '1' to '9'.
 * All the values in digits are unique.
 * digits is sorted in non-decreasing order.
 * 1 <= n <= 10^9
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
 * 对每个可能的数位和进行DP，分别求得方案数，返回最大方案数
 * f(i,high_limit,is_num)表示构造第i到m-1数位的方案数
 * f(i,high_limit,is_num)=sum{f(i+1,high_limit&&d==hi,is_num)},
 * lo=is_num?0:1, hi=high_limit?high[i]-'0':9, high=string(n), 
 * m=high.length, d∈[lo,hi]
 * 
 * 边界：i=m-1&&is_num=true时，f=1
 * 入口：f(0,true,false)
 */
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int m = s.length();
        vector<int> memo(m, -1);
        auto dfs = [&](this auto &&dfs, int i, bool high_limit, bool is_num) -> int {
            if (i == m) {
                return is_num;
            }
            if (!high_limit && is_num && memo[i] != -1) {
                return memo[i];
            }
            int res = 0;
            if (!is_num) {
                res = dfs(i + 1, false, false);
            }
            // int lo = is_num ? 0 : 1; // ditgit中不包含 '0'，故无需考虑
            char up = high_limit ? s[i] : '9';
            for (auto &d : digits) { // 枚举要填入的数字 d
                if (d[0] > up) break; // d 超过上限，由于 digits 是有序的，后面的 d 都会超过上限，故退出循环
                // is_limit：如果当前受到 n 的约束，且填的数字等于上限，那么后面仍然会受到 n 的约束
                // is_num 为 true，因为填了数字
                res += dfs(i + 1, high_limit && d[0] == up, true);
            }
            if (!high_limit && is_num) {
                memo[i] = res;
            }
            return res;
        };
        return dfs(0, true, false);
    }
};
// @lc code=end

