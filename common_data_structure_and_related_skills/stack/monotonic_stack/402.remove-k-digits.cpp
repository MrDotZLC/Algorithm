/*
 * @lc app=leetcode id=402 lang=cpp
 *
 * [402] Remove K Digits
 *
 * https://leetcode.com/problems/remove-k-digits/description/
 *
 * algorithms
 * Medium (35.20%)
 * Likes:    10296
 * Dislikes: 538
 * Total Accepted:    661.4K
 * Total Submissions: 1.8M
 * Testcase Example:  '"1432219"\n3'
 *
 * Given string num representing a non-negative integer num, and an integer k,
 * return the smallest possible integer after removing k digits from num.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: num = "1432219", k = 3
 * Output: "1219"
 * Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219
 * which is the smallest.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: num = "10200", k = 1
 * Output: "200"
 * Explanation: Remove the leading 1 and the number is 200. Note that the
 * output must not contain leading zeroes.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: num = "10", k = 2
 * Output: "0"
 * Explanation: Remove all the digits from the number and it is left with
 * nothing which is 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= num.length <= 10^5
 * num consists of only digits.
 * num does not have any leading zeros except for the zero itself.
 * 
 * 
 */
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans;
        for (char v : num) {
            while (ans.size() && k && ans.back() > v) {
                ans.pop_back();
                k--;
            }
            if (ans.size() == 0 && v == '0') {
                continue;
            }
            ans += v;
        }
        while (k && ans.size()) {
            ans.pop_back();
            k--;
        }
        return ans == "" ? "0" : ans;
    }
};
// @lc code=end

