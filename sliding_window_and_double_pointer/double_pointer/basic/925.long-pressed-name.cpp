/*
 * @lc app=leetcode id=925 lang=cpp
 *
 * [925] Long Pressed Name
 *
 * https://leetcode.com/problems/long-pressed-name/description/
 *
 * algorithms
 * Easy (32.58%)
 * Likes:    2546
 * Dislikes: 399
 * Total Accepted:    174.5K
 * Total Submissions: 535.2K
 * Testcase Example:  '"alex"\n"aaleex"'
 *
 * Your friend is typing his name into a keyboard. Sometimes, when typing a
 * character c, the key might get long pressed, and the character will be typed
 * 1 or more times.
 * 
 * You examine the typed characters of the keyboard. Return True if it is
 * possible that it was your friends name, with some characters (possibly none)
 * being long pressed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: name = "alex", typed = "aaleex"
 * Output: true
 * Explanation: 'a' and 'e' in 'alex' were long pressed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: name = "saeed", typed = "ssaaedd"
 * Output: false
 * Explanation: 'e' must have been pressed twice, but it was not in the typed
 * output.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= name.length, typed.length <= 1000
 * name and typed consist of only lowercase English letters.
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
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (i < name.size() && j < typed.size()) {
            if (name[i] == typed[j]) {
                i++;
                j++;
            } else {
                if (j == 0) {
                    return false;
                }
                while (j < typed.size() && typed[j] == typed[j - 1]) {
                    j++;
                }
                if (name[i] == typed[j]) {
                    i++;
                    j++;
                } else {
                    return false;
                }
            }
        }

        if (i < name.size()) {
            return false;
        }

        while (j < typed.size()) {
            if (typed[j] == typed[j - 1]) {
                j++;
            } else {
                return false;
            }
        }

        return true;
    }
};
// @lc code=end

