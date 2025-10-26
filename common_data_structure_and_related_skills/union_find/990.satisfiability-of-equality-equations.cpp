/*
 * @lc app=leetcode id=990 lang=cpp
 *
 * [990] Satisfiability of Equality Equations
 *
 * https://leetcode.com/problems/satisfiability-of-equality-equations/description/
 *
 * algorithms
 * Medium (51.10%)
 * Likes:    3963
 * Dislikes: 67
 * Total Accepted:    157.4K
 * Total Submissions: 306.6K
 * Testcase Example:  '["a==b","b!=a"]'
 *
 * You are given an array of strings equations that represent relationships
 * between variables where each string equations[i] is of length 4 and takes
 * one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are
 * lowercase letters (not necessarily different) that represent one-letter
 * variable names.
 * 
 * Return true if it is possible to assign integers to variable names so as to
 * satisfy all the given equations, or false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: equations = ["a==b","b!=a"]
 * Output: false
 * Explanation: If we assign say, a = 1 and b = 1, then the first equation is
 * satisfied, but not the second.
 * There is no way to assign the variables to satisfy both equations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: equations = ["b==a","a==b"]
 * Output: true
 * Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= equations.length <= 500
 * equations[i].length == 4
 * equations[i][0] is a lowercase letter.
 * equations[i][1] is either '=' or '!'.
 * equations[i][2] is '='.
 * equations[i][3] is a lowercase letter.
 * 
 * 
 */
#include <vector>
#include <numeric>
#include <functional>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 排序+并查集，相较于两次遍历，并查集find/union操作次数相同，多出了排序耗时
    bool equationsPossible1(vector<string>& equations) {
        vector<int> p(26);
        ranges::iota(p, 0);
        function<int(int)> find = [&](int x) {
            return x == p[x] ? x : p[x] = find(p[x]);
        };

        ranges::sort(equations, [](const string& a, const string& b){
            if (a[1] == b[1]) {
                return a[0] < b[0];
            } else {
                return b[1] == '!';
            }
        });

        for (auto& s : equations) {
            if (s[1] == '=') {
                int x = find(s[0] - 'a'), y = find(s[3] - 'a');
                if (x != y) {
                    if (s[0] < s[3]) {
                        swap(x, y);
                    }
                    p[x] = y;
                }
            } else if (find(s[0] - 'a') == find(s[3] - 'a')) {
                return false;
            }
        }

        return true;
    }

    // 并查集+遍历2遍
    bool equationsPossible(vector<string>& equations) {
        vector<int> p(26);
        ranges::iota(p, 0);
        function<int(int)> find = [&](int x) {
            return x == p[x] ? x : p[x] = find(p[x]);
        };
        for (auto& s : equations) {
            if (s[1] == '=') {
                int x = find(s[0] - 'a'), y = find(s[3] - 'a');
                if (x != y) {
                    if (s[0] < s[3]) {
                        swap(x, y);
                    }
                    p[x] = y;
                }
            }
        }
        for (auto& s : equations) {
            if (s[1] != '=' && find(s[0] - 'a') == find(s[3] - 'a')) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

