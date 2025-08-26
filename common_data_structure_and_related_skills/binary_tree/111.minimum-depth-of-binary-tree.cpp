/*
 * @lc app=leetcode id=111 lang=cpp
 *
 * [111] Minimum Depth of Binary Tree
 *
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (50.92%)
 * Likes:    7644
 * Dislikes: 1352
 * Total Accepted:    1.5M
 * Total Submissions: 2.9M
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, find its minimum depth.
 * 
 * The minimum depth is the number of nodes along the shortest path from the
 * root node down to the nearest leaf node.
 * 
 * Note: A leaf is a node with no children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [2,null,3,null,4,null,5,null,6]
 * Output: 5
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 10^5].
 * -1000 <= Node.val <= 1000
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
    int minDepth1(TreeNode* root) {
        if (!root) {
            return 0;
        }
        auto dfs = [&](auto &dfs, TreeNode *node) -> int {
            if (!node) {
                return 0;
            }
            if (!node->left) {
                return dfs(dfs, node->right) + 1;
            }
            if (!node->right) {
                return dfs(dfs, node->left) + 1;
            }
            return min(dfs(dfs, node->left), dfs(dfs, node->right)) + 1;
        };
        return dfs(dfs, root);
    }

    int minDepth2(TreeNode* root) {
        int ans = INT_MAX;
        auto dfs = [&](auto &dfs, TreeNode *node, int cnt) -> void {
            if (!node) {
                return;
            }
            cnt++;
            if (!node->left && !node->right) {
                ans = min(ans, cnt);
                return;
            }
            dfs(dfs, node->left, cnt);
            dfs(dfs, node->right, cnt);
        };
        dfs(dfs, root, 0);
        return ans == INT_MAX ? 0 : ans;
    }

    int minDepth(TreeNode* root) {
        int ans = INT_MAX;
        auto dfs = [&](this auto &&dfs, TreeNode *node, int cnt) -> void {
            if (!node || ++cnt >= ans) {
                return;
            }
            if (!node->left && !node->right) {
                ans = cnt;
                return;
            }
            dfs(node->left, cnt);
            dfs(node->right, cnt);
        };
        dfs(root, 0);
        return ans == INT_MAX ? 0 : ans;
    }
};
// @lc code=end
