/*
 * @lc app=leetcode id=767 lang=cpp
 *
 * [767] Reorganize String
 *
 * https://leetcode.com/problems/reorganize-string/description/
 *
 * algorithms
 * Medium (56.31%)
 * Likes:    9068
 * Dislikes: 282
 * Total Accepted:    556.7K
 * Total Submissions: 984.3K
 * Testcase Example:  '"aab"'
 *
 * Given a string s, rearrange the characters of s so that any two adjacent
 * characters are not the same.
 * 
 * Return any possible rearrangement of s or return "" if not possible.
 * 
 * 
 * Example 1:
 * Input: s = "aab"
 * Output: "aba"
 * Example 2:
 * Input: s = "aaab"
 * Output: ""
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
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // heap
    string reorganizeString1(string s) {
        int n = s.length();
        unordered_map<int, int> cnt;
        for (char c : s) {
            cnt[c]++;
        }
        priority_queue<pair<int, char>> pq;
        for (auto &[c, n] : cnt) {
            pq.emplace(n, c);
        }

        if (pq.top().first * 2 > n + 1) {
            return "";
        }

        string ans;
        while (!pq.empty()) {
            auto t = pq.top();
            pq.pop();
            if (!ans.empty() && ans.back() == t.second) {
                auto t1 = pq.top();
                pq.pop();
                ans += t1.second;
                if (--t1.first > 0) {
                    pq.push(t1);
                }
                pq.push(t);
            } else {
                ans += t.second;
                if (--t.first > 0) {
                    pq.push(t);
                }
            }
        }
        return ans;
    }

    // greedy
    string reorganizeString(string s) {
        int n = s.length(), m = 0, mch = s[0];
        unordered_map<int, int> cnt;
        for (char c : s) {
            if (++cnt[c] > m) {
                m = cnt[c];
                mch = c;
            }
        }

        if (m * 2 > n + 1) {
            return "";
        }

        string ans(n, 0);
        int i = 0;
        for (; m--; i += 2) {
            ans[i] = mch;
        }
        cnt[mch] = 0;

        for (auto &[c, v] : cnt) {
            while (v--) {
                if (i >= n) {
                    i = 1;
                }
                ans[i] = c;
                i += 2;
            }
        }

        return ans;
    }
};
// @lc code=end

