/*
 * @lc app=leetcode id=2212 lang=cpp
 *
 * [2212] Maximum Points in an Archery Competition
 *
 * https://leetcode.com/problems/maximum-points-in-an-archery-competition/description/
 *
 * algorithms
 * Medium (50.62%)
 * Likes:    508
 * Dislikes: 57
 * Total Accepted:    18.6K
 * Total Submissions: 36.6K
 * Testcase Example:  '9\n[1,1,0,1,0,0,2,1,0,1,2,0]'
 *
 * Alice and Bob are opponents in an archery competition. The competition has
 * set the following rules:
 * 
 * 
 * Alice first shoots numArrows arrows and then Bob shoots numArrows
 * arrows.
 * The points are then calculated as follows:
 * 
 * The target has integer scoring sections ranging from 0 to 11
 * inclusive.
 * For each section of the target with score k (in between 0 to 11), say Alice
 * and Bob have shot ak and bk arrows on that section respectively. If ak >=
 * bk, then Alice takes k points. If ak < bk, then Bob takes k points.
 * However, if ak == bk == 0, then nobody takes k points.
 * 
 * 
 * 
 * 
 * 
 * 
 * For example, if Alice and Bob both shot 2 arrows on the section with score
 * 11, then Alice takes 11 points. On the other hand, if Alice shot 0 arrows on
 * the section with score 11 and Bob shot 2 arrows on that same section, then
 * Bob takes 11 points.
 * 
 * 
 * 
 * You are given the integer numArrows and an integer array aliceArrows of size
 * 12, which represents the number of arrows Alice shot on each scoring section
 * from 0 to 11. Now, Bob wants to maximize the total number of points he can
 * obtain.
 * 
 * Return the array bobArrows which represents the number of arrows Bob shot on
 * each scoring section from 0 to 11. The sum of the values in bobArrows should
 * equal numArrows.
 * 
 * If there are multiple ways for Bob to earn the maximum total points, return
 * any one of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
 * Output: [0,0,0,0,1,1,0,0,1,2,3,1]
 * Explanation: The table above shows how the competition is scored. 
 * Bob earns a total point of 4 + 5 + 8 + 9 + 10 + 11 = 47.
 * It can be shown that Bob cannot obtain a score higher than 47 points.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: numArrows = 3, aliceArrows = [0,0,1,0,0,0,0,0,0,0,0,2]
 * Output: [0,0,0,0,0,0,0,0,1,1,1,0]
 * Explanation: The table above shows how the competition is scored.
 * Bob earns a total point of 8 + 9 + 10 = 27.
 * It can be shown that Bob cannot obtain a score higher than 27 points.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= numArrows <= 10^5
 * aliceArrows.length == bobArrows.length == 12
 * 0 <= aliceArrows[i], bobArrows[i] <= numArrows
 * sum(aliceArrows[i]) == numArrows
 * 
 * 
 */
#include <vector>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // backtracking
    vector<int> maximumBobPoints1(int numArrows, vector<int>& aliceArrows) {
        vector<int> ans(12,0), path(12,0);
        int mx_score = 0;
        function<void(int, int, int)> dfs = [&](int i, int score, int arrows_left) {
            if (i == 12) {
                if (score > mx_score) {
                    mx_score = score;
                    ans = path;
                    ans[11] += arrows_left;
                }
                return;
            }

            path[i] = 0;
            dfs(i + 1, score, arrows_left);

            int need = aliceArrows[i] + 1;
            if (need <= arrows_left) {
                path[i] = need;
                dfs(i + 1, score + i, arrows_left - (aliceArrows[i] + 1));
                path[i] = 0;
            }
        };
        
        dfs(1, 0, numArrows);
        return ans;
    }

    // DP
    vector<int> maximumBobPoints2(int numArrows, vector<int>& aliceArrows) {
        vector<int> ans(12, 0);
        vector<vector<int>> dp(12, vector<int>(numArrows + 1, 0));
        for (int i = 1; i < 12; i++) {
            for (int j = 1; j <= numArrows; j++) {
                if (j <= aliceArrows[i]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] =
                        max(dp[i - 1][j],
                            dp[i - 1][j - aliceArrows[i] - 1] + i);
                }
            }
        }

        for (int i = 11; i > 0; i--) {
            if (dp[i][numArrows] > dp[i - 1][numArrows]) {
                ans[i] = aliceArrows[i] + 1;
                numArrows -= ans[i];
            }
        }

        ans[0] = numArrows;
        return ans;
    }

    // bit + enum
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        vector<int> ans(12, 0);
        int mx_score = 0;
        for (int i = 0; i < (1 << 12); i++) {
            int used_arrows = 0;
            int cur_score = 0;
            vector<int> path(12, 0);
            for (int j = 0; j < 12; j++) {
                if ((i >> j) & 1) {
                    used_arrows += aliceArrows[j] + 1;
                    cur_score += j;
                    path[j] = aliceArrows[j] + 1;
                }
            }

            if (used_arrows <= numArrows && cur_score > mx_score) {
                path[0] = numArrows - used_arrows;
                mx_score = cur_score;
                ans = path;
            }
        }
        return ans;
    }
};
// @lc code=end

