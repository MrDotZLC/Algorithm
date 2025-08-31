/*
 * @lc app=leetcode id=257 lang=cpp
 *
 * [257] Binary Tree Paths
 *
 * https://leetcode.com/problems/binary-tree-paths/description/
 *
 * algorithms
 * Easy (66.83%)
 * Likes:    7024
 * Dislikes: 333
 * Total Accepted:    913.9K
 * Total Submissions: 1.4M
 * Testcase Example:  '[1,2,3,null,5]'
 *
 * Given the root of a binary tree, return all root-to-leaf paths in any
 * order.
 * 
 * A leaf is a node with no children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,null,5]
 * Output: ["1->2->5","1->3"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1]
 * Output: ["1"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 100].
 * -100 <= Node.val <= 100
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        vector<string> path;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (node == nullptr) {
                return;
            }
            path.push_back(to_string(node->val));
            if (node->left == nullptr && node->right == nullptr) { // 叶子节点
                string joined_path;
                for (int i = 0; i < path.size(); i++) {
                    if (i > 0) {
                        joined_path += "->";
                    }
                    joined_path += path[i];
                }
                ans.push_back(joined_path);
            } else {
                dfs(node->left);
                dfs(node->right);
            }
            path.pop_back(); // 恢复现场，撤销上面的 path.push_back(to_string(node->val));
        };
        dfs(root);
        return ans;
    }
};
// @lc code=end

