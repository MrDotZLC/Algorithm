/*
 * @lc app=leetcode id=943 lang=cpp
 *
 * [943] Find the Shortest Superstring
 *
 * https://leetcode.com/problems/find-the-shortest-superstring/description/
 *
 * algorithms
 * Hard (44.41%)
 * Likes:    1510
 * Dislikes: 152
 * Total Accepted:    34.2K
 * Total Submissions: 76.1K
 * Testcase Example:  '["alex","loves","leetcode"]'
 *
 * Given an array of strings words, return the smallest string that contains
 * each string in words as a substring. If there are multiple valid strings of
 * the smallest length, return any of them.
 * 
 * You may assume that no string in words is a substring of another string in
 * words.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["alex","loves","leetcode"]
 * Output: "alexlovesleetcode"
 * Explanation: All permutations of "alex","loves","leetcode" would also be
 * accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
 * Output: "gctaagttcatgcatc"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 12
 * 1 <= words[i].length <= 20
 * words[i] consists of lowercase English letters.
 * All the strings of words are unique.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <bit>
using namespace std;
// @lc code=start
/**
 * 状压DP
 * 预处理每对字符串(i,j)，i的后缀与j的前缀的重复长度len
 * 枚举所有字符串选用情况，找到最短长度的答案
 * f(mask,last)表示已选用下标集合为mask且上一个字符串下标为j时的最短长度
 * f(mask,last)=f(mask|1<<nxt,nxt)+len(words[nxt])-repetition_len(last,nxt)
 */
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> g(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int l1 = words[i].size(), l2 = words[j].size();
                int max_l = min(l1, l2);
                for (int k = max_l; k >= 0; k--) {
                    if (words[i].substr(l1 - k, k) == words[j].substr(0, k)) {
                        g[i][j] = k;
                        break;
                    }
                }
            }
        }

        int m = (1 << n) - 1;
        vector<vector<string>> memo(m, vector<string>(n, ""));
        auto dfs = [&](this auto &&dfs, int mask, int last) -> string {
            if (mask == m) {
                return "";
            }
            string &res = memo[mask][last];
            if (!res.empty()) {
                return res;
            }
            int cnt = INT_MAX;
            for (int nxt = 0; nxt < n; nxt++) {
                if (mask == 0) {
                    string x = dfs(mask | 1 << nxt, nxt);
                    if (cnt > words[nxt].size() + x.size()) {
                        cnt = words[nxt].size() + x.size();
                        res = words[nxt] + x;
                    }
                } else if ((mask & 1 << nxt) == 0) {
                    string x = dfs(mask | 1 << nxt, nxt);
                    if (cnt > words[nxt].size() - g[last][nxt] + x.size()) {
                        cnt = words[nxt].size() - g[last][nxt] + x.size();
                        res = words[nxt].substr(g[last][nxt]) + x;
                    }
                }
            }
            return res;
        };
        return dfs(0, 0);
    }
};
// @lc code=end

