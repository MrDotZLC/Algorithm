/*
 * @lc app=leetcode id=17 lang=cpp
 *
 * [17] Letter Combinations of a Phone Number
 *
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (64.10%)
 * Likes:    20258
 * Dislikes: 1104
 * Total Accepted:    2.7M
 * Total Submissions: 4.2M
 * Testcase Example:  '"23"'
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer in
 * any order.
 * 
 * A mapping of digits to letters (just like on the telephone buttons) is given
 * below. Note that 1 does not map to any letters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: digits = ""
 * Output: []
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: digits = "2"
 * Output: ["a","b","c"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= digits.length <= 4
 * digits[i] is a digit in the range ['2', '9'].
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        int n = digits.length();
        if (n == 0) {
            return {};
        }

        vector<string> ans;
        string path(n, 0);

        auto dfs = [&](this auto &&dfs, int i) -> void {
            if (i == n) {
                ans.emplace_back(path);
                return;
            }
            for (char c : MAPPING[digits[i] - '0']) {
                path[i] = c;
                dfs(i + 1);
            }
        };
        dfs(0);
        return ans;
    }
private:
    string MAPPING[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};
// @lc code=end

