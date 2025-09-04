/*
 * @lc app=leetcode id=623 lang=cpp
 *
 * [623] Add One Row to Tree
 *
 * https://leetcode.com/problems/add-one-row-to-tree/description/
 *
 * algorithms
 * Medium (64.06%)
 * Likes:    3633
 * Dislikes: 270
 * Total Accepted:    294.2K
 * Total Submissions: 459.2K
 * Testcase Example:  '[4,2,6,3,1,5]\n1\n2'
 *
 * Given the root of a binary tree and two integers val and depth, add a row of
 * nodes with value val at the given depth depth.
 * 
 * Note that the root node is at depth 1.
 * 
 * The adding rule is:
 * 
 * 
 * Given the integer depth, for each not null tree node cur at the depth depth
 * - 1, create two tree nodes with value val as cur's left subtree root and
 * right subtree root.
 * cur's original left subtree should be the left subtree of the new left
 * subtree root.
 * cur's original right subtree should be the right subtree of the new right
 * subtree root.
 * If depth == 1 that means there is no depth depth - 1 at all, then create a
 * tree node with value val as the new root of the whole original tree, and the
 * original tree is the new root's left subtree.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [4,2,6,3,1,5], val = 1, depth = 2
 * Output: [4,1,1,2,null,null,6,3,1,5]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [4,2,null,3,1], val = 1, depth = 3
 * Output: [4,2,null,1,1,3,null,null,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * The depth of the tree is in the range [1, 10^4].
 * -100 <= Node.val <= 100
 * -10^5 <= val <= 10^5
 * 1 <= depth <= the depth of tree + 1
 * 
 * 
 */
#include "template.h"
#include <deque>
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
    TreeNode* addOneRow1(TreeNode* root, int val, int depth) {
        TreeNode dummy(0, root, nullptr);
        TreeNode *cur = &dummy;
        auto dfs = [&](auto &dfs, TreeNode* node, int d) -> void {
            if (!node) {
                return;
            }
            if (d == depth -1) {
                TreeNode *l = new TreeNode(val, node->left, nullptr);
                TreeNode *r = new TreeNode(val, nullptr, node->right);
                node->left = l;
                node->right = r;
                return;
            }
            dfs(dfs, node->left, d + 1);
            dfs(dfs, node->right, d + 1);
        };
        dfs(dfs, cur, 0);
        return dummy.left;
    }

    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            return new TreeNode(val, root, nullptr);
        }
        deque<TreeNode*> q;
        q.push_back(root);
        int d = 1;
        while (!q.empty()) {
            int i = q.size();
            while (i--) {
                auto node = q.front();
                q.pop_front();
                if (d == depth - 1) {
                    TreeNode *l = new TreeNode(val, node->left, nullptr);
                    TreeNode *r = new TreeNode(val, nullptr, node->right);
                    node->left = l;
                    node->right = r;
                    q.push_back(l);
                    q.push_back(r);
                } else {
                    if (node->left) {
                        q.push_back(node->left);
                    }
                    if (node->right) {
                        q.push_back(node->right);
                    }
                }
            }
            d++;
        }
        return root;
    }
};
// @lc code=end

