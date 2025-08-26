/*
 * @lc app=leetcode id=1315 lang=cpp
 *
 * [1315] Sum of Nodes with Even-Valued Grandparent
 *
 * https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/description/
 *
 * algorithms
 * Medium (85.75%)
 * Likes:    2808
 * Dislikes: 78
 * Total Accepted:    175.2K
 * Total Submissions: 204.3K
 * Testcase Example:  '[6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]'
 *
 * Given the root of a binary tree, return the sum of values of nodes with an
 * even-valued grandparent. If there are no nodes with an even-valued
 * grandparent, return 0.
 * 
 * A grandparent of a node is the parent of its parent if it exists.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
 * Output: 18
 * Explanation: The red nodes are the nodes with even-value grandparent while
 * the blue nodes are the even-value grandparents.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * 1 <= Node.val <= 100
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
    int sumEvenGrandparent(TreeNode* root) {
        int ans = 0;
        auto dfs = [&](auto &dfs, TreeNode *node, TreeNode *grandp, TreeNode *father) -> void {
            if (!node) {
                return;
            }
            if (grandp && grandp->val % 2 == 0) {
                ans += node->val;
            }
            grandp = father;
            father = node;
            dfs(dfs, node->left, grandp, father);
            dfs(dfs, node->right, grandp, father);
        };
        dfs(dfs, root, nullptr, nullptr);
        return ans;
    }
};
// @lc code=end

