/*
 * @lc app=leetcode id=1023 lang=cpp
 *
 * [1023] Camelcase Matching
 *
 * https://leetcode.com/problems/camelcase-matching/description/
 *
 * algorithms
 * Medium (63.97%)
 * Likes:    960
 * Dislikes: 345
 * Total Accepted:    58.8K
 * Total Submissions: 91.8K
 * Testcase Example:  '["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"]\n"FB"'
 *
 * Given an array of strings queries and a string pattern, return a boolean
 * array answer where answer[i] is true if queries[i] matches pattern, and
 * false otherwise.
 * 
 * A query word queries[i] matches pattern if you can insert lowercase English
 * letters into the pattern so that it equals the query. You may insert a
 * character at any position in pattern or you may choose not to insert any
 * characters at all.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: queries =
 * ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern =
 * "FB"
 * Output: [true,false,true,true,false]
 * Explanation: "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
 * "FootBall" can be generated like this "F" + "oot" + "B" + "all".
 * "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: queries =
 * ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern =
 * "FoBa"
 * Output: [true,false,true,false,false]
 * Explanation: "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
 * "FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: queries =
 * ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern =
 * "FoBaT"
 * Output: [false,true,false,false,false]
 * Explanation: "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r"
 * + "T" + "est".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= pattern.length, queries.length <= 100
 * 1 <= queries[i].length <= 100
 * queries[i] and pattern consist of English letters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        vector<bool> ans;
        for (string s : queries) {
            ans.push_back(check(s, pattern));
        }
        return ans;
    }

    bool check(string &s, string &p) {
        int i = 0, j = 0, m = s.length(), n = p.length();
        if (m < n) {
            return false;
        }
        while (i < m || j < n) {
            if (s[i] == p[j]) {
                i++;
                j++;
            } else if (s[i] >= 97) {
                i++;
            } else {
                return false;
            }
        }
        return j == n;
    }
};
// @lc code=end

