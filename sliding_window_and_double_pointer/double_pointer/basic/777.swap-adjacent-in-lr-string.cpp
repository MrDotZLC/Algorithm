/*
 * @lc app=leetcode id=777 lang=cpp
 *
 * [777] Swap Adjacent in LR String
 *
 * https://leetcode.com/problems/swap-adjacent-in-lr-string/description/
 *
 * algorithms
 * Medium (37.57%)
 * Likes:    1300
 * Dislikes: 947
 * Total Accepted:    89K
 * Total Submissions: 236.9K
 * Testcase Example:  '"RXXLRXRXL"\n"XRLXXRRLX"'
 *
 * In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a
 * move consists of either replacing one occurrence of "XL" with "LX", or
 * replacing one occurrence of "RX" with "XR". Given the starting string start
 * and the ending string result, return True if and only if there exists a
 * sequence of moves to transform start to result.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: start = "RXXLRXRXL", result = "XRLXXRRLX"
 * Output: true
 * Explanation: We can transform start to result following these steps:
 * RXXLRXRXL ->
 * XRXLRXRXL ->
 * XRLXRXRXL ->
 * XRLXXRRXL ->
 * XRLXXRRLX
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: start = "X", result = "L"
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= start.length <= 10^4
 * start.length == result.length
 * Both start and result will only consist of characters in 'L', 'R', and 'X'.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool canTransform(string start, string result) {
        string s = start, r = result;
        s.erase(remove(s.begin(), s.end(), 'X'), s.end());
        r.erase(remove(r.begin(), r.end(), 'X'), r.end());
        if (s != r) {
            return false;
        }
        int i = 0, j = 0;
        while (i < start.length() && j < result.length()) {
            while (start[i] == 'X') {
                i++;
            }
            while (result[j] == 'X') {
                j++;
            }
            if (i != j && (start[i] == 'L') == (i < j)) {
                return false;
            }
            i++;
            j++;
        }
        return true;
    }
};
// @lc code=end

