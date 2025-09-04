/*
 * @lc app=leetcode id=2583 lang=cpp
 *
 * [2583] Kth Largest Sum in a Binary Tree
 *
 * https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/description/
 *
 * algorithms
 * Medium (59.19%)
 * Likes:    1041
 * Dislikes: 38
 * Total Accepted:    170.5K
 * Total Submissions: 288.3K
 * Testcase Example:  '[5,8,9,2,1,3,7,4,6]\n2'
 *
 * You are given the root of a binary tree and a positive integer k.
 * 
 * The level sum in the tree is the sum of the values of the nodes that are on
 * the same level.
 * 
 * Return the k^th largest level sum in the tree (not necessarily distinct). If
 * there are fewer than k levels in the tree, return -1.
 * 
 * Note that two nodes are on the same level if they have the same distance
 * from the root.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [5,8,9,2,1,3,7,4,6], k = 2
 * Output: 13
 * Explanation: The level sums are the following:
 * - Level 1: 5.
 * - Level 2: 8 + 9 = 17.
 * - Level 3: 2 + 1 + 3 + 7 = 13.
 * - Level 4: 4 + 6 = 10.
 * The 2^nd largest level sum is 13.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,null,3], k = 1
 * Output: 3
 * Explanation: The largest level sum is 3.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is n.
 * 2 <= n <= 10^5
 * 1 <= Node.val <= 10^6
 * 1 <= k <= n
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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        if (!root) {
            return {};
        }
        vector<long long> ans;
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            long long sum = 0LL;
            int i = q.size();
            while (i--) {
                auto node = q.front();
                q.pop_front();
                sum += node->val;
                if (node->left) {
                    q.push_back(node->left);
                }
                if (node->right) {
                    q.push_back(node->right);
                }
            }
            ans.push_back(sum);
        }
        int n = ans.size();
        if (n < k) {
            return -1;
        }
        ranges::sort(ans);
        return ans[n - k];
    }
};
// @lc code=end

