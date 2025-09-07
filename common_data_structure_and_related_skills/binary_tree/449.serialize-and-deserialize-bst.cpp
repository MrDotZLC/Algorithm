/*
 * @lc app=leetcode id=449 lang=cpp
 *
 * [449] Serialize and Deserialize BST
 *
 * https://leetcode.com/problems/serialize-and-deserialize-bst/description/
 *
 * algorithms
 * Medium (58.72%)
 * Likes:    3563
 * Dislikes: 180
 * Total Accepted:    261.5K
 * Total Submissions: 444.2K
 * Testcase Example:  '[2,1,3]'
 *
 * Serialization is converting a data structure or object into a sequence of
 * bits so that it can be stored in a file or memory buffer, or transmitted
 * across a network connection link to be reconstructed later in the same or
 * another computer environment.
 * 
 * Design an algorithm to serialize and deserialize a binary search tree. There
 * is no restriction on how your serialization/deserialization algorithm should
 * work. You need to ensure that a binary search tree can be serialized to a
 * string, and this string can be deserialized to the original tree structure.
 * 
 * The encoded string should be as compact as possible.
 * 
 * 
 * Example 1:
 * Input: root = [2,1,3]
 * Output: [2,1,3]
 * Example 2:
 * Input: root = []
 * Output: []
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 10^4].
 * 0 <= Node.val <= 10^4
 * The input tree is guaranteed to be a binary search tree.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        if (root == nullptr) {
            return "";
        }
        ostringstream out;
        dfs_build(root, out);
        string ans = out.str();
        if (!ans.empty()) {
            ans.pop_back();
        }
        return ans;
    }

    void dfs_build(TreeNode* root, ostringstream& out) {
        if (!root) return;
        out << root->val << ",";
        dfs_build(root->left, out);
        dfs_build(root->right, out);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") {
            return nullptr;
        }
        vector<int> vals;
        string token;
        stringstream ss(data);
        while (getline(ss, token, ',')) {
            vals.push_back(stoi(token));
        }
        int idx = 0;
        return dfs_rebuild(vals, idx, INT_MIN, INT_MAX);
    }

    TreeNode* dfs_rebuild(const vector<int>& vals, int& idx, int low, int high) {
        if (idx >= vals.size()) return nullptr;
        int v = vals[idx];
        if (v < low || v > high) return nullptr;

        TreeNode* root = new TreeNode(v);
        idx++;
        root->left = dfs_rebuild(vals, idx, low, v);
        root->right = dfs_rebuild(vals, idx, v, high);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
// @lc code=end

