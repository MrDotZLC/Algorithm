/*
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (36.05%)
 * Likes:    31809
 * Dislikes: 1965
 * Total Accepted:    4.3M
 * Total Submissions: 11.7M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, return the longest palindromic substring in s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "cbbd"
 * Output: "bb"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s consist of only digits and English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
/**
 * 方法一：暴力双指针
 * 遍历每个右端点的左端点
 * 
 * 方法二：记忆化搜索/DP
 * f(i,j)，表示下标[i, j]范围内最长回文子数组的长度 
 * f(i,j)=f(i+1,j-1)+2，              当f[i]==f[j]
 * 边界：f(i,j)=1，当i==j
 *       f(i,j)=0，当i>j
 * 
 * 方法三：中心扩展法
 * 区分奇偶地从第i个字符向两边扩展
 * 合并奇偶计算，则遍历范围为[0,2n-1]
 * 偶数初始左指针l=i/2、右指针r=i/2
 * 奇数初始左指针l=floor(i/2)、右指针r=ceil(i/2)
 * 合并初始指针：左指针l=floor(i/2)、右指针r=ceil(i/2)
 * 
 * 方法四：Manacher算法
 * O(n)时间预处理所有字符的最大回文半径
 * O(1)时间查询结果
 */
class Solution {
public:
    // 记忆化搜索
    string longestPalindrome1(string s) {
        string ans = "";
        int n = s.length();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i >= j) {
                return 1;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            if (s[i] == s[j] && dfs(i + 1, j - 1)) {
                res = 1;
                if (j - i + 1 > ans.length()) {
                    ans = s.substr(i, j - i + 1);
                }
            } else { // 搜索更多可能
                dfs(i, j - 1);
                dfs(i + 1, j);
            }
            return res;
        };
        dfs(0, n - 1);
        return ans == "" ? s.substr(0, 1) : ans;
    }

    // DP+空间优化
    string longestPalindrome2(string s) {
        string ans = "";
        int n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--) {
            f[i] = 1;
            int pre = 1;
            for (int j = i + 1; j < n; j++) {
                int tmp = f[j];
                if (s[i] == s[j] && pre) {
                    f[j] = 1;
                    if (j - i + 1 > ans.length()) {
                        ans = s.substr(i, j - i + 1);
                    }
                } else {
                    f[j] = 0; // 滚动数组需要更新
                }
                pre = tmp;
            }
        }
        return ans == "" ? s.substr(0, 1) : ans;
    }

    // 中心扩展法
    string longestPalindrome3(string s) {
        string ans = "";
        int n = s.length();
        for (int i = 0; i < 2 * n - 1; i++) {
            int l = i / 2, r = (i + 1) / 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                l--;
                r++;
            }
            // 循环结束回文子串[i+1,j-1]
            if (r - l - 1 > ans.length()) {
                ans = s.substr(l + 1, r - l - 1);
            }
        }   
        return ans;
    }

    // Manacher算法
    string longestPalindrome(string s) {
        // 将s改造成t，字符用'#'隔开，收尾加不可能用到的2个字符，如'^'和'$'
        // 方便适配奇偶下标
        string t = "^";
        for (char c : s) {
            t += "#";
            t += c;
        }
        t += "#$";

        // 定义t中奇回文串的回文半径（包括中心字符）
        vector<int> half_len(t.length());
        half_len[1] = 1; // 初始化第一个有效字符半径为1

        // 定义已遍历的右边界box_r和当前字符的回文中心box_m
        // max_i最大半径的回文中心下标，方便获取最长回文子串
        int box_r = 0, box_m = 0, max_i = 0;
        for (int i = 2; i < half_len.size(); i++) { // 从第1个有效字符遍历
            int hl = 1; // 声明当前回文半径

            // 初始化当前回文半径，不初始化，相当于从 1 开始的暴力扩展
            if (i < box_r) {
                // 记 i 关于 box_m 的对称位置 i'=box_m*2-i
                // 若以 i' 为回文中心的最大回文范围大于以 box_m 为中心的回文范围
                // （超右界了）即i+half_len[i'] >= box_r
                // 则更新当前回文半径 hl 应先初始化为i到右界的距离 box_r-i
                // 否则应初始化为镜像中心 i' 的最大回文半径half_len[i']
                hl = min(half_len[box_m * 2 - i], box_r - i);
            }

            // 随着 i 遍历增大，box_r 也持续向右更新
            while (t[i - hl] == t[i + hl]) {
                hl++;
                box_m = i;
                box_r = i + hl;
            }
            half_len[i] = hl;

            if (hl > half_len[max_i]) {
                max_i = i;
            }
        }

        int max_radis = half_len[max_i];
        // 在s到t的映射中，下标t_i == s_i * 2 + 2
        // 由于回文半径包含中心需 -1 ，此外t回文子串的首尾是'#'还需 -1 ，则t回文子串左端点下标t_l=t_i-(hl-2) 
        // 合并同类项得：s最长回文子串左端点下标 s_l=((max_i-(hl-2))-2) / 2=(max_i-hl)/2
        // s回文子串长度 = t回文半径-1 = hl-1
        return s.substr((max_i - max_radis) / 2, max_radis - 1);
    }
};
// @lc code=end

