/*
 * @lc app=leetcode id=2265 lang=cpp
 *
 * [2265] Count Nodes Equal to Average of Subtree
 *
 * https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/description/
 *
 * algorithms
 * Medium (86.47%)
 * Likes:    2298
 * Dislikes: 56
 * Total Accepted:    179.4K
 * Total Submissions: 207.2K
 * Testcase Example:  '[4,8,5,0,1,null,6]'
 *
 * Given the root of a binary tree, return the number of nodes where the value
 * of the node is equal to the average of the values in its subtree.
 * 
 * Note:
 * 
 * 
 * The average of n elements is the sum of the n elements divided by n and
 * rounded down to the nearest integer.
 * A subtree of root is a tree consisting of root and all of its
 * descendants.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [4,8,5,0,1,null,6]
 * Output: 5
 * Explanation: 
 * For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1
 * + 6) / 6 = 24 / 6 = 4.
 * For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 /
 * 2 = 5.
 * For the node with value 0: The average of its subtree is 0 / 1 = 0.
 * For the node with value 1: The average of its subtree is 1 / 1 = 1.
 * For the node with value 6: The average of its subtree is 6 / 1 = 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1]
 * Output: 1
 * Explanation: For the node with value 1: The average of its subtree is 1 / 1
 * = 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 1000].
 * 0 <= Node.val <= 1000
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
    int averageOfSubtree(TreeNode* root) {
        int ans = 0;
        auto dfs = [&](auto &dfs, TreeNode *node) -> pair<int, int> {
            if (!node) {
                return {0, 0};
            }
            auto l = dfs(dfs, node->left);
            auto r = dfs(dfs, node->right);
            int sum = node->val + l.first + r.first;
            int n = 1 + l.second + r.second;
            ans += (node->val == sum / n);
            return {sum, n};
        };
        dfs(dfs, root);
        return ans;
    }
};
// @lc code=end

