/*
 * @lc app=leetcode id=730 lang=cpp
 *
 * [730] Count Different Palindromic Subsequences
 *
 * https://leetcode.com/problems/count-different-palindromic-subsequences/description/
 *
 * algorithms
 * Hard (46.56%)
 * Likes:    1995
 * Dislikes: 103
 * Total Accepted:    43.6K
 * Total Submissions: 92.5K
 * Testcase Example:  '"bccb"'
 *
 * Given a string s, return the number of different non-empty palindromic
 * subsequences in s. Since the answer may be very large, return it modulo 10^9
 * + 7.
 * 
 * A subsequence of a string is obtained by deleting zero or more characters
 * from the string.
 * 
 * A sequence is palindromic if it is equal to the sequence reversed.
 * 
 * Two sequences a1, a2, ... and b1, b2, ... are different if there is some i
 * for which ai != bi.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "bccb"
 * Output: 6
 * Explanation: The 6 different non-empty palindromic subsequences are 'b',
 * 'c', 'bb', 'cc', 'bcb', 'bccb'.
 * Note that 'bcb' is counted only once, even though it occurs twice.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s =
 * "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"
 * Output: 104860361
 * Explanation: There are 3104860382 different non-empty palindromic
 * subsequences, which is 104860361 modulo 10^9 + 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s[i] is either 'a', 'b', 'c', or 'd'.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 方法一：
 * f(i,j)表示下标[i,j]范围内，回文子序列的个数
 * 枚举每个字母作为边界字符对f(i,j)的贡献，累加就是f(i,j)，不存在重复序列
 * 在枚举i和j的过程中，统计每个字母在区间内出现的最左l和最右r位置
 * 若字符c不存在于区间内，则贡献为0
 * 若字符c只有一个，则贡献为1
 * 若字符c个数至少有2个，则贡献为f(l+1,r-1)+2，2是指c和cc的贡献
 * 
 * 方法二：
 * 考虑s[i]和s[j]对整个序列的贡献
 * s[i]=s[j]且[i+1,j-1]中无s[i]：
 *          每个已有子回文序列都能生成一个新的回文子序列，额外贡献c和cc，则f(i,j)=2*f(i+1,j-1)+2
 * s[i]=s[j]且[i+1,j-1]中s[i]有1个：
 *          每个已有子回文序列都能生成一个新的回文子序列，额外贡献cc，则f(i,j)=2*f(i+1,j-1)+1
 * s[i]=s[j]且[i+1,j-1]中s[i]有至少2个：
 *          每个已有子回文序列都能生成一个新的回文子序列，减去重复贡献f[l+1,r-1]，则f(i,j)=2*f(i+1,j-1)+1
 * 
 * s[i]!=s[j]：
 *          分别贡献f(i+1,j)和f(i,j-1)，减去重复贡献f(i+1,j-1)，则f(i,j)=f(i+1,j)+f(i,j-1)-f(i+1,j-1)
 */
class Solution {
public:
    const int MOD = 1e9+7;
    // DP（方法一）
    int countPalindromicSubsequences(string s) {
        int n = s.length();
        vector<vector<int>> f(n, vector<int>(n));
        vector<int> left(4), right(4);
        fill(left.begin(), left.end(), -1); // 初始化为-1
        for (int i = n - 1; i >= 0; i--) { // f[i]由f[l+1]转移而来，依赖高下标数据，则倒序遍历
            left[s[i] - 'a'] = i;
            fill(right.begin(), right.end(), -1); // 清空旧数据
            for (int j = i; j < n; j++) { // f[i][j]从f[i][r-1]转移而来，依赖低下标数据，则正序遍历
                right[s[j] - 'a'] = j;
                for (int k = 0; k < 4; k++) {
                    int l = left[k], r = right[k];
                    if (l == -1 || r == -1) {
                        continue;
                    }
                    if (l == r) {
                        f[i][j] = (f[i][j] + 1) % MOD;
                    } else {
                        f[i][j] = (f[i][j] + f[l + 1][r - 1] + 2) % MOD;
                    }
                }
            }
        }
        return f[0][n - 1];
    }
};
// @lc code=end

