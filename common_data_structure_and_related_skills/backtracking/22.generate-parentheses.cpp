/*
 * @lc app=leetcode id=22 lang=cpp
 *
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (77.35%)
 * Likes:    22649
 * Dislikes: 1057
 * Total Accepted:    2.6M
 * Total Submissions: 3.3M
 * Testcase Example:  '3'
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * 
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 8
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> generateParenthesis1(int n) {
        vector<string> ans;
        string s(n * 2, ')');
        
        auto dfs = [&](auto &dfs, int l, int r) -> void {
            if (r == n) {
                ans.push_back(s);
                return;
            }

            if (l < n) {
                s[l + r] = '(';
                dfs(dfs, l + 1, r);
            }

            if (r < l) {
                s[l + r] = ')';
                dfs(dfs, l, r + 1);
            }
        };

        dfs(dfs, 0, 0);
        return ans;
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        vector<int> combi;
        
        auto dfs = [&](auto &dfs, int i, int balance) -> void {
            if (combi.size() == n) {
                string s(n * 2, ')');
                for (int i : combi) {
                    s[i] = '(';
                }
                ans.push_back(s);
                return;
            }

            for (int r = 0; r <= balance; r++) {
                combi.push_back(i + r);
                dfs(dfs, i + r + 1, balance - r + 1);
                combi.pop_back();
            }
        };

        dfs(dfs, 0, 0);
        return ans;
    }
};
// @lc code=end

