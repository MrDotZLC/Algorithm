/*
 * @lc app=leetcode id=744 lang=cpp
 *
 * [744] Find Smallest Letter Greater Than Target
 *
 * https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/
 *
 * algorithms
 * Easy (54.26%)
 * Likes:    4718
 * Dislikes: 2215
 * Total Accepted:    620.6K
 * Total Submissions: 1.1M
 * Testcase Example:  '["c","f","j"]\n"a"'
 *
 * You are given an array of characters letters that is sorted in
 * non-decreasing order, and a character target. There are at least two
 * different characters in letters.
 * 
 * Return the smallest character in letters that is lexicographically greater
 * than target. If such a character does not exist, return the first character
 * in letters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: letters = ["c","f","j"], target = "a"
 * Output: "c"
 * Explanation: The smallest character that is lexicographically greater than
 * 'a' in letters is 'c'.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: letters = ["c","f","j"], target = "c"
 * Output: "f"
 * Explanation: The smallest character that is lexicographically greater than
 * 'c' in letters is 'f'.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: letters = ["x","x","y","y"], target = "z"
 * Output: "x"
 * Explanation: There are no characters in letters that is lexicographically
 * greater than 'z' so we return letters[0].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= letters.length <= 10^4
 * letters[i] is a lowercase English letter.
 * letters is sorted in non-decreasing order.
 * letters contains at least two different characters.
 * target is a lowercase English letter.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int pos = lower_bound(letters, target + 1);
        if (pos == letters.size() || letters[pos] <= target) {
            return letters[0];
        } else {
            return letters[pos];
        }
    }

    int lower_bound(vector<char>& letters, char target) {
        int L = -1, R = letters.size();
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            if (letters[mid] < target) {
                L = mid;
            } else {    
                R = mid;
            }

        }
        return L + 1;
    }
};
// @lc code=end

