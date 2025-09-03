/*
 * @lc app=leetcode id=1305 lang=cpp
 *
 * [1305] All Elements in Two Binary Search Trees
 *
 * https://leetcode.com/problems/all-elements-in-two-binary-search-trees/description/
 *
 * algorithms
 * Medium (80.05%)
 * Likes:    3151
 * Dislikes: 98
 * Total Accepted:    248K
 * Total Submissions: 309.6K
 * Testcase Example:  '[2,1,4]\n[1,0,3]'
 *
 * Given two binary search trees root1 and root2, return a list
 * containing all the integers from both trees sorted in ascending
 * order.
 *
 *
 * Example 1:
 *
 *
 * Input: root1 = [2,1,4], root2 = [1,0,3]
 * Output: [0,1,1,2,3,4]
 *
 *
 * Example 2:
 *
 *
 * Input: root1 = [1,null,8], root2 = [8,1]
 * Output: [1,1,8,8]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in each tree is in the range [0, 5000].
 * -10^5 <= Node.val <= 10^5
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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x),
 * left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> getAllElements(TreeNode *root1, TreeNode *root2) {
        auto dfs = [&](this auto &&dfs, TreeNode *node,
                       vector<int> &arr) -> void {
            if (!node) {
                return;
            }
            dfs(node->left, arr);
            arr.push_back(node->val);
            dfs(node->right, arr);
        };

        vector<int> v1, v2;
        vector<int> ans;
        dfs(root1, v1);
        dfs(root2, v2);

        int i1 = 0, i2 = 0;
        while (i1 < v1.size() || i2 < v2.size()) {
            if (i2 == v2.size() ||
                i1 != v1.size() && v1[i1] <= v2[i2])
                ans.emplace_back(v1[i1++]);
            else
                ans.emplace_back(v2[i2++]);
        }
        return ans;
    }
};
// @lc code=end
