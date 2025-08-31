/*
 * @lc app=leetcode id=2096 lang=cpp
 *
 * [2096] Step-By-Step Directions From a Binary Tree Node to Another
 *
 * https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/description/
 *
 * algorithms
 * Medium (56.33%)
 * Likes:    3199
 * Dislikes: 165
 * Total Accepted:    223.6K
 * Total Submissions: 396.8K
 * Testcase Example:  '[5,1,2,3,null,6,4]\n3\n6'
 *
 * You are given the root of a binary tree with n nodes. Each node is uniquely
 * assigned a value from 1 to n. You are also given an integer startValue
 * representing the value of the start node s, and a different integer
 * destValue representing the value of the destination node t.
 * 
 * Find the shortest path starting from node s and ending at node t. Generate
 * step-by-step directions of such path as a string consisting of only the
 * uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific
 * direction:
 * 
 * 
 * 'L' means to go from a node to its left child node.
 * 'R' means to go from a node to its right child node.
 * 'U' means to go from a node to its parent node.
 * 
 * 
 * Return the step-by-step directions of the shortest path from node s to node
 * t.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
 * Output: "UURL"
 * Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [2,1], startValue = 2, destValue = 1
 * Output: "L"
 * Explanation: The shortest path is: 2 → 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is n.
 * 2 <= n <= 10^5
 * 1 <= Node.val <= n
 * All the values in the tree are unique.
 * 1 <= startValue, destValue <= n
 * startValue != destValue
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <string>
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
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string path;
        auto dfs = [&](this auto &&dfs, TreeNode *node, int target) -> bool {
            if (!node) {
                return false;
            }
            if (node->val == target) {
                return true;
            }
            path += 'L';
            if (dfs(node->left, target)) {
                return true;
            }
            path[path.length() - 1] = 'R';
            if (dfs(node->right, target)) {
                return true;
            }
            path.pop_back();
            return false;
        };
        dfs(root, startValue);
        string sp = path;
        path = "";
        dfs(root, destValue);
        string dp = path;

        ranges::reverse(sp);
        ranges::reverse(dp);
        while (sp.length() && dp.length() && sp.back() == dp.back()) {
            sp.pop_back();
            dp.pop_back();
        }
        ranges::reverse(dp);
        return string(sp.length(), 'U') + dp;
    }
};
// @lc code=end

