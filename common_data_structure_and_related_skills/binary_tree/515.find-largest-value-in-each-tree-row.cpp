/*
 * @lc app=leetcode id=515 lang=cpp
 *
 * [515] Find Largest Value in Each Tree Row
 *
 * https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
 *
 * algorithms
 * Medium (66.27%)
 * Likes:    4081
 * Dislikes: 129
 * Total Accepted:    494K
 * Total Submissions: 745.6K
 * Testcase Example:  '[1,3,2,5,3,null,9]'
 *
 * Given the root of a binary tree, return an array of the largest value in
 * each row of the tree (0-indexed).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,3,2,5,3,null,9]
 * Output: [1,3,9]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3]
 * Output: [1,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree will be in the range [0, 10^4].
 * -2^31 <= Node.val <= 2^31 - 1
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
class Solution {
public:
    vector<int> largestValues1(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> ans;
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            int mx = q.front()->val;
            int i = q.size();
            while (i--) {
                auto node = q.front();
                q.pop_front();
                mx = max(mx, node->val);
                if (node->left) {
                    q.push_back(node->left);
                }
                if (node->right) {
                    q.push_back(node->right);
                }
            }
            ans.emplace_back(mx);
        }
        return ans;
    }

    vector<int> largestValues(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> ans;
        auto dfs = [&](auto &dfs, TreeNode *node, int depth) -> void {
            if (!node) {
                return;
            }
            if (ans.size() == depth) {
                ans.push_back(node->val);
            } else {
                ans[depth] = max(ans[depth], node->val);
            }
            dfs(dfs, node->left, depth + 1);
            dfs(dfs, node->right, depth + 1);
        };
        dfs(dfs, root, 0);
        return ans;
    }
};
// @lc code=end

