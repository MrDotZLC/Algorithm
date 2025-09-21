/*
 * @lc app=leetcode id=301 lang=cpp
 *
 * [301] Remove Invalid Parentheses
 *
 * https://leetcode.com/problems/remove-invalid-parentheses/description/
 *
 * algorithms
 * Hard (49.31%)
 * Likes:    6020
 * Dislikes: 300
 * Total Accepted:    487.1K
 * Total Submissions: 985.2K
 * Testcase Example:  '"()())()"'
 *
 * Given a string s that contains parentheses and letters, remove the minimum
 * number of invalid parentheses to make the input string valid.
 * 
 * Return a list of unique strings that are valid with the minimum number of
 * removals. You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "()())()"
 * Output: ["(())()","()()()"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "(a)())()"
 * Output: ["(a())()","(a)()()"]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = ")("
 * Output: [""]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 25
 * s consists of lowercase English letters and parentheses '(' and ')'.
 * There will be at most 20 parentheses in s.
 * 
 * 
 */
#include <string>
#include <vector>
#include<unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> ans;
        int l_num = 0;
        int r_num = 0;
        for (char c : s) {
            if (c == '(') {
                l_num++;
            } else if (c == ')') {
                if (l_num == 0) {
                    r_num++;
                } else {
                    l_num--;
                }
            }
        }

        auto dfs = [&](auto &dfs, string ss, int pos, int l, int r) -> void {
            if (l == 0 && r == 0) {
                if (check(ss)) {
                    ans.insert(ss);
                }
                return;
            }

            for (int i = pos; i < ss.size(); i++) {
                if (i > pos && ss[i] == ss[i - 1]) {
                    continue;
                }
                if (l > 0 && ss[i] == '(') {
                    string t = ss;
                    t.erase(i, 1);
                    dfs(dfs, t, i, l - 1, r); // 长度-1，所以pos不变
                }
                if (r > 0 && ss[i] == ')') {
                    string t = ss;
                    t.erase(i, 1);
                    dfs(dfs, t, i, l, r - 1);
                }
            }
        };

        dfs(dfs, s, 0, l_num, r_num);
        return vector<string>(ans.begin(), ans.end());
    }

    bool check(string &s) {
        int cnt = 0;
        for (char c : s) {
            if (c == '(') {
                cnt++;
            }
            if (c == ')') {
                cnt--;
                if (cnt < 0) {
                    return false;
                }
            }
        }
        return cnt == 0;
    }
};
// @lc code=end

