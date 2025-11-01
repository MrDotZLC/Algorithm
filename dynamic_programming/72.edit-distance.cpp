/*
 * @lc app=leetcode id=72 lang=cpp
 *
 * [72] Edit Distance
 *
 * https://leetcode.com/problems/edit-distance/description/
 *
 * algorithms
 * Medium (59.02%)
 * Likes:    16068
 * Dislikes: 306
 * Total Accepted:    1.3M
 * Total Submissions: 2.2M
 * Testcase Example:  '"horse"\n"ros"'
 *
 * Given two strings word1 and word2, return the minimum number of operations
 * required to convert word1 to word2.
 * 
 * You have the following three operations permitted on a word:
 * 
 * 
 * Insert a character
 * Delete a character
 * Replace a character
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation: 
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation: 
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= word1.length, word2.length <= 500
 * word1 and word2 consist of lowercase English letters.
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
    // f(i,j)=f(i-1,j-1);                           (s[i] == t[j])
    //        max(f(i,j-1),f(i-1,j),f(i-1,j-1))+1;  (s[i] != t[j])

    // DP递归
    int minDistance1(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0) {
                return j + 1;
            }
            if (j < 0) {
                return i + 1;
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            if (word1[i] == word2[j]) {
                return ans = dfs(dfs, i - 1, j - 1);
            }
            return ans = min({dfs(dfs, i - 1, j), dfs(dfs, i, j - 1),
                              dfs(dfs, i - 1, j - 1)}) +
                         1;
        };
        return dfs(dfs, n - 1, m - 1);
    }

    // DP递推
    int minDistance2(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1));
        for (int j = 0; j < m; j++) {
            f[0][j + 1] = j + 1;
        }
        for (int i = 0; i < n; i++) {
            f[i + 1][0] = i + 1;
            for (int j = 0; j < m; j++) {
                if (word1[i] == word2[j]) {
                    f[i + 1][j + 1] = f[i][j];
                } else {
                    f[i + 1][j + 1] =
                        min({f[i + 1][j], f[i][j + 1], f[i][j]}) + 1;
                }
            }
        }
        return f[n][m];
    }

    // DP递推+空间优化
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> f(m + 1);
        for (int j = 0; j < m; j++) {
            f[j + 1] = j + 1;
        }
        for (char x : word1) {
            int pre = f[0];
            f[0]++;
            for (int j = 0; j < m; j++) {
                int tmp = f[j + 1];
                if (x == word2[j]) {
                    f[j + 1] = pre;
                } else {
                    f[j + 1] =
                        min({f[j], f[j + 1], pre}) + 1;
                }
                pre = tmp;
            }
        }
        return f[m];
    }
};
// @lc code=end

