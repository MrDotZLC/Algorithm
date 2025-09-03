/*
 * @lc app=leetcode id=700 lang=cpp
 *
 * [700] Search in a Binary Search Tree
 *
 * https://leetcode.com/problems/search-in-a-binary-search-tree/description/
 *
 * algorithms
 * Easy (81.88%)
 * Likes:    6366
 * Dislikes: 208
 * Total Accepted:    1.2M
 * Total Submissions: 1.5M
 * Testcase Example:  '[4,2,7,1,3]\n2'
 *
 * You are given the root of a binary search tree (BST) and an integer val.
 * 
 * Find the node in the BST that the node's value equals val and return the
 * subtree rooted with that node. If such a node does not exist, return
 * null.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [4,2,7,1,3], val = 2
 * Output: [2,1,3]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [4,2,7,1,3], val = 5
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 5000].
 * 1 <= Node.val <= 10^7
 * root is a binary search tree.
 * 1 <= val <= 10^7
 * 
 * 
 */
#include "template.h"
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
    // recursion
    TreeNode* searchBST1(TreeNode* root, int val) {
        if (!root || root->val == val) {
            return root;
        }
        return searchBST(val < root->val ? root->left : root->right, val);
    }

    // iteration
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root && root->val != val) {
            root = val < root->val ? root->left : root->right;
        }
        return root;
    }
};
// @lc code=end

