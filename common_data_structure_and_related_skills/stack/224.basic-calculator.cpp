/*
 * @lc app=leetcode id=224 lang=cpp
 *
 * [224] Basic Calculator
 *
 * https://leetcode.com/problems/basic-calculator/description/
 *
 * algorithms
 * Hard (45.78%)
 * Likes:    6793
 * Dislikes: 547
 * Total Accepted:    643.3K
 * Total Submissions: 1.4M
 * Testcase Example:  '"1 + 1"'
 *
 * Given a string s representing a valid expression, implement a basic
 * calculator to evaluate it, and return the result of the evaluation.
 * 
 * Note: You are not allowed to use any built-in function which evaluates
 * strings as mathematical expressions, such as eval().
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "1 + 1"
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = " 2-1 + 2 "
 * Output: 3
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 3 * 10^5
 * s consists of digits, '+', '-', '(', ')', and ' '.
 * s represents a valid expression.
 * '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is
 * invalid).
 * '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is
 * valid).
 * There will be no two consecutive operators in the input.
 * Every number and running calculation will fit in a signed 32-bit integer.
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
    int calculate(string s) {
        vector<pair<int, int>> stk;
        int sum = 0;
        int num = 0;
        int op = '+';
        for (char c : s) {
            if (isspace(c)) {
                continue;
            } else if (isdigit(c)) {
                num = num * 10 + (c - 48);
            } else if (c == '(') {
                stk.emplace_back(sum, op);
                sum = 0;
                op = '+';
            } else if (c == ')') {
                sum = (op == '+') ? sum + num : sum - num;
                num = sum;

                auto &[pre_sum, pre_op] = stk.back();
                sum = (pre_op == '+') ? pre_sum + num : pre_sum - num;
                num = 0;
                op = '+';
                stk.pop_back(); // 引用还在用，不能提前pop释放资源
            } else {
                sum = (op == '+') ? sum + num : sum - num;
                num = 0;
                op = c;
            }
        }

        sum = (op == '+') ? sum + num : sum - num;

        return sum;
    }
};
// @lc code=end

