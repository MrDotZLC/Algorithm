/*
 * @lc app=leetcode id=106 lang=cpp
 *
 * [106] Construct Binary Tree from Inorder and Postorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 *
 * algorithms
 * Medium (66.45%)
 * Likes:    8504
 * Dislikes: 149
 * Total Accepted:    852.7K
 * Total Submissions: 1.3M
 * Testcase Example:  '[9,3,15,20,7]\n[9,15,7,20,3]'
 *
 * Given two integer arrays inorder and postorder where inorder is the inorder
 * traversal of a binary tree and postorder is the postorder traversal of the
 * same tree, construct and return the binary tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 * Output: [3,9,20,null,null,15,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: inorder = [-1], postorder = [-1]
 * Output: [-1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= inorder.length <= 3000
 * postorder.length == inorder.length
 * -3000 <= inorder[i], postorder[i] <= 3000
 * inorder and postorder consist of unique values.
 * Each value of postorder also appears in inorder.
 * inorder is guaranteed to be the inorder traversal of the tree.
 * postorder is guaranteed to be the postorder traversal of the tree.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <unordered_map>
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < n; i++) {
            idx[inorder[i]] = i;
        }

        auto dfs = [&](auto &dfs, int post_l, int post_r, int in_l, int in_r) -> TreeNode* {
            if (post_l == post_r) {
                return nullptr;
            }
            int l_size = idx[postorder[post_r - 1]] - in_l;
            TreeNode *l = dfs(dfs, post_l, post_l + l_size, in_l, in_l + l_size);
            TreeNode *r = dfs(dfs, post_l + l_size, post_r - 1, in_l + l_size + 1, in_r);
            return new TreeNode(postorder[post_r - 1], l, r);
        };
        return dfs(dfs, 0, n, 0, n);
    }
};
// @lc code=end

