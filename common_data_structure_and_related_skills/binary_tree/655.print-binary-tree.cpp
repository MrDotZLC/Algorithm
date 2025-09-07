/*
 * @lc app=leetcode id=655 lang=cpp
 *
 * [655] Print Binary Tree
 *
 * https://leetcode.com/problems/print-binary-tree/description/
 *
 * algorithms
 * Medium (65.65%)
 * Likes:    546
 * Dislikes: 466
 * Total Accepted:    81.3K
 * Total Submissions: 123.5K
 * Testcase Example:  '[1,2]'
 *
 * Given the root of a binary tree, construct a 0-indexed m x n string matrix
 * res that represents a formatted layout of the tree. The formatted layout
 * matrix should be constructed using the following rules:
 * 
 * 
 * The height of the tree is height and the number of rows m should be equal to
 * height + 1.
 * The number of columns n should be equal to 2^height+1 - 1.
 * Place the root node in the middle of the top row (more formally, at location
 * res[0][(n-1)/2]).
 * For each node that has been placed in the matrix at position res[r][c],
 * place its left child at res[r+1][c-2^height-r-1] and its right child at
 * res[r+1][c+2^height-r-1].
 * Continue this process until all the nodes in the tree have been placed.
 * Any empty cells should contain the empty string "".
 * 
 * 
 * Return the constructed matrix res.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2]
 * Output: 
 * [["","1",""],
 * ["2","",""]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,null,4]
 * Output: 
 * [["","","","1","","",""],
 * ["","2","","","","3",""],
 * ["","","4","","","",""]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 2^10].
 * -99 <= Node.val <= 99
 * The depth of the tree will be in the range [1, 10].
 * 
 * 
 */
#include "template.h"
#include <vector>
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
    int get_depth(TreeNode *root) {
        if (!root) return 0;
        int left = get_depth(root->left);
        int right = get_depth(root->right);
        return left > right ? left + 1 : right + 1;
    }
    void print(TreeNode *root, int start, int end, int row,
               vector<vector<string>> &res) {
        if (!root) return;
        int mid = (start + end) / 2;
        res[row][mid] = to_string(root->val);
        print(root->left, start, mid - 1, row + 1, res);
        print(root->right, mid + 1, end, row + 1, res);
    }

    vector<vector<string>> printTree(TreeNode *root) {
        int high = get_depth(root);
        int width = (1 << high) - 1;
        vector<vector<string>> res(high, vector<string>(width, ""));
        print(root, 0, width - 1, 0, res);
        return res;
    }
};
// @lc code=end

