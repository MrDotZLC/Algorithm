/*
 * @lc app=leetcode id=572 lang=cpp
 *
 * [572] Subtree of Another Tree
 *
 * https://leetcode.com/problems/subtree-of-another-tree/description/
 *
 * algorithms
 * Easy (50.19%)
 * Likes:    8675
 * Dislikes: 577
 * Total Accepted:    1.1M
 * Total Submissions: 2.2M
 * Testcase Example:  '[3,4,5,1,2]\n[4,1,2]'
 *
 * Given the roots of two binary trees root and subRoot, return true if there
 * is a subtree of root with the same structure and node values of subRoot and
 * false otherwise.
 * 
 * A subtree of a binary tree tree is a tree that consists of a node in tree
 * and all of this node's descendants. The tree tree could also be considered
 * as a subtree of itself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the root tree is in the range [1, 2000].
 * The number of nodes in the subRoot tree is in the range [1, 1000].
 * -10^4 <= root.val <= 10^4
 * -10^4 <= subRoot.val <= 10^4
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
    // 代码逻辑同 104. 二叉树的最大深度
    int getHeight(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_h = getHeight(root->left);
        int right_h = getHeight(root->right);
        return max(left_h, right_h) + 1;
    }

    // 100. 相同的树
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr || q == nullptr) {
            return p == q; // 必须都是 nullptr
        }
        return p->val == q->val &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }

    bool isSubtree1(TreeNode* root, TreeNode* subRoot) {
        if (!root) {
            return false;
        }

        return isSameTree(root, subRoot) || 
            isSubtree(root->left, subRoot) || 
            isSubtree(root->right, subRoot);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        int h = getHeight(subRoot);
        auto dfs = [&](auto dfs, TreeNode* node) -> pair<int, bool> {
            if (!node) {
                return {0, false};
            }

            auto l = dfs(dfs, node->left);
            auto r = dfs(dfs, node->right);
            if (l.second || r.second) {
                return {0, true};
            }
            int node_h = max(l.first, r.first) + 1;
            return {node_h, node_h == h && isSameTree(node, subRoot)};
        };

        return dfs(dfs, root).second;
    }
};
// @lc code=end

