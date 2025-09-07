/*
 * @lc app=leetcode id=297 lang=cpp
 *
 * [297] Serialize and Deserialize Binary Tree
 *
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/
 *
 * algorithms
 * Hard (59.21%)
 * Likes:    10839
 * Dislikes: 422
 * Total Accepted:    1.1M
 * Total Submissions: 1.8M
 * Testcase Example:  '[1,2,3,null,null,4,5]'
 *
 * Serialization is the process of converting a data structure or object into a
 * sequence of bits so that it can be stored in a file or memory buffer, or
 * transmitted across a network connection link to be reconstructed later in
 * the same or another computer environment.
 * 
 * Design an algorithm to serialize and deserialize a binary tree. There is no
 * restriction on how your serialization/deserialization algorithm should work.
 * You just need to ensure that a binary tree can be serialized to a string and
 * this string can be deserialized to the original tree structure.
 * 
 * Clarification: The input/output format is the same as how LeetCode
 * serializes a binary tree. You do not necessarily need to follow this format,
 * so please be creative and come up with different approaches yourself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,null,null,4,5]
 * Output: [1,2,3,null,null,4,5]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = []
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 10^4].
 * -1000 <= Node.val <= 1000
 * 
 * 
 */
#include "template.h"
#include <deque>
#include <string>
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
    string serialize(TreeNode* root) {
        if (!root) {
            return "[]";
        }
        string ans = "[";
        deque<TreeNode*> q{root};
        while (!q.empty()) {
            auto node = q.front();
            q.pop_front();
            if (node) {
                ans += to_string(node->val) + ",";
                q.push_back(node->left);
                q.push_back(node->right);
            } else {
                ans += "null,";
            }
        }
        if (ans.back() == ',') {
            ans.pop_back();
        }
        return ans + ']';
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "[]") return nullptr;
        data = data.substr(1, data.size() - 2);
        vector<string> vals;
        string cur;
        for (char c : data) {
            if (c == ',') {
                vals.push_back(cur);
                cur.clear();
            } else {
                cur.push_back(c);
            }
        }
        if (!cur.empty()) {
            vals.push_back(cur);
        }
        if (vals.empty() || vals[0] == "null") return nullptr; // ✅ 防御性判断

        TreeNode* root = new TreeNode(stoi(vals[0]));
        deque<TreeNode*> q{root};
        int i = 1;
        while (!q.empty() && i < vals.size()) {
            TreeNode* node = q.front();
            q.pop_front();
            if (i < vals.size() && vals[i] != "null") {
                node->left = new TreeNode(stoi(vals[i]));
                q.push_back(node->left);
            }
            i++;
            if (i < vals.size() && vals[i] != "null") {
                node->right = new TreeNode(stoi(vals[i]));
                q.push_back(node->right);
            }
            i++;
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
// @lc code=end

