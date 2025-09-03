/*
 * @lc app=leetcode id=1382 lang=cpp
 *
 * [1382] Balance a Binary Search Tree
 *
 * https://leetcode.com/problems/balance-a-binary-search-tree/description/
 *
 * algorithms
 * Medium (84.68%)
 * Likes:    3783
 * Dislikes: 96
 * Total Accepted:    291.7K
 * Total Submissions: 344.3K
 * Testcase Example:  '[1,null,2,null,3,null,4]'
 *
 * Given the root of a binary search tree, return a balanced binary search tree
 * with the same node values. If there is more than one answer, return any of
 * them.
 * 
 * A binary search tree is balanced if the depth of the two subtrees of every
 * node never differs by more than 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,null,2,null,3,null,4,null,null]
 * Output: [2,1,3,null,null,null,4]
 * Explanation: This is not the only correct answer, [3,1,4,null,2] is also
 * correct.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [2,1,3]
 * Output: [2,1,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * 1 <= Node.val <= 10^5
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
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> v;
        dfs(root, v);
        return build(v, 0, v.size());
    }

    void dfs(TreeNode *node, vector<int> &v) {
        if (!node) {
            return;
        }
        dfs(node->left, v);
        v.push_back(node->val);
        dfs(node->right, v);
    }

    TreeNode* build(vector<int> &v, int l, int r) {
        if (l == r) {
            return nullptr;
        }
        int m = l + (r - l) / 2;
        return new TreeNode(v[m], build(v, l, m), build(v, m + 1, r));
    }
};
// @lc code=end

