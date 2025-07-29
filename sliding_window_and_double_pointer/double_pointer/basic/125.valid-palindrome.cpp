/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 *
 * https://leetcode.com/problems/valid-palindrome/description/
 *
 * algorithms
 * Easy (51.25%)
 * Likes:    10593
 * Dislikes: 8567
 * Total Accepted:    4.4M
 * Total Submissions: 8.7M
 * Testcase Example:  '"A man, a plan, a canal: Panama"'
 *
 * A phrase is a palindrome if, after converting all uppercase letters into
 * lowercase letters and removing all non-alphanumeric characters, it reads the
 * same forward and backward. Alphanumeric characters include letters and
 * numbers.
 * 
 * Given a string s, return true if it is a palindrome, or false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "race a car"
 * Output: false
 * Explanation: "raceacar" is not a palindrome.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = " "
 * Output: true
 * Explanation: s is an empty string "" after removing non-alphanumeric
 * characters.
 * Since an empty string reads the same forward and backward, it is a
 * palindrome.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2 * 10^5
 * s consists only of printable ASCII characters.
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
    bool isPalindrome(string s) {
        int l = 0, r = s.length();
        while(l < r) {
            if (!is_letter_or_dig(s[l])) {
                l++;
                continue;
            }
            if (!is_letter_or_dig(s[r])) {
                r--;
                continue;
            }
            if (transform(s[l++]) != transform(s[r--])) {
                return false;
            }
        }
        return true;
    }

    bool is_letter_or_dig(char c) {
        return (c >= '0' && c <= '9') || 
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z');
    }

    char transform(char c) {
        if (c >= 'A' && c <= 'Z') {
            return c + 32; 
        }
        return c;
    }
};
// @lc code=end

