/*
 * @lc app=leetcode id=653 lang=cpp
 *
 * [653] Two Sum IV - Input is a BST
 *
 * https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
 *
 * algorithms
 * Easy (62.38%)
 * Likes:    7126
 * Dislikes: 288
 * Total Accepted:    694.9K
 * Total Submissions: 1.1M
 * Testcase Example:  '[5,3,6,2,4,null,7]\n9'
 *
 * Given the root of a binary search tree and an integer k, return true if
 * there exist two elements in the BST such that their sum is equal to k, or
 * false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [5,3,6,2,4,null,7], k = 9
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [5,3,6,2,4,null,7], k = 28
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * -10^4 <= Node.val <= 10^4
 * root is guaranteed to be a valid binary search tree.
 * -10^5 <= k <= 10^5
 * 
 * 
 */
#include "template.h"
#include <stack>
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
    TreeNode *get_next(stack<TreeNode *> &stk, bool is_left) {
        TreeNode *root = stk.top();
        stk.pop();
        TreeNode *node = is_left ? root->right : root->left;
        while (node != nullptr) {
            stk.push(node);
            node = is_left ? node->left : node->right;
        }
        return root;
    }

    bool findTarget(TreeNode* root, int k) {
        TreeNode *left = root, *right = root;
        stack<TreeNode *> leftStack, rightStack;
        leftStack.push(left);
        while (left->left != nullptr) {
            leftStack.push(left->left);
            left = left->left;
        }
        rightStack.push(right);
        while (right->right != nullptr) {
            rightStack.push(right->right);
            right = right->right;
        }
        while (left != right) {
            if (left->val + right->val == k) {
                return true;
            }
            if (left->val + right->val < k) {
                left = get_next(leftStack, true);
            } else {
                right = get_next(rightStack, false);
            }
        }
        return false;
    }
};
// @lc code=end

