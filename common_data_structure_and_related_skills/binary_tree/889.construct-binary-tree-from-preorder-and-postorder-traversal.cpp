/*
 * @lc app=leetcode id=889 lang=cpp
 *
 * [889] Construct Binary Tree from Preorder and Postorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/
 *
 * algorithms
 * Medium (78.02%)
 * Likes:    3351
 * Dislikes: 157
 * Total Accepted:    210.3K
 * Total Submissions: 269.5K
 * Testcase Example:  '[1,2,4,5,3,6,7]\n[4,5,2,6,7,3,1]'
 *
 * Given two integer arrays, preorder and postorder where preorder is the
 * preorder traversal of a binary tree of distinct values and postorder is the
 * postorder traversal of the same tree, reconstruct and return the binary
 * tree.
 * 
 * If there exist multiple answers, you can return any of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
 * Output: [1,2,3,4,5,6,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: preorder = [1], postorder = [1]
 * Output: [1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= preorder.length <= 30
 * 1 <= preorder[i] <= preorder.length
 * All the values of preorder are unique.
 * postorder.length == preorder.length
 * 1 <= postorder[i] <= postorder.length
 * All the values of postorder are unique.
 * It is guaranteed that preorder and postorder are the preorder traversal and
 * postorder traversal of the same binary tree.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <unordered_map>
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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < n; i++) {
            idx[postorder[i]] = i;
        }

        auto dfs = [&](auto &dfs, int pre_l, int pre_r, int post_l, int post_r) -> TreeNode* {
            if (pre_l == pre_r) {
                return nullptr;
            }
            if (pre_r - pre_l == 1) {
                return new TreeNode(preorder[pre_l], nullptr, nullptr);
            }
            int l_size = idx[preorder[pre_l + 1]] - post_l + 1;
            TreeNode *l = dfs(dfs, pre_l + 1, pre_l + 1 + l_size, post_l, post_l + l_size);
            TreeNode *r = dfs(dfs, pre_l + 1 + l_size, pre_r, post_l + l_size, post_r - 2);
            return new TreeNode(preorder[pre_l], l, r);
        };

        return dfs(dfs, 0, n, 0, n);
    }
};
// @lc code=end

