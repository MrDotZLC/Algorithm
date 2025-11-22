/*
 * @lc app=leetcode id=788 lang=cpp
 *
 * [788] Rotated Digits
 *
 * https://leetcode.com/problems/rotated-digits/description/
 *
 * algorithms
 * Medium (56.48%)
 * Likes:    776
 * Dislikes: 1944
 * Total Accepted:    125.3K
 * Total Submissions: 221.2K
 * Testcase Example:  '10'
 *
 * An integer x is a good if after rotating each digit individually by 180
 * degrees, we get a valid number that is different from x. Each digit must be
 * rotated - we cannot choose to leave it alone.
 * 
 * A number is valid if each digit remains a digit after rotation. For
 * example:
 * 
 * 
 * 0, 1, and 8 rotate to themselves,
 * 2 and 5 rotate to each other (in this case they are rotated in a different
 * direction, in other words, 2 or 5 gets mirrored),
 * 6 and 9 rotate to each other, and
 * the rest of the numbers do not rotate to any other number and become
 * invalid.
 * 
 * 
 * Given an integer n, return the number of good integers in the range [1,
 * n].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 10
 * Output: 4
 * Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
 * Note that 1 and 10 are not good numbers, since they remain unchanged after
 * rotating.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 0
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 2
 * Output: 1
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
#include <array>
#include <string>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 数位DP
 * 对每个可能的数位和进行DP，分别求得方案数，返回最大方案数
 * f(i,is_good,high_limit)表示第0到i数位在是否包括好数位（is_good）下的方案数
 * f(i,is_good,high_limit)=sum{f(i+1,new_good,high_limit&&d==hi)},
 * hi=high_limit?high[i]-'0':9, high=string(n), new_good=is_good||d属于{2,5,6,9}
 * m=high.length, d∈[0,9]/{3,4,7}
 * 
 * 边界：i=m-1且target=0时，f=1
 * 入口：f(0,target,true), target∈[1,9*m]
 */
class Solution {
public:
    int diffs[10] = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
    int rotatedDigits(int n) {
        string s = to_string(n);
        int m = s.length();
        vector<array<int, 2>> memo(m, {-1, -1});
        auto dfs = [&](this auto &&dfs, int i, bool is_good, bool high_limit) -> int {
            if (i == m) {
                return is_good;
            }
            if (!high_limit && memo[i][is_good] != -1) {
                return memo[i][is_good];
            }
            int res = 0;
            int hi = high_limit ? s[i] - '0' : 9;
            for (int d = 0; d <= hi; d++) {
                if (diffs[d] != -1) {
                    res += dfs(i + 1, is_good || diffs[d], high_limit && d == hi);
                }
            }
            if (!high_limit) {
                memo[i][is_good] = res;
            }
            return res;
        };
        return dfs(0, false, true);
    }
};
// @lc code=end

