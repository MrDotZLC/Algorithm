/*
 * @lc app=leetcode id=1307 lang=cpp
 *
 * [1307] Verbal Arithmetic Puzzle
 *
 * https://leetcode.com/problems/verbal-arithmetic-puzzle/description/
 *
 * algorithms
 * Hard (34.79%)
 * Likes:    523
 * Dislikes: 136
 * Total Accepted:    16.7K
 * Total Submissions: 48K
 * Testcase Example:  '["SEND","MORE"]\n"MONEY"'
 *
 * Given an equation, represented by words on the left side and the result on
 * the right side.
 * 
 * You need to check if the equation is solvable under the following
 * rules:
 * 
 * 
 * Each character is decoded as one digit (0 - 9).
 * No two characters can map to the same digit.
 * Each words[i] and result are decoded as one number without leading
 * zeros.
 * Sum of numbers on the left side (words) will equal to the number on the
 * right side (result).
 * 
 * 
 * Return true if the equation is solvable, otherwise return false.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["SEND","MORE"], result = "MONEY"
 * Output: true
 * Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8,
 * 'Y'->'2'
 * Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
 * Output: true
 * Explanation: Map 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1,
 * 'W'->'3', 'Y'->4
 * Such that: "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 =
 * 138214
 * 
 * Example 3:
 * 
 * 
 * Input: words = ["LEET","CODE"], result = "POINT"
 * Output: false
 * Explanation: There is no possible mapping to satisfy the equation, so we
 * return false.
 * Note that two different characters cannot map to the same digit.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= words.length <= 5
 * 1 <= words[i].length, result.length <= 7
 * words[i], result contain only uppercase English letters.
 * The number of different characters used in the expression is at most 10.
 * 
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isSolvable(vector<string>& words, string result) {
        vector<int> used(10, 0), weights(26, 0), not_zero(26, 0), chars;
        for (string &w : words) {
            int pos = 1;
            for (int i = w.length() - 1; i >= 0; i--) {
                chars.push_back(w[i] - 'A');
                weights[w[i] - 'A'] += pos;
                pos *= 10;
            }
            if (w.length() > 1) {
                not_zero[w[0] - 'A'] = 1;
            }
        }
        int pos = 1;
        for (int i = result.length() - 1; i >= 0; i--) {
            chars.push_back(result[i] - 'A');
            weights[result[i] - 'A'] -= pos;
            pos *= 10;
        }
        if (result.length() > 1) {
            not_zero[result[0] - 'A'] = 1;
        }
        ranges::sort(chars);
        chars.erase(unique(chars.begin(), chars.end()), chars.end());
        int n = chars.size();
        auto dfs = [&](auto &dfs, int i, int sum) -> bool {
            if (i == n) {
                return sum == 0;
            }

            for (int j = 0; j < 10; j++) {
                if (used[j] || j == 0 && not_zero[i]) {
                    continue;
                }
                used[j] = 1;
                if (dfs(dfs, i + 1, sum + j * weights[chars[i]])) {
                    return true;
                }
                used[j] = 0;
            }
            return false;
        };

        return dfs(dfs, 0, 0);
    }
};
// @lc code=end

