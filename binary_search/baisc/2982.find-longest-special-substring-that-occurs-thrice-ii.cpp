/*
 * @lc app=leetcode id=2982 lang=cpp
 *
 * [2982] Find Longest Special Substring That Occurs Thrice II
 *
 * https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-ii/description/
 *
 * algorithms
 * Medium (38.50%)
 * Likes:    390
 * Dislikes: 32
 * Total Accepted:    29.2K
 * Total Submissions: 75.9K
 * Testcase Example:  '"aaaa"'
 *
 * You are given a string s that consists of lowercase English letters.
 * 
 * A string is called special if it is made up of only a single character. For
 * example, the string "abc" is not special, whereas the strings "ddd", "zz",
 * and "f" are special.
 * 
 * Return the length of the longest special substring of s which occurs at
 * least thrice, or -1 if no special substring occurs at least thrice.
 * 
 * A substring is a contiguous non-empty sequence of characters within a
 * string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aaaa"
 * Output: 2
 * Explanation: The longest special substring which occurs thrice is "aa":
 * substrings "aaaa", "aaaa", and "aaaa".
 * It can be shown that the maximum length achievable is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcdef"
 * Output: -1
 * Explanation: There exists no special substring which occurs at least thrice.
 * Hence return -1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abcaba"
 * Output: 1
 * Explanation: The longest special substring which occurs thrice is "a":
 * substrings "abcaba", "abcaba", and "abcaba".
 * It can be shown that the maximum length achievable is 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 5 * 10^5
 * s consists of only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();
        // 分组
        auto check = [&](int k) -> bool {
            int i = 0;
            vector<int> cnt(26);
            while (i < n) {
                int count = 0, start = i;
                while (i < n && s[start] == s[i]) {
                    i++;
                }
                if (i - start >= k) {
                    count += (i - start) - k + 1;
                    cnt[s[start] - 'a'] += count;
                    if (cnt[s[start] - 'a'] >= 3) {
                        return true;
                    }
                }
            }
            return false;
        };

        int L = 0, R = n - 1;
        while (L + 1 < R) {
            int k = L + (R - L) / 2;
            (check(k) ? L : R) = k;
        }
        return L ? L : -1;
    }
};
// @lc code=end

int main() {
    Solution sol;
    string s = "aaaa";
    sol.maximumLength(s);
}