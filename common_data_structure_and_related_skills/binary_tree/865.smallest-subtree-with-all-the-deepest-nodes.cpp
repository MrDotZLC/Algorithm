/*
 * @lc app=leetcode id=865 lang=cpp
 *
 * [865] Smallest Subtree with all the Deepest Nodes
 *
 * https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description/
 *
 * algorithms
 * Medium (72.53%)
 * Likes:    2802
 * Dislikes: 382
 * Total Accepted:    167.5K
 * Total Submissions: 230.7K
 * Testcase Example:  '[3,5,1,6,2,0,8,null,null,7,4]'
 *
 * Given the root of a binary tree, the depth of each node is the shortest
 * distance to the root.
 * 
 * Return the smallest subtree such that it contains all the deepest nodes in
 * the original tree.
 * 
 * A node is called the deepest if it has the largest depth possible among any
 * node in the entire tree.
 * 
 * The subtree of a node is a tree consisting of that node, plus the set of all
 * descendants of that node.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4]
 * Output: [2,7,4]
 * Explanation: We return the node with value 2, colored in yellow in the
 * diagram.
 * The nodes coloured in blue are the deepest nodes of the tree.
 * Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node
 * 2 is the smallest subtree among them, so we return it.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1]
 * Output: [1]
 * Explanation: The root is the deepest node in the tree.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [0,1,3,null,2]
 * Output: [2]
 * Explanation: The deepest node in the tree is 2, the valid subtrees are the
 * subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree will be in the range [1, 500].
 * 0 <= Node.val <= 500
 * The values of the nodes in the tree are unique.
 * 
 * 
 * 
 * Note: This question is the same as 1123:
 * https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
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
    TreeNode* subtreeWithAllDeepest1(TreeNode* root) {
        TreeNode *ans = nullptr;
        int max_depth = 0;
        auto dfs = [&](this auto &&dfs, TreeNode *node, int depth) -> int {
            if (!node) {
                return depth - 1;
            }
            max_depth = max(max_depth, depth);
            int l_max_depth = dfs(node->left, depth + 1);
            int r_max_depth = dfs(node->right, depth + 1);
            if (l_max_depth == r_max_depth && l_max_depth == max_depth) {
                ans = node;
            }
            return max(l_max_depth, r_max_depth);
        };
        dfs(root, 1);
        return ans;
    }

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> pair<int, TreeNode*> {
            if (!node) {
                return {0, nullptr};
            }
            auto l = dfs(node->left);
            auto r = dfs(node->right);
            if (l.first > r.first) {
                return {l.first + 1, l.second};
            }
            if (l.first < r.first) {
                return {r.first + 1, r.second};
            }
            return {l.first + 1, node};
        };
        return dfs(root).second;
    }
};
// @lc code=end

