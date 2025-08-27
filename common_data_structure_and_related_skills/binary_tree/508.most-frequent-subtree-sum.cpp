/*
 * @lc app=leetcode id=508 lang=cpp
 *
 * [508] Most Frequent Subtree Sum
 *
 * https://leetcode.com/problems/most-frequent-subtree-sum/description/
 *
 * algorithms
 * Medium (68.06%)
 * Likes:    2341
 * Dislikes: 326
 * Total Accepted:    164.3K
 * Total Submissions: 240.9K
 * Testcase Example:  '[5,2,-3]'
 *
 * Given the root of a binary tree, return the most frequent subtree sum. If
 * there is a tie, return all the values with the highest frequency in any
 * order.
 * 
 * The subtree sum of a node is defined as the sum of all the node values
 * formed by the subtree rooted at that node (including the node itself).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [5,2,-3]
 * Output: [2,-3,4]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [5,2,-5]
 * Output: [2]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * -10^5 <= Node.val <= 10^5
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <unordered_map>
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> ans;
        int freq = 0;
        unordered_map<int, int> cnt;
        auto update = [&](int val) -> void {
            if(++cnt[val] >= freq) {
                if (cnt[val] > freq) {
                    ans.clear();
                }
                ans.push_back(val);
                freq = cnt[val];
            }
        };
        auto dfs = [&](auto &dfs, TreeNode* node) -> int {
            if (!node) {
                return 0;
            }
            int sum = dfs(dfs, node->left) + dfs(dfs, node->right) + node->val;
            update(sum);
            return sum;
        };
        dfs(dfs, root);
        return ans;
    }


};
// @lc code=end

