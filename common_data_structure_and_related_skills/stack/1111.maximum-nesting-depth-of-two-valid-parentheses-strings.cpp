/*
 * @lc app=leetcode id=1111 lang=cpp
 *
 * [1111] Maximum Nesting Depth of Two Valid Parentheses Strings
 *
 * https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/description/
 *
 * algorithms
 * Medium (71.47%)
 * Likes:    462
 * Dislikes: 1893
 * Total Accepted:    31.6K
 * Total Submissions: 44.2K
 * Testcase Example:  '"(()())"'
 *
 * A string is a valid parentheses string (denoted VPS) if and only if it
 * consists of "(" and ")" characters only, and:
 * 
 * 
 * It is the empty string, or
 * It can be written as AB (A concatenated with B), where A and B are VPS's,
 * or
 * It can be written as (A), where A is a VPS.
 * 
 * 
 * We can similarly define the nesting depth depth(S) of any VPS S as
 * follows:
 * 
 * 
 * depth("") = 0
 * depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
 * depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
 * 
 * 
 * For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0,
 * 1, and 2), and ")(" and "(()" are not VPS's.
 * 
 * 
 * 
 * Given a VPS seq, split it into two disjoint subsequences A and B, such that
 * A and B are VPS's (and A.length + B.length = seq.length).
 * 
 * Now choose any such A and B such that max(depth(A), depth(B)) is the minimum
 * possible value.
 * 
 * Return an answer array (of length seq.length) that encodes such a choice of
 * A and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note
 * that even though multiple answers may exist, you may return any of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: seq = "(()())"
 * Output: [0,1,1,1,1,0]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: seq = "()(())()"
 * Output: [0,0,0,1,1,0,1,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= seq.size <= 10000
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // 将深度超过ceil(mx_depth / 2)的元素分到1组
    vector<int> maxDepthAfterSplit1(string seq) {
        vector<int> ans(seq.length());
        int level = 0, mx_level = 0;
        for (int i = 0; i < seq.length(); i++) {
            char c = seq[i];
            if (c == '(') {
                level++;
                if (level > mx_level) {
                    mx_level = level;
                }
            } else if (c == ')') {
                level--;
            }
        }

        mx_level = (mx_level + 1) / 2;
        level = 0;
        for (int i = 0; i < seq.length(); i++) {
            char c = seq[i];
            if (c == '(') {
                level++;
                if (level > mx_level) {
                    ans[i] = 1;
                }
            } else if (c == ')') {
                if (level > mx_level) {
                    ans[i] = 1;
                }
                level--;
            }
        }

        return ans;
    }

    // 根据深度的奇偶划分组
    vector<int> maxDepthAfterSplit2(string seq) {
        vector<int> ans(seq.length());
        int level = 0;
        for (int i = 0; i < seq.length(); i++) {
            char c = seq[i];
            if (c == '(') {
                level++;
                ans[i] = level % 2;
            } else if (c == ')') {
                ans[i] = level % 2;
                level--;
            }
        }

        return ans;
    }

    // 根据深度的奇偶划分组
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans(seq.length());
        int idx = 0;
        for (char c : seq) {
            ans[idx++] = c == '(' ? idx % 2 : (idx + 1) % 2;
        }
        return ans;
    }
};
// @lc code=end

