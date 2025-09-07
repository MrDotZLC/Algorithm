/*
 * @lc app=leetcode id=979 lang=cpp
 *
 * [979] Distribute Coins in Binary Tree
 *
 * https://leetcode.com/problems/distribute-coins-in-binary-tree/description/
 *
 * algorithms
 * Medium (77.17%)
 * Likes:    5992
 * Dislikes: 244
 * Total Accepted:    216.9K
 * Total Submissions: 281K
 * Testcase Example:  '[3,0,0]'
 *
 * You are given the root of a binary tree with n nodes where each node in the
 * tree has node.val coins. There are n coins in total throughout the whole
 * tree.
 * 
 * In one move, we may choose two adjacent nodes and move one coin from one
 * node to another. A move may be from parent to child, or from child to
 * parent.
 * 
 * Return the minimum number of moves required to make every node have exactly
 * one coin.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,0,0]
 * Output: 2
 * Explanation: From the root of the tree, we move one coin to its left child,
 * and one coin to its right child.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [0,3,0]
 * Output: 3
 * Explanation: From the left child of the root, we move two coins to the root
 * [taking two moves]. Then, we move one coin from the root of the tree to the
 * right child.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is n.
 * 1 <= n <= 100
 * 0 <= Node.val <= n
 * The sum of all Node.val is n.
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
    int distributeCoins(TreeNode* root) {
        int ans = 0;
        // auto dfs = [&](auto &dfs, TreeNode *node) -> pair<int, int> {
        //     if (!node) {
        //         return {0, 0};
        //     }
        //     auto [n_l, sum_l] = dfs(dfs, node->left);
        //     auto [n_r, sum_r] = dfs(dfs, node->right);

        //     int n = 1 + n_l + n_r;
        //     int sum = node->val + sum_l + sum_r;
        //     ans += abs(sum - n);
        //     return {n, sum};
        // };

        auto dfs = [&](auto &dfs, TreeNode *node) -> int {
            if (!node) {
                return 0;
            }
            int d = node->val - 1 + dfs(dfs, node->left) +
                        dfs(dfs, node->right);
            ans += abs(d);
            return d;
        };

        dfs(dfs, root);
        return ans;
    }
};
// @lc code=end

