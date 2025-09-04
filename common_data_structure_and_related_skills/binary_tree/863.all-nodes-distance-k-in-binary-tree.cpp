/*
 * @lc app=leetcode id=863 lang=cpp
 *
 * [863] All Nodes Distance K in Binary Tree
 *
 * https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/
 *
 * algorithms
 * Medium (66.66%)
 * Likes:    11791
 * Dislikes: 267
 * Total Accepted:    622.6K
 * Total Submissions: 930.9K
 * Testcase Example:  '[3,5,1,6,2,0,8,null,null,7,4]\n5\n2'
 *
 * Given the root of a binary tree, the value of a target node target, and an
 * integer k, return an array of the values of all nodes that have a distance k
 * from the target node.
 * 
 * You can return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
 * Output: [7,4,1]
 * Explanation: The nodes that are a distance 2 from the target node (with
 * value 5) have values 7, 4, and 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1], target = 1, k = 3
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 500].
 * 0 <= Node.val <= 500
 * All the values Node.val are unique.
 * target is the value of one of the nodes in the tree.
 * 0 <= k <= 1000
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <deque>
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 1. dfs(find_parent) + bfs √
// 2. dfs(find_parent) + dfs
// 3. dfs(build map) + bfs
// 4. split target tree(find k) and parent tree(find k - 1) 
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        find_parent(root);
        bfs(target, k);
        return ans;
    }

    void find_parent(TreeNode *node) {
        if (node->left != nullptr) {
            _map[node->left->val] = node;
            find_parent(node->left);
        }
        if (node->right != nullptr) {
            _map[node->right->val] = node;
            find_parent(node->right);
        }
    }
    
    void bfs(TreeNode *target, int k) {
        deque<TreeNode*> q{target};
        unordered_set<int> freq;
        int d = 0;
        while (!q.empty()) {
            int n = q.size();
            while (n--) {
                auto node = q.front();
                q.pop_front();
                freq.insert(node->val);
                if (d == k) {
                    ans.push_back(node->val);
                }
                if (node->left && freq.count(node->left->val) == 0) {
                    q.push_back(node->left);
                }
                if (node->right && freq.count(node->right->val) == 0) {
                    q.push_back(node->right);
                }
                if (_map[node->val] && freq.count(_map[node->val]->val) == 0) {
                    q.push_back(_map[node->val]);
                }
            }
            d++;
        }
    }
private:
    unordered_map<int, TreeNode*> _map;
    vector<int> ans;
};
// @lc code=end

