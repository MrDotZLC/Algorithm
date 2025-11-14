/*
 * @lc app=leetcode id=1312 lang=cpp
 *
 * [1312] Minimum Insertion Steps to Make a String Palindrome
 *
 * https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
 *
 * algorithms
 * Hard (72.78%)
 * Likes:    5492
 * Dislikes: 75
 * Total Accepted:    280.5K
 * Total Submissions: 382.6K
 * Testcase Example:  '"zzazz"'
 *
 * Given a string s. In one step you can insert any character at any index of
 * the string.
 * 
 * Return the minimum number of steps to make s palindrome.
 * 
 * A Palindrome String is one that reads the same backward as well as
 * forward.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "zzazz"
 * Output: 0
 * Explanation: The string "zzazz" is already palindrome we do not need any
 * insertions.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "mbadm"
 * Output: 2
 * Explanation: String can be "mbdadbm" or "mdbabdm".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "leetcode"
 * Output: 5
 * Explanation: Inserting 5 characters the string becomes "leetcodocteel".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 500
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 求n-最长回文子序列
 * f(i,j)表示区间[i,j]范围内需要插入的次数
 * 如果s[i]=s[j]，无需操作，f(i,j)=f(i+1,j-1)
 *     s[i]!=s[j]，考虑在左边插入还是右边，取最小值+1，即f(i,j)=min(f(i,j-1), f(i+1,j)) + 1
 * 边界：
 * i==j时，单个字符是回文的，无需操作，返回0
 * i+1==j且s[i]==s[j]时，两个相邻相同字符是回文的，返回0
 * i+1==j且s[i]!=s[j]时，两个相邻不同字符需要插入一个字符使它们回文，返回1
 */
class Solution {
public:
    // 记忆化递归
    int minInsertions1(string s) {
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i + 1 >= j) {
                return s[i] != s[j];
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            if (s[i] == s[j]) {
                res = dfs(i + 1, j - 1);
            } else {
                res = min(dfs(i, j - 1), dfs(i + 1, j)) + 1;
            }
            return res;
        };
        return dfs(0, n - 1);
    }

    // DP+空间优化
    int minInsertions(string s) {
        int n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--) {
            int pre = 0; // 存放f[i+1][j-1]
            for (int j = i + 1; j < n; j++) {
                int tmp = f[j];
                if (s[i] == s[j]) {
                    f[j] = pre;
                } else {
                    f[j] = min(f[j - 1], f[j]) + 1;
                }
                pre = tmp;
            }
        }
        return f[n - 1];
    }
};
// @lc code=end

