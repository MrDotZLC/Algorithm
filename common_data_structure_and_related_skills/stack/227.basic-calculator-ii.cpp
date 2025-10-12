/*
 * @lc app=leetcode id=227 lang=cpp
 *
 * [227] Basic Calculator II
 *
 * https://leetcode.com/problems/basic-calculator-ii/description/
 *
 * algorithms
 * Medium (45.97%)
 * Likes:    6500
 * Dislikes: 946
 * Total Accepted:    886.3K
 * Total Submissions: 1.9M
 * Testcase Example:  '"3+2*2"'
 *
 * Given a string s which represents an expression, evaluate this expression
 * and return its value. 
 * 
 * The integer division should truncate toward zero.
 * 
 * You may assume that the given expression is always valid. All intermediate
 * results will be in the range of [-2^31, 2^31 - 1].
 * 
 * Note: You are not allowed to use any built-in function which evaluates
 * strings as mathematical expressions, such as eval().
 * 
 * 
 * Example 1:
 * Input: s = "3+2*2"
 * Output: 7
 * Example 2:
 * Input: s = " 3/2 "
 * Output: 1
 * Example 3:
 * Input: s = " 3+5 / 2 "
 * Output: 5
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 3 * 10^5
 * s consists of integers and operators ('+', '-', '*', '/') separated by some
 * number of spaces.
 * s represents a valid expression.
 * All the integers in the expression are non-negative integers in the range
 * [0, 2^31 - 1].
 * The answer is guaranteed to fit in a 32-bit integer.
 * 
 * 
 */
#include <vector>
#include <string>
#include <cctype>
using namespace std;
// @lc code=start
class Solution {
public:
    public:
    int calculate(const string& s) {
        int idx = 0;
        return helper(s, idx);
    }

private:
    int helper(const string& s, int& i) {
        vector<int> stk;
        int num = 0;
        char op = '+';

        while (i < s.size()) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            else if (c == '(') {
                i++; // 跳过 '('
                num = helper(s, i); // 递归计算括号内
            }

            if ((!isdigit(c) && !isspace(c)) || i == s.size() - 1) {
                switch(op) {
                    case '+': stk.push_back(num); break;
                    case '-': stk.push_back(-num); break;
                    case '*': {
                        int temp = stk.back(); stk.pop_back();
                        stk.push_back(temp * num);
                        break;
                    }
                    case '/': {
                        int temp = stk.back(); stk.pop_back();
                        stk.push_back(temp / num);
                        break;
                    }
                }
                op = c;
                num = 0;
            }

            if (c == ')') {
                i++; // 跳过 ')'
                break; // 返回本层结果
            }
            i++;
        }

        int sum = 0;
        while (!stk.empty()) {
            sum += stk.back();
            stk.pop_back();
        }
        return sum;
    }
};
// @lc code=end

