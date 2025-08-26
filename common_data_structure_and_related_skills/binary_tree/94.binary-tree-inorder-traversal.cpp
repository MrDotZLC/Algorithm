/*
 * @lc app=leetcode id=94 lang=cpp
 *
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Easy (78.80%)
 * Likes:    14389
 * Dislikes: 862
 * Total Accepted:    3.3M
 * Total Submissions: 4.2M
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given the root of a binary tree, return the inorder traversal of its nodes'
 * values.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,null,2,3]
 * 
 * Output: [1,3,2]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
 * 
 * Output: [4,2,6,5,7,1,3,9,8]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = []
 * 
 * Output: []
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: root = [1]
 * 
 * Output: [1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100
 * 
 * 
 * 
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 */
#include "template.h"
#include <vector>
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
    vector<int> inorderTraversal(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> ans;
        inorderTraversal(root, ans);
        return ans;
    }

    void inorderTraversal(TreeNode* root, vector<int> &ans) {
        if (!root) {
            return;
        }
        inorderTraversal(root->left, ans);
        ans.push_back(root->val);
        inorderTraversal(root->right, ans);
    }
};
// @lc code=end

