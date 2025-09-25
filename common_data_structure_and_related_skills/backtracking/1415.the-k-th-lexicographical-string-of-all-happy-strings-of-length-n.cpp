/*
 * @lc app=leetcode id=1415 lang=cpp
 *
 * [1415] The k-th Lexicographical String of All Happy Strings of Length n
 *
 * https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/description/
 *
 * algorithms
 * Medium (85.14%)
 * Likes:    1521
 * Dislikes: 45
 * Total Accepted:    177.8K
 * Total Submissions: 208.8K
 * Testcase Example:  '1\n3'
 *
 * A happy string is a string that:
 * 
 * 
 * consists only of letters of the set ['a', 'b', 'c'].
 * s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is
 * 1-indexed).
 * 
 * 
 * For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings
 * and strings "aa", "baa" and "ababbc" are not happy strings.
 * 
 * Given two integers n and k, consider a list of all happy strings of length n
 * sorted in lexicographical order.
 * 
 * Return the kth string of this list or return an empty string if there are
 * less than k happy strings of length n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1, k = 3
 * Output: "c"
 * Explanation: The list ["a", "b", "c"] contains all happy strings of length
 * 1. The third string is "c".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1, k = 4
 * Output: ""
 * Explanation: There are only 3 happy strings of length 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, k = 9
 * Output: "cab"
 * Explanation: There are 12 different happy string of length 3 ["aba", "abc",
 * "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You
 * will find the 9^th string = "cab"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10
 * 1 <= k <= 100
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
    string getHappyString(int n, int k) {
        int m = 3 * (1 << (n - 1));
        if (m < k) {
            return "";
        }
        string ans, path(n, 'c');
        bool more_half = 2 * k > m;
        k = more_half ? m - k + 1 : k;
        auto dfs = [&](auto &dfs, int i) -> bool {
            if (i == n) {
                if (--k == 0) {
                    ans = path;
                    return true;
                }
                return false;
            }

            if (more_half) {
                for (int j = 'c'; j >= 'a'; j--) {
                    if (i > 0 && path[i - 1] == j) {
                        continue;
                    }
                    path[i] = j;
                    if (dfs(dfs, i + 1)) {
                        return true;
                    }
                }
            } else {
                for (int j = 'a'; j <= 'c'; j++) {
                    if (i > 0 && path[i - 1] == j) {
                        continue;
                    }
                    path[i] = j;
                    if (dfs(dfs, i + 1)) {
                        return true;
                    }
                }
            }

            return false;
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

