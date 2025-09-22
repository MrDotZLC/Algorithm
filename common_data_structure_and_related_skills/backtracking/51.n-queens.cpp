/*
 * @lc app=leetcode id=51 lang=cpp
 *
 * [51] N-Queens
 *
 * https://leetcode.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (73.24%)
 * Likes:    13750
 * Dislikes: 332
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n
 * chessboard such that no two queens attack each other.
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * You may return the answer in any order.
 * 
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space,
 * respectively.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as
 * shown above
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: [["Q"]]
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
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> path(n, -1);
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                vector<string> res;
                string s(n, '.');
                for (int i : path) {
                    s[i] = 'Q';
                    res.push_back(s);
                    s[i] = '.';
                }
                ans.push_back(res);
            }

            for (int j = 0; j < n; j++) {
                bool can_arrange = true;
                for (int row = 0; row < i; row++) {
                    int col = path[row];
                    if (col == j || abs(i - row) == abs(j - col)) {
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

