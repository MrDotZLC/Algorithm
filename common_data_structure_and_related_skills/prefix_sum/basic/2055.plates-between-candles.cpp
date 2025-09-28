/*
 * @lc app=leetcode id=2055 lang=cpp
 *
 * [2055] Plates Between Candles
 *
 * https://leetcode.com/problems/plates-between-candles/description/
 *
 * algorithms
 * Medium (46.77%)
 * Likes:    1330
 * Dislikes: 70
 * Total Accepted:    73.5K
 * Total Submissions: 156.5K
 * Testcase Example:  '"**|**|***|"\n[[2,5],[5,9]]'
 *
 * There is a long table with a line of plates and candles arranged on top of
 * it. You are given a 0-indexed string s consisting of characters '*' and '|'
 * only, where a '*' represents a plate and a '|' represents a candle.
 * 
 * You are also given a 0-indexed 2D integer array queries where queries[i] =
 * [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For
 * each query, you need to find the number of plates between candles that are
 * in the substring. A plate is considered between candles if there is at least
 * one candle to its left and at least one candle to its right in the
 * substring.
 * 
 * 
 * For example, s = "||**||**|*", and a query [3, 8] denotes the substring
 * "*||**|". The number of plates between candles in this substring is 2, as
 * each of the two plates has at least one candle in the substring to its left
 * and right.
 * 
 * 
 * Return an integer array answer where answer[i] is the answer to the i^th
 * query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "**|**|***|", queries = [[2,5],[5,9]]
 * Output: [2,3]
 * Explanation:
 * - queries[0] has two plates between candles.
 * - queries[1] has three plates between candles.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "***|**|*****|**||**|*", queries =
 * [[1,17],[4,5],[14,17],[5,11],[15,16]]
 * Output: [9,0,0,0,0]
 * Explanation:
 * - queries[0] has nine plates between candles.
 * - The other queries have zero plates between candles.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= s.length <= 10^5
 * s consists of '*' and '|' characters.
 * 1 <= queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= lefti <= righti < s.length
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
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> presum(n + 1), left(n), right(n);
        int p = -1;
        for (int i = 0; i < n; i++) {
            presum[i + 1] = presum[i];
            if (s[i] == '*') {
                presum[i + 1]++;
            } else {
                p = i;
            }
            left[i] = p;
        }
        p = n;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '|') {
                p = i;
            }
            right[i] = p;
        }

        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int l = right[queries[i][0]], r = left[queries[i][1]];
            if (l < r) {
                ans[i] = presum[r] - presum[l];
            }
        }   
        return ans;
    }
};
// @lc code=end

