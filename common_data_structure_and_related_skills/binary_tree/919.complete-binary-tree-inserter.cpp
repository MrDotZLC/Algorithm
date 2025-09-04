/*
 * @lc app=leetcode id=919 lang=cpp
 *
 * [919] Complete Binary Tree Inserter
 *
 * https://leetcode.com/problems/complete-binary-tree-inserter/description/
 *
 * algorithms
 * Medium (64.63%)
 * Likes:    1144
 * Dislikes: 120
 * Total Accepted:    63.2K
 * Total Submissions: 97.6K
 * Testcase Example:  '["CBTInserter","insert","insert","get_root"]\n[[[1,2]],[3],[4],[]]'
 *
 * A complete binary tree is a binary tree in which every level, except
 * possibly the last, is completely filled, and all nodes are as far left as
 * possible.
 * 
 * Design an algorithm to insert a new node to a complete binary tree keeping
 * it complete after the insertion.
 * 
 * Implement the CBTInserter class:
 * 
 * 
 * CBTInserter(TreeNode root) Initializes the data structure with the root of
 * the complete binary tree.
 * int insert(int v) Inserts a TreeNode into the tree with value Node.val ==
 * val so that the tree remains complete, and returns the value of the parent
 * of the inserted TreeNode.
 * TreeNode get_root() Returns the root node of the tree.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["CBTInserter", "insert", "insert", "get_root"]
 * [[[1, 2]], [3], [4], []]
 * Output
 * [null, 1, 2, [1, 2, 3, 4]]
 * 
 * Explanation
 * CBTInserter cBTInserter = new CBTInserter([1, 2]);
 * cBTInserter.insert(3);  // return 1
 * cBTInserter.insert(4);  // return 2
 * cBTInserter.get_root(); // return [1, 2, 3, 4]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree will be in the range [1, 1000].
 * 0 <= Node.val <= 5000
 * root is a complete binary tree.
 * 0 <= val <= 5000
 * At most 10^4 calls will be made to insert and get_root.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <deque>
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
class CBTInserter {
public:
    CBTInserter(TreeNode* root) {
        _root = root;
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            auto node = q.front();
            q.pop_front();
            if (!node->left || !node->right) {
                _q.push_back(node);
            }
            if (node->left) {
                q.push_back(node->left);
            }
            if (node->right) {
                q.push_back(node->right);
            }
        }
    }
    
    int insert(int val) {
        auto parent = _q.front();
        TreeNode *node = new TreeNode(val);
        if (parent->left) {
            parent->right = node;
            _q.pop_front();
        } else {
            parent->left = node;
        }
        _q.push_back(node);
        return parent->val;
    }
    
    TreeNode* get_root() {
        return _root;
    }
private:
    TreeNode *_root;
    int _size;
    deque<TreeNode*> _q;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
// @lc code=end

