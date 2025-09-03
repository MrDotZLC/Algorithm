/*
 * @lc app=leetcode id=1373 lang=cpp
 *
 * [1373] Maximum Sum BST in Binary Tree
 *
 * https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/description/
 *
 * algorithms
 * Hard (44.71%)
 * Likes:    2873
 * Dislikes: 198
 * Total Accepted:    108.2K
 * Total Submissions: 239.7K
 * Testcase Example:  '[1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]'
 *
 * Given a binary tree root, return the maximum sum of all keys of any sub-tree
 * which is also a Binary Search Tree (BST).
 * 
 * Assume a BST is defined as follows:
 * 
 * 
 * The left subtree of a node contains only nodes with keys less than the
 * node's key.
 * The right subtree of a node contains only nodes with keys greater than the
 * node's key.
 * Both the left and right subtrees must also be binary search trees.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
 * Output: 20
 * Explanation: Maximum sum in a valid Binary search tree is obtained in root
 * node with key equal to 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: root = [4,3,null,1,2]
 * Output: 2
 * Explanation: Maximum sum in a valid Binary search tree is obtained in a
 * single root node with key equal to 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [-4,-2,-5]
 * Output: 0
 * Explanation: All values are negatives. Return an empty BST.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 4 * 10^4].
 * -4 * 10^4 <= Node.val <= 4 * 10^4
 * 
 * 
 */
#include "template.h"
#include <tuple>
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
    int maxSumBST(TreeNode* root) {
        dfs(root);
        return ans;
    }

    tuple<int, int, int> dfs(TreeNode *node) {
        if (node == nullptr)
            return {INT_MAX, INT_MIN, 0};

        auto [l_min, l_max, l_sum] = dfs(node->left); // 递归左子树
        auto [r_min, r_max, r_sum] = dfs(node->right); // 递归右子树
        int x = node->val;
        if (x <= l_max || x >= r_min) // 不是二叉搜索树
            return {INT_MIN, INT_MAX, 0};

        int s = l_sum + r_sum + x; // 这棵子树的所有节点值之和
        ans = max(ans, s);

        return {min(l_min, x), max(r_max, x), s};
    }

private:
    int ans = 0;
};
// @lc code=end

