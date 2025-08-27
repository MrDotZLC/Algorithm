/*
 * @lc app=leetcode id=3319 lang=cpp
 *
 * [3319] K-th Largest Perfect Subtree Size in Binary Tree
 *
 * https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/description/
 *
 * algorithms
 * Medium (61.10%)
 * Likes:    118
 * Dislikes: 11
 * Total Accepted:    25.7K
 * Total Submissions: 42K
 * Testcase Example:  '[5,3,6,5,2,5,7,1,8,null,null,6,8]\n2'
 *
 * You are given the root of a binary tree and an integer k.
 * 
 * Return an integer denoting the size of the k^th largest perfect binary
 * subtree, or -1 if it doesn't exist.
 * 
 * A perfect binary tree is a tree where all leaves are on the same level, and
 * every parent has two children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * 
 * The roots of the perfect binary subtrees are highlighted in black. Their
 * sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
 * The 2^nd largest size is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,4,5,6,7], k = 1
 * 
 * Output: 7
 * 
 * Explanation:
 * 
 * 
 * 
 * The sizes of the perfect binary subtrees in non-increasing order are [7, 3,
 * 3, 1, 1, 1, 1]. The size of the largest perfect binary subtree is 7.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [1,2,3,null,4], k = 3
 * 
 * Output: -1
 * 
 * Explanation:
 * 
 * 
 * 
 * The sizes of the perfect binary subtrees in non-increasing order are [1, 1].
 * There are fewer than 3 perfect binary subtrees.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 2000].
 * 1 <= Node.val <= 2000
 * 1 <= k <= 1024
 * 
 * 
 */
#include "template.h"
#include <vector>
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
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        vector<int> v;
        auto dfs = [&](auto &dfs, TreeNode *node) -> pair<bool, int> {
            if (!node) {
                return {true, 0};
            }
            auto l = dfs(dfs, node->left);
            auto r = dfs(dfs, node->right);
            if (l.first && r.first && l.second == r.second) {
                v.push_back(l.second * 2 + 1);
                return {true, l.second * 2 + 1};
            }
            return {false, 0};
        };
        dfs(dfs, root);
        ranges::sort(v, greater<>());
        return v.size() < k ? -1 : v[k - 1];
    }
};
// @lc code=end

