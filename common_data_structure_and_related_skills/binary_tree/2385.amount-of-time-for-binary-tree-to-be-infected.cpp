/*
 * @lc app=leetcode id=2385 lang=cpp
 *
 * [2385] Amount of Time for Binary Tree to Be Infected
 *
 * https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/description/
 *
 * algorithms
 * Medium (64.11%)
 * Likes:    3072
 * Dislikes: 68
 * Total Accepted:    181.6K
 * Total Submissions: 282K
 * Testcase Example:  '[1,5,3,null,4,10,6,9,2]\n3'
 *
 * You are given the root of a binary tree with unique values, and an
 * integer start. At minute 0, an infection starts from the node with
 * value start.
 *
 * Each minute, a node becomes infected if:
 *
 *
 * The node is currently uninfected.
 * The node is adjacent to an infected node.
 *
 *
 * Return the number of minutes needed for the entire tree to be
 * infected.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,5,3,null,4,10,6,9,2], start = 3
 * Output: 4
 * Explanation: The following nodes are infected during:
 * - Minute 0: Node 3
 * - Minute 1: Nodes 1, 10 and 6
 * - Minute 2: Node 5
 * - Minute 3: Node 4
 * - Minute 4: Nodes 9 and 2
 * It takes 4 minutes for the whole tree to be infected so we
 * return 4.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1], start = 1
 * Output: 0
 * Explanation: At minute 0, the only node in the tree is infected so
 * we return 0.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^5].
 * 1 <= Node.val <= 10^5
 * Each node has a unique value.
 * A node with a value of start exists in the tree.
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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x),
 * left(left), right(right) {}
 * };
 */
class Solution {
public:
    int amountOfTime(TreeNode *root, int start) {
        int ans = 0;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> pair<int, bool> {
            if (!node) {
                return {0, false};
            }
            auto l = dfs(node->left);
            auto r = dfs(node->right);

            if (node->val == start) {
                ans = max(ans, max(l.first, r.first));
                return {1, true};
            }

            if (l.second || r.second) {
                ans = max(ans, l.first + r.first);
                return {(l.second ? l.first : r.first) + 1, true};
            }
            return {max(l.first, r.first) + 1, false};
        };
        dfs(root);
        return ans;
    }
};
// @lc code=end
