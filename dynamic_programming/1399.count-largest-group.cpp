/*
 * @lc app=leetcode id=1399 lang=cpp
 *
 * [1399] Count Largest Group
 *
 * https://leetcode.com/problems/count-largest-group/description/
 *
 * algorithms
 * Easy (74.94%)
 * Likes:    792
 * Dislikes: 1187
 * Total Accepted:    180.6K
 * Total Submissions: 241.7K
 * Testcase Example:  '13'
 *
 * You are given an integer n.
 * 
 * We need to group the numbers from 1 to n according to the sum of its digits.
 * For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3
 * belong to different groups.
 * 
 * Return the number of groups that have the largest size, i.e. the maximum
 * number of elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 13
 * Output: 4
 * Explanation: There are 9 groups in total, they are grouped according sum of
 * its digits of numbers from 1 to 13:
 * [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
 * There are 4 groups with largest size.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2
 * Output: 2
 * Explanation: There are 2 groups [1], [2] of size 1.
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
#include <string>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 对每个可能得组，用数位DP去计算方案数
 * f(i,target,high_limit)表示第i到m-1数位和为target的方案数
 * f(i,target,high_limit)=sum{f(i+1,target-d,high_limit&&d==hi)},
 * hi=high_limit?s[i]-'0':9, s=string(n), m=s.length, d∈[0,hi]
 * 边界：i=m-1且target=0时，f=1
 * 入口：f(0,target,true), target∈[1,9*m]
 */
class Solution {
public:
    int countLargestGroup(int n) {
        string s = to_string(n);
        int m = s.length();
        vector<vector<int>> memo(m, vector<int>((9 * m) + 1, -1));
        auto dfs = [&](this auto &&dfs, int i, int target, bool high_limit) -> int {
            if (target < 0) {
                return 0;
            }
            if (i == m) {
                return target == 0;
            }
            if (!high_limit && memo[i][target] != -1) {
                return memo[i][target];
            }
            int res = 0;
            int hi = high_limit ? s[i] - '0' : 9;
            for (int d = 0; d <= hi; d++) {
                res += dfs(i + 1, target - d, high_limit && d == hi);
            }
            if (!high_limit) {
                memo[i][target] = res;
            }
            return res;
        };
        int ans = 0, max_cnt = 0;
        for (int target = 1; target <= 9 * m; target++) {
            int cnt = dfs(0, target, true);
            if (cnt > max_cnt) {
                max_cnt = cnt;
                ans = 1;
            } else if (cnt == max_cnt) {
                ans++;
            }
        }
        return ans;
    }
};
// @lc code=end

