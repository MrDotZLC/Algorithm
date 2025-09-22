/*
 * @lc app=leetcode id=52 lang=cpp
 *
 * [52] N-Queens II
 *
 * https://leetcode.com/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (76.95%)
 * Likes:    4163
 * Dislikes: 279
 * Total Accepted:    529.6K
 * Total Submissions: 684.5K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n
 * chessboard such that no two queens attack each other.
 * 
 * Given an integer n, return the number of distinct solutions to the n-queens
 * puzzle.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4
 * Output: 2
 * Explanation: There are two distinct solutions to the 4-queens puzzle as
 * shown.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 9
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int totalNQueens(int n) {
        int ans = 0;
        vector<int> path(n, -1);
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans++;
            }

            for (int j = 0; j < n; j++) {
                bool can_arrange = true;
                for (int row = 0; row < i; row++) {
                    int col = path[row];
                    if (j == col || abs(i - row) == abs(j - col)) {
                        can_arrange = false;
                        break;
                    }
                }
                if (can_arrange) {
                    path[i] = j;
                    dfs(dfs, i + 1);
                    path[i] = -1;
                }
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

