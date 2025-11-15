/*
 * @lc app=leetcode id=647 lang=cpp
 *
 * [647] Palindromic Substrings
 *
 * https://leetcode.com/problems/palindromic-substrings/description/
 *
 * algorithms
 * Medium (71.81%)
 * Likes:    11347
 * Dislikes: 255
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
 * Testcase Example:  '"abc"'
 *
 * Given a string s, return the number of palindromic substrings in it.
 * 
 * A string is a palindrome when it reads the same backward as forward.
 * 
 * A substring is a contiguous sequence of characters within the string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abc"
 * Output: 3
 * Explanation: Three palindromic strings: "a", "b", "c".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aaa"
 * Output: 6
 * Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
/**
 * 方法一：暴力双指针
 * 遍历每个右端点的左端点
 * 
 * 方法二：记忆化搜索/DP
 * f(i,j)，表示下标[i, j]是否为回文串，是则+1，最后加上s的长度
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
 * O(n)时间累加s所有字符的 最大回文半径 = (s子串长度-1)/2 = (t回文半径-1+1)/2
 */
class Solution {
public:
    // DP+空间优化
    int countSubstrings1(string s) {
        int ans = 0, n = s.length();
        vector<int> f(n);
        for (int i = n - 1; i >= 0; i--) {
            ans++;
            f[i] = 1;
            int pre = 1;
            for (int j = i + 1; j < n; j++) {
                int tmp = f[j];
                f[j] = (s[i] == s[j] && pre) ? 1 : 0;
                ans += f[j];
                pre = tmp;
            }
        }
        return ans;
    }

    // Manacher算法
    int countSubstrings(string s) {
        string t = "^";
        for (char c : s) {
            t += "#";
            t += c;
        }
        t += "#$";

        vector<int> half_len(t.length());
        half_len[1] = 1;

        int box_m = 0, box_r = 0;
        for (int i = 2; i < half_len.size(); i++) {
            int hl = 1;
            if (i < box_r) {
                hl = min(half_len[2 * box_m - i], box_r - i);
            }
            while (t[i - hl] == t[i + hl]) {
                hl++;
                box_m = i;
                box_r = i + hl;
            }
            half_len[i] = hl;
        }

        int ans = 0;
        // t除首尾所有字符的最大回文半径，包含#字符，其代表长度为偶数的t回文子串半径
        // s最大回文半径 = (s子串长度-1)/2 = (t回文半径-1+1)/2
        for (int i = 1; i < half_len.size() - 1; i++) {
            ans += half_len[i] / 2;
        }
        
        return ans;
    }
};
// @lc code=end

