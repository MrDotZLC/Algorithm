/*
 * @lc app=leetcode id=1898 lang=cpp
 *
 * [1898] Maximum Number of Removable Characters
 *
 * https://leetcode.com/problems/maximum-number-of-removable-characters/description/
 *
 * algorithms
 * Medium (46.03%)
 * Likes:    1036
 * Dislikes: 136
 * Total Accepted:    39K
 * Total Submissions: 84.6K
 * Testcase Example:  '"abcacb"\n"ab"\n[3,1,0]'
 *
 * You are given two strings s and p where p is a subsequence of s. You are
 * also given a distinct 0-indexed integer array removable containing a subset
 * of indices of s (s is also 0-indexed).
 * 
 * You want to choose an integer k (0 <= k <= removable.length) such that,
 * after removing k characters from s using the first k indices in removable, p
 * is still a subsequence of s. More formally, you will mark the character at
 * s[removable[i]] for each 0 <= i < k, then remove all marked characters and
 * check if p is still a subsequence.
 * 
 * Return the maximum k you can choose such that p is still a subsequence of s
 * after the removals.
 * 
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcacb", p = "ab", removable = [3,1,0]
 * Output: 2
 * Explanation: After removing the characters at indices 3 and 1, "abcacb"
 * becomes "accb".
 * "ab" is a subsequence of "accb".
 * If we remove the characters at indices 3, 1, and 0, "abcacb" becomes "ccb",
 * and "ab" is no longer a subsequence.
 * Hence, the maximum k is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcbddddd", p = "abcd", removable = [3,2,1,4,5,6]
 * Output: 1
 * Explanation: After removing the character at index 3, "abcbddddd" becomes
 * "abcddddd".
 * "abcd" is a subsequence of "abcddddd".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abcab", p = "abc", removable = [0,1,2,3,4]
 * Output: 0
 * Explanation: If you remove the first index in the array removable, "abc" is
 * no longer a subsequence.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= p.length <= s.length <= 10^5
 * 0 <= removable.length < s.length
 * 0 <= removable[i] < s.length
 * p is a subsequence of s.
 * s and p both consist of lowercase English letters.
 * The elements in removable are distinct.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        auto is_sub = [&](string &s, string &t) -> bool {
            int i = 0;
            for (char c : s) {
                if (c == t[i]) {
                    i++;
                }
                if (i == t.length()) {
                    return true;
                }
            }
            return false;
        };
        auto check = [&](int k){
            string tmp(s);
            for(int i = 0; i < k; i++){
                tmp[removable[i]] = '0';
            }
            return is_sub(tmp, p);
        };

        int L = 0;
        int R = removable.size() + 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid; 
        }
        return L;
    }
};
// @lc code=end

