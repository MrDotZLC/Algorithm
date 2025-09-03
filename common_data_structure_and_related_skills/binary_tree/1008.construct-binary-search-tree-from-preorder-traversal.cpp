/*
 * @lc app=leetcode id=1008 lang=cpp
 *
 * [1008] Construct Binary Search Tree from Preorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/
 *
 * algorithms
 * Medium (83.48%)
 * Likes:    6589
 * Dislikes: 91
 * Total Accepted:    488.9K
 * Total Submissions: 584.3K
 * Testcase Example:  '[8,5,1,7,10,12]'
 *
 * Given an array of integers preorder, which represents the preorder traversal
 * of a BST (i.e., binary search tree), construct the tree and return its
 * root.
 * 
 * It is guaranteed that there is always possible to find a binary search tree
 * with the given requirements for the given test cases.
 * 
 * A binary search tree is a binary tree where for every node, any descendant
 * of Node.left has a value strictly less than Node.val, and any descendant of
 * Node.right has a value strictly greater than Node.val.
 * 
 * A preorder traversal of a binary tree displays the value of the node first,
 * then traverses Node.left, then traverses Node.right.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: preorder = [8,5,1,7,10,12]
 * Output: [8,5,10,1,7,null,12]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: preorder = [1,3]
 * Output: [1,null,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= preorder.length <= 100
 * 1 <= preorder[i] <= 1000
 * All the values of preorder are unique.
 * 
 * 
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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return dfs(preorder, 0, preorder.size());
    }

    TreeNode* dfs(vector<int>& preorder, int l, int r) {
        if (l == r) {
            return nullptr;
        }
        int root = preorder[l];
        int m = ranges::lower_bound(preorder.begin() + 1 + l, preorder.begin() + r, root) - preorder.begin();
        return new TreeNode(root, dfs(preorder, l + 1, m), dfs(preorder, m, r));
    }
};
// @lc code=end

