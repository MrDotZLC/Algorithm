/*
 * @lc app=leetcode id=1932 lang=cpp
 *
 * [1932] Merge BSTs to Create Single BST
 *
 * https://leetcode.com/problems/merge-bsts-to-create-single-bst/description/
 *
 * algorithms
 * Hard (36.16%)
 * Likes:    626
 * Dislikes: 46
 * Total Accepted:    13.3K
 * Total Submissions: 36.5K
 * Testcase Example:  '[[2,1],[3,2,5],[5,4]]'
 *
 * You are given n BST (binary search tree) root nodes for n separate BSTs
 * stored in an array trees (0-indexed). Each BST in trees has at most 3 nodes,
 * and no two roots have the same value. In one operation, you can:
 * 
 * 
 * Select two distinct indices i and j such that the value stored at one of the
 * leaves of trees[i] is equal to the root value of trees[j].
 * Replace the leaf node in trees[i] with trees[j].
 * Remove trees[j] from trees.
 * 
 * 
 * Return the root of the resulting BST if it is possible to form a valid BST
 * after performing n - 1 operations, or null if it is impossible to create a
 * valid BST.
 * 
 * A BST (binary search tree) is a binary tree where each node satisfies the
 * following property:
 * 
 * 
 * Every node in the node's left subtree has a value strictly less than the
 * node's value.
 * Every node in the node's right subtree has a value strictly greater than the
 * node's value.
 * 
 * 
 * A leaf is a node that has no children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: trees = [[2,1],[3,2,5],[5,4]]
 * Output: [3,2,5,1,null,4]
 * Explanation:
 * In the first operation, pick i=1 and j=0, and merge trees[0] into trees[1].
 * Delete trees[0], so trees = [[3,2,5,1],[5,4]].
 * 
 * In the second operation, pick i=0 and j=1, and merge trees[1] into trees[0].
 * Delete trees[1], so trees = [[3,2,5,1,null,4]].
 * 
 * The resulting tree, shown above, is a valid BST, so return its root.
 * 
 * Example 2:
 * 
 * 
 * Input: trees = [[5,3,8],[3,2,6]]
 * Output: []
 * Explanation:
 * Pick i=0 and j=1 and merge trees[1] into trees[0].
 * Delete trees[1], so trees = [[5,3,8,2,6]].
 * 
 * The resulting tree is shown above. This is the only valid operation that can
 * be performed, but the resulting tree is not a valid BST, so return null.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: trees = [[5,4],[3]]
 * Output: []
 * Explanation: It is impossible to perform any operations.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == trees.length
 * 1 <= n <= 5 * 10^4
 * The number of nodes in each tree is in the range [1, 3].
 * Each node in the input may have children but no grandchildren.
 * No two roots of trees have the same value.
 * All the trees in the input are valid BSTs.
 * 1 <= TreeNode.val <= 5 * 10^4.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
public:
    unordered_map<int, TreeNode*> root;
    void dfs(TreeNode *node) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            auto it = root.find(node->val);
            if (it != root.end()) {
                node->left = it->second->left;
                node->right = it->second->right;
                root.erase(it);
            }
        }
        dfs(node->left);
        dfs(node->right);
    }
    void dfs(TreeNode *node, vector<int> &seq) {
        if (node == nullptr) {
            return;
        }
        dfs(node->left, seq);
        seq.emplace_back(node->val);
        dfs(node->right, seq);
    }
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        // 检查条件一
        unordered_set<int> leaf_value;
        for (auto t : trees) {
            if (t->left) { 
                if(leaf_value.insert(t->left->val).second == false){
                    return nullptr;
                }
            }
            if (t->right) {
                if (leaf_value.insert(t->right->val).second == false) {
                    return nullptr;
                }
            }
        }
        // 检查条件二
        int include = 0;
        TreeNode *final_root = nullptr;
        for (auto t : trees) {
            if (leaf_value.count(t->val)) {
                include++;
            } else {
                final_root = t;
            }
        }
        if (include+1 != trees.size()) {
            return nullptr;
        }
        // 检查完成

        // 构造 node->val 到 node 的映射
        for (auto t : trees) {
            if (t != final_root) {
                root[t->val] = t; 
            }
        }
        // 开始合并
        dfs(final_root);
        if (!root.empty()) {
            return nullptr;
        }
        // 中序遍历检查
        vector<int> seq;
        dfs(final_root, seq);
        for (int i = 1; i < seq.size(); i++) {
            if (seq[i-1] >= seq[i]) {
                return nullptr;
            }
        }
        return final_root;
    }
};
// @lc code=end

