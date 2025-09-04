/*
 * @lc app=leetcode id=993 lang=cpp
 *
 * [993] Cousins in Binary Tree
 *
 * https://leetcode.com/problems/cousins-in-binary-tree/description/
 *
 * algorithms
 * Easy (58.33%)
 * Likes:    4261
 * Dislikes: 228
 * Total Accepted:    331.3K
 * Total Submissions: 566.1K
 * Testcase Example:  '[1,2,3,4]\n4\n3'
 *
 * Given the root of a binary tree with unique values and the values of two
 * different nodes of the tree x and y, return true if the nodes corresponding
 * to the values x and y in the tree are cousins, or false otherwise.
 * 
 * Two nodes of a binary tree are cousins if they have the same depth with
 * different parents.
 * 
 * Note that in a binary tree, the root node is at the depth 0, and children of
 * each depth k node are at the depth k + 1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,4], x = 4, y = 3
 * Output: false
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [1,2,3,null,4], x = 2, y = 3
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [2, 100].
 * 1 <= Node.val <= 100
 * Each node has a unique value.
 * x != y
 * x and y are exist in the tree.
 * 
 * 
 */
#include "template.h"
#include <vector>
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
    bool isCousins(TreeNode* root, int x, int y) {
        deque<pair<TreeNode*, TreeNode*>> q;
        q.push_back({root, root});
        while (!q.empty()) {
            TreeNode *i = nullptr, *j = nullptr;
            int k = q.size();
            while (k--) {
                auto node = q.front();
                if (node.first->val == x) {
                    i = node.second;
                }
                if (node.first->val == y) {
                    j = node.second;
                }
                if (i && j) {
                    return i != j;
                }
                q.pop_front();
                if (node.first->left) {
                    q.push_back({node.first->left, node.first});
                }
                if (node.first->right) {
                    q.push_back({node.first->right, node.first});
                }
            }
            if (i || j) {
                return false;
            }
        }
        return false;
    }
};
// @lc code=end

