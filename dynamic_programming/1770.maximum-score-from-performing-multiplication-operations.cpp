/*
 * @lc app=leetcode id=1770 lang=cpp
 *
 * [1770] Maximum Score from Performing Multiplication Operations
 *
 * https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/description/
 *
 * algorithms
 * Hard (42.39%)
 * Likes:    2588
 * Dislikes: 514
 * Total Accepted:    131.3K
 * Total Submissions: 306.5K
 * Testcase Example:  '[1,2,3]\n[3,2,1]'
 *
 * You are given two 0-indexed integer arrays nums and multipliers of size n
 * and m respectively, where n >= m.
 * 
 * You begin with a score of 0. You want to perform exactly m operations. On
 * the i^th operation (0-indexed) you will:
 * 
 * 
 * ⁠   Choose one integer x from either the start or the end of the array nums.
 * ⁠   Add multipliers[i] * x to your score.
 * ⁠   
 * ⁠       Note that multipliers[0] corresponds to the first operation,
 * multipliers[1] to the second operation, and so on.
 * ⁠   
 * ⁠   
 * ⁠   Remove x from nums.
 * 
 * 
 * Return the maximum score after performing m operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3], multipliers = [3,2,1]
 * Output: 14
 * Explanation: An optimal solution is as follows:
 * - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
 * - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
 * - Choose from the end, [1], adding 1 * 1 = 1 to the score.
 * The total score is 9 + 4 + 1 = 14.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
 * Output: 102
 * Explanation: An optimal solution is as follows:
 * - Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the
 * score.
 * - Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
 * - Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
 * - Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
 * - Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
 * The total score is 50 + 15 - 9 + 4 + 42 = 102.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * m == multipliers.length
 * 1 <= m <= 300
 * m <= n <= 10^5 
 * -1000 <= nums[i], multipliers[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
// @lc code=start
/**
 * 
 * 方法一：内存超限
 * f(i,j)表示区间[i,j]内最大分数
 * f(i,j)=max{f(i+1,j)+vi,f(i,j-1)+vj}
 * 边界：j-i+1<=n-m，f(i,j)=0
 * 入口：f(0,n-1)
 * 
 * 方法二
 * f(i,j)表示左边操作i次右边操作j次后的最大分数
 * f(i,j)=max{f(i+1,j)+vi,f(i,j+1)+vj}
 * 边界：i+j>m，f(i,j)=0
 * 入口：f(0,0)
 */
class Solution {
public:
    // 记忆化搜索：方法一
    int maximumScore1(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size(), m = multipliers.size();
        vector memo(n, vector(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) {
            if (j - i + 1 <= n - m) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            int op = n - (j - i + 1);
            res = max(dfs(i + 1, j) + multipliers[op] * nums[i],
                      dfs(i, j - 1) + multipliers[op] * nums[j]);
            return res;
        };
        return dfs(0, n - 1);
    }

    // 记忆化搜索：方法二
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size(), m = multipliers.size();
        vector memo(m + 1, vector<int>(m + 1, INT_MIN));
        function<int(int, int)> dfs = [&](int i, int j) {
            if (i + j >= m) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != INT_MIN) {
                return res;
            }
            int op = i + j;
            res = max({res, dfs(i + 1, j) + multipliers[op] * nums[i],
                       dfs(i, j + 1) +
                           multipliers[op] * nums[n - (j + 1)]});
            return res;
        };
        return dfs(0, 0);
    }
};
// @lc code=end

