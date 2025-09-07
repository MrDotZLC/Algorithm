/*
 * @lc app=leetcode id=331 lang=cpp
 *
 * [331] Verify Preorder Serialization of a Binary Tree
 *
 * https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/description/
 *
 * algorithms
 * Medium (46.27%)
 * Likes:    2420
 * Dislikes: 128
 * Total Accepted:    158.4K
 * Total Submissions: 341K
 * Testcase Example:  '"9,3,4,#,#,1,#,#,2,#,6,#,#"'
 *
 * One way to serialize a binary tree is to use preorder traversal. When we
 * encounter a non-null node, we record the node's value. If it is a null node,
 * we record using a sentinel value such as "#".
 * 
 * For example, the above binary tree can be serialized to the string
 * "9,3,4,#,#,1,#,#,2,#,6,#,#", where "#" represents a null node.
 * 
 * Given a string of comma-separated values preorder, return true if it is a
 * correct preorder traversal serialization of a binary tree.
 * 
 * It is guaranteed that each comma-separated value in the string must be
 * either an integer or a character "#" representing null pointer.
 * 
 * You may assume that the input format is always valid.
 * 
 * 
 * For example, it could never contain two consecutive commas, such as
 * "1,,3".
 * 
 * 
 * Note: You are not allowed to reconstruct the tree.
 * 
 * 
 * Example 1:
 * Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
 * Output: true
 * Example 2:
 * Input: preorder = "1,#"
 * Output: false
 * Example 3:
 * Input: preorder = "9,#,#,1"
 * Output: false
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= preorder.length <= 10^4
 * preorder consist of integers in the range [0, 100] and "#" separated by
 * commas ','.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
// @lc code=start
class Solution {
public:
    bool isValidSerialization1(string preorder) {
        vector<string> stk;
        vector<string> nodes;
        stringstream ss(preorder);
        string token;
        while (getline(ss, token, ',')) {
            nodes.push_back(token);
        }
        for (string s : nodes) {
            stk.push_back(s);
            int n = stk.size();
            while (n >= 3 && stk[n - 1] == stk[n - 2] &&
                   stk[n - 2] == "#" && stk[n - 3] != "#") {
                stk.pop_back();
                stk.pop_back();
                stk.pop_back();
                stk.push_back("#");
                n = stk.size();
            }
        }
        int n = stk.size();
        return n == 1 && stk.back() == "#";
    }

    bool isValidSerialization(string preorder) {
        vector<string> nodes;
        stringstream ss(preorder);
        string token;
        while (getline(ss, token, ',')) {
            nodes.push_back(token);
        }
        int diff = 1;
        for (string s : nodes) {
            diff--;
            if (diff < 0) {
                return false;
            }
            if (s != "#") {
                diff += 2;
            }
        }
        return diff == 0;
    }
};
// @lc code=end

