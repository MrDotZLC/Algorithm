/*
 * @lc app=leetcode id=1028 lang=cpp
 *
 * [1028] Recover a Tree From Preorder Traversal
 *
 * https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/description/
 *
 * algorithms
 * Hard (83.31%)
 * Likes:    2271
 * Dislikes: 69
 * Total Accepted:    160.1K
 * Total Submissions: 192.3K
 * Testcase Example:  '"1-2--3--4-5--6--7"'
 *
 * We run a preorder depth-first search (DFS) on the root of a binary tree.
 * 
 * At each node in this traversal, we output D dashes (where D is the depth of
 * this node), then we output the value of this node.  If the depth of a node
 * is D, the depth of its immediate child is D + 1.  The depth of the root node
 * is 0.
 * 
 * If a node has only one child, that child is guaranteed to be the left
 * child.
 * 
 * Given the output traversal of this traversal, recover the tree and return
 * its root.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: traversal = "1-2--3--4-5--6--7"
 * Output: [1,2,5,3,4,6,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: traversal = "1-2--3---4-5--6---7"
 * Output: [1,2,5,3,null,6,null,4,null,7]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: traversal = "1-401--349---90--88"
 * Output: [1,401,null,349,88,90]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the original tree is in the range [1, 1000].
 * 1 <= Node.val <= 10^9
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
    bool is_digit(char c) {
        return c >= '0' && c <= '9';
    }

    TreeNode* recoverFromPreorder(string traversal) {
        vector<TreeNode*> stk;
        int pos = 0;
        while (pos < traversal.size()) {
            int level = 0;
            while (traversal[pos] == '-') {
                ++level;
                ++pos;
            }
            int value = 0;
            while (pos < traversal.size() && is_digit(traversal[pos])) {
                value = value * 10 + (traversal[pos] - '0');
                ++pos;
            }
            TreeNode *node = new TreeNode(value);
            if (level == stk.size()) {
                if (!stk.empty()) {
                    stk.back()->left = node;
                }
            } else {
                while (level != stk.size()) {
                    stk.pop_back();
                }
                stk.back()->right = node;
            }
            stk.push_back(node);
        }
        while (stk.size() > 1) {
            stk.pop_back();
        }
        return stk.back();
    }
};
// @lc code=end

