/*
 * @lc app=leetcode id=828 lang=cpp
 *
 * [828] Count Unique Characters of All Substrings of a Given String
 *
 * https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/description/
 *
 * algorithms
 * Hard (52.95%)
 * Likes:    2235
 * Dislikes: 254
 * Total Accepted:    81.6K
 * Total Submissions: 153.2K
 * Testcase Example:  '"ABC"'
 *
 * Let's define a function countUniqueChars(s) that returns the number of
 * unique characters in s.
 * 
 * 
 * For example, calling countUniqueChars(s) if s = "LEETCODE" then "L", "T",
 * "C", "O", "D" are the unique characters since they appear only once in s,
 * therefore countUniqueChars(s) = 5.
 * 
 * 
 * Given a string s, return the sum of countUniqueChars(t) where t is a
 * substring of s. The test cases are generated such that the answer fits in a
 * 32-bit integer.
 * 
 * Notice that some substrings can be repeated so in this case you have to
 * count the repeated ones too.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ABC"
 * Output: 10
 * Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
 * Every substring is composed with only unique letters.
 * Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "ABA"
 * Output: 8
 * Explanation: The same as example 1, except countUniqueChars("ABA") = 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "LEETCODE"
 * Output: 92
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of uppercase English letters only.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int uniqueLetterString(string s) {
        vector<int> last0(26, -1), last1(26, -1);
        int ans = 0, sum = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i] - 'A';
            sum += i - last1[c] * 2 + last0[c];
            ans += sum;
            last0[c] = last1[c];
            last1[c] = i;
        }
        return ans;
    }
};
// @lc code=end

