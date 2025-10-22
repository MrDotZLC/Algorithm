/*
 * @lc app=leetcode id=1405 lang=cpp
 *
 * [1405] Longest Happy String
 *
 * https://leetcode.com/problems/longest-happy-string/description/
 *
 * algorithms
 * Medium (65.46%)
 * Likes:    2764
 * Dislikes: 318
 * Total Accepted:    210.3K
 * Total Submissions: 321.2K
 * Testcase Example:  '1\n1\n7'
 *
 * A string s is called happy if it satisfies the following conditions:
 * 
 * 
 * s only contains the letters 'a', 'b', and 'c'.
 * s does not contain any of "aaa", "bbb", or "ccc" as a substring.
 * s contains at most a occurrences of the letter 'a'.
 * s contains at most b occurrences of the letter 'b'.
 * s contains at most c occurrences of the letter 'c'.
 * 
 * 
 * Given three integers a, b, and c, return the longest possible happy string.
 * If there are multiple longest happy strings, return any of them. If there is
 * no such string, return the empty string "".
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: a = 1, b = 1, c = 7
 * Output: "ccaccbcc"
 * Explanation: "ccbccacc" would also be a correct answer.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: a = 7, b = 1, c = 0
 * Output: "aabaa"
 * Explanation: It is the only correct answer in this case.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= a, b, c <= 100
 * a + b + c > 0
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
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if (a > 0) {
            pq.emplace(a, 'a');
        }
        if (b > 0) {
            pq.emplace(b, 'b');
        }
        if (c > 0) {
            pq.emplace(c, 'c');
        }

        string ans;
        while (!pq.empty()) {
            auto t = pq.top();
            pq.pop();
            if (ans.size() >= 2 && ans.back() == t.second &&
                ans[ans.size() - 2] == t.second) {
                if (pq.empty()) {
                    break;
                }
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
};
// @lc code=end

