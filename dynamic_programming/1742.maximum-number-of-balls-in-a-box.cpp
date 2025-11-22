/*
 * @lc app=leetcode id=1742 lang=cpp
 *
 * [1742] Maximum Number of Balls in a Box
 *
 * https://leetcode.com/problems/maximum-number-of-balls-in-a-box/description/
 *
 * algorithms
 * Easy (74.30%)
 * Likes:    646
 * Dislikes: 168
 * Total Accepted:    80.7K
 * Total Submissions: 108.2K
 * Testcase Example:  '1\n10'
 *
 * You are working in a ball factory where you have n balls numbered from
 * lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1),
 * and an infinite number of boxes numbered from 1 to infinity.
 * 
 * Your job at this factory is to put each ball in the box with a number equal
 * to the sum of digits of the ball's number. For example, the ball number 321
 * will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be
 * put in the box number 1 + 0 = 1.
 * 
 * Given two integers lowLimit and highLimit, return the number of balls in the
 * box with the most balls.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: lowLimit = 1, highLimit = 10
 * Output: 2
 * Explanation:
 * Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
 * Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
 * Box 1 has the most number of balls with 2 balls.
 * 
 * Example 2:
 * 
 * 
 * Input: lowLimit = 5, highLimit = 15
 * Output: 2
 * Explanation:
 * Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
 * Ball Count:  1 1 1 1 2 2 1 1 1 0  0  ...
 * Boxes 5 and 6 have the most number of balls with 2 balls in each.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: lowLimit = 19, highLimit = 28
 * Output: 2
 * Explanation:
 * Box Number:  1 2 3 4 5 6 7 8 9 10 11 12 ...
 * Ball Count:  0 1 1 1 1 1 1 1 1 2  0  0  ...
 * Box 10 has the most number of balls with 2 balls.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= lowLimit <= highLimit <= 10^5
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
 * f(i,target,low_limit,high_limit)表示第i到m-1数位和为target的方案数
 * f(i,target,low_limit,high_limit)=sum{f(i+1,target-d,low_limit&&d==lo,high_limit&&d==hi)},
 * lo=low_limit?low[i]-'0':0, hi=high_limit?high[i]-'0':9, low=string(lowLimit), high=string(highlimit), 
 * m=high.length, d∈[lo,hi]
 * 
 * 边界：i=m-1且target=0时，f=1
 * 入口：f(0,target,true), target∈[1,9*m]
 */
class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        string high = to_string(highLimit), low = to_string(lowLimit);
        int n = high.length();
        low = string(n - low.length(), '0') + low;
        int m = high[0] - '0' + (n - 1) * 9; // 第一位最高位只能是high[0]，其他位为[0,9]

        vector<vector<int>> memo(m, vector<int>(m + 1, -1));
        auto dfs = [&](this auto &&dfs, int i, int target, bool low_limit, bool high_limit) -> int {
            if (target < 0) {
                return 0;
            }
            if (i == n) {
                return target == 0;
            }
            if (!low_limit && !high_limit && memo[i][target] != -1) {
                return  memo[i][target];
            }
            int res = 0;
            int lo = low_limit ? low[i] - '0' : 0;
            int hi = high_limit ? high[i] - '0' : 9;
            for (int d = lo; d <= hi; d++) {
                res += dfs(i + 1, target - d, low_limit && d == lo, high_limit && d == hi);
            }
            if (!low_limit && !high_limit) {
                memo[i][target] = res;
            }
            return res;
        };

        int ans = 0;
        for (int target = 1; target <= m; target++) {
            ans = max(ans, dfs(0, target, true, true));
        }
        return ans;
    }
};
// @lc code=end

