/*
 * @lc app=leetcode id=988 lang=cpp
 *
 * [988] Smallest String Starting From Leaf
 *
 * https://leetcode.com/problems/smallest-string-starting-from-leaf/description/
 *
 * algorithms
 * Medium (60.88%)
 * Likes:    2375
 * Dislikes: 336
 * Total Accepted:    211.5K
 * Total Submissions: 347.1K
 * Testcase Example:  '[0,1,2,3,4,3,4]'
 *
 * You are given the root of a binary tree where each node has a value in the
 * range [0, 25] representing the letters 'a' to 'z'.
 * 
 * Return the lexicographically smallest string that starts at a leaf of this
 * tree and ends at the root.
 * 
 * As a reminder, any shorter prefix of a string is lexicographically
 * smaller.
 * 
 * 
 * For example, "ab" is lexicographically smaller than "aba".
 * 
 * 
 * A leaf of a node is a node that has no children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [0,1,2,3,4,3,4]
 * Output: "dba"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [25,1,3,1,3,0,2]
 * Output: "adz"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [2,2,1,null,1,0,null,0]
 * Output: "abc"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 8500].
 * 0 <= Node.val <= 25
 * 
 * 
 */
#include "template.h"
#include <string>
using namespace std;
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string smallestFromLeaf(TreeNode* root) {
        string ans(1, 'z' + 1);
        string cur = "";
        auto dfs = [&](auto &dfs, TreeNode *node) -> void {
            if (!node) {
                return;
            }
            cur.insert(cur.begin(), 'a' + node->val);
            if (!node->left && !node->right) {
                ans = min(ans, cur);
            }
            dfs(dfs, node->left);
            dfs(dfs, node->right);
            cur.erase(cur.begin());
        };
        dfs(dfs, root);
        return ans;
    }
};
// @lc code=end

