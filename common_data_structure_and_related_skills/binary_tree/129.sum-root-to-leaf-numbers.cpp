/*
 * @lc app=leetcode id=129 lang=cpp
 *
 * [129] Sum Root to Leaf Numbers
 *
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
 *
 * algorithms
 * Medium (68.70%)
 * Likes:    8481
 * Dislikes: 150
 * Total Accepted:    1.2M
 * Total Submissions: 1.7M
 * Testcase Example:  '[1,2,3]'
 *
 * You are given the root of a binary tree containing digits from 0 to 9 only.
 * 
 * Each root-to-leaf path in the tree represents a number.
 * 
 * 
 * For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
 * 
 * 
 * Return the total sum of all root-to-leaf numbers. Test cases are generated
 * so that the answer will fit in a 32-bit integer.
 * 
 * A leaf node is a node with no children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3]
 * Output: 25
 * Explanation:
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Therefore, sum = 12 + 13 = 25.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [4,9,0,5,1]
 * Output: 1026
 * Explanation:
 * The root-to-leaf path 4->9->5 represents the number 495.
 * The root-to-leaf path 4->9->1 represents the number 491.
 * The root-to-leaf path 4->0 represents the number 40.
 * Therefore, sum = 495 + 491 + 40 = 1026.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 1000].
 * 0 <= Node.val <= 9
 * The depth of the tree will not exceed 10.
 * 
 * 
 */
#include "template.h"
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
    int sumNumbers(TreeNode* root) {
        int ans = 0;
        auto dfs = [&](auto &dfs, TreeNode *node, int sum) -> void {
            if (!node) {
                return;
            }
            if (!node->left && !node->right) {
                ans += sum * 10 + node->val;
                return;
            }
            dfs(dfs, node->left, sum * 10 + node->val);
            dfs(dfs, node->right, sum * 10 + node->val);
        };
        dfs(dfs, root, 0);
        return ans;
    }
};
// @lc code=end
