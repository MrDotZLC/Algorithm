/*
 * @lc app=leetcode id=132 lang=cpp
 *
 * [132] Palindrome Partitioning II
 *
 * https://leetcode.com/problems/palindrome-partitioning-ii/description/
 *
 * algorithms
 * Hard (35.46%)
 * Likes:    5817
 * Dislikes: 156
 * Total Accepted:    375.4K
 * Total Submissions: 1M
 * Testcase Example:  '"aab"'
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 * 
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using
 * 1 cut.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "a"
 * Output: 0
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "ab"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2000
 * s consists of lowercase English letters only.
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        vector pal_memo(n, vector<int>(n, -1));
        auto is_palindrome = [&](this auto &&is_palindrome, int l, int r) -> bool {
            if (l >= r) {
                return true;
            }
            int &res = pal_memo[l][r];
            if (res != -1) {
                return res;
            }
            return res = s[l] == s[r] && is_palindrome(l + 1, r - 1);
        };

        vector<int> dfs_memo(n, INT_MAX); // INT_MAX 表示没有计算过
        auto dfs = [&](this auto && dfs, int r) -> int {
            if (is_palindrome(0, r)) {
                return 0;
            }
            int &res = dfs_memo[r];
            if (res != INT_MAX) {
                return res;
            }
            for (int l = 1; l <= r; l++) {
                if (is_palindrome(l, r)) {
                    res = min(res, dfs(l - 1) + 1);
                }
            }
            return res;
        };
        return dfs(n - 1);
    }
};
// @lc code=end

