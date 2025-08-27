/*
 * @lc app=leetcode id=1530 lang=cpp
 *
 * [1530] Number of Good Leaf Nodes Pairs
 *
 * https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/description/
 *
 * algorithms
 * Medium (71.77%)
 * Likes:    2473
 * Dislikes: 109
 * Total Accepted:    157.6K
 * Total Submissions: 219.7K
 * Testcase Example:  '[1,2,3,null,4]\n3'
 *
 * You are given the root of a binary tree and an integer distance. A pair of
 * two different leaf nodes of a binary tree is said to be good if the length
 * of the shortest path between them is less than or equal to distance.
 * 
 * Return the number of good leaf node pairs in the tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,null,4], distance = 3
 * Output: 1
 * Explanation: The leaf nodes of the tree are 3 and 4 and the length of the
 * shortest path between them is 3. This is the only good pair.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,4,5,6,7], distance = 3
 * Output: 2
 * Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The
 * pair [4,6] is not good because the length of ther shortest path between them
 * is 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
 * Output: 1
 * Explanation: The only good pair is [2,5].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 2^10].
 * 1 <= Node.val <= 100
 * 1 <= distance <= 10
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
    int countPairs(TreeNode* root, int distance) {
        int ans = 0;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> vector<int> {
            if (!node) {
                return {};
            }
            if (!node->left && !node->right) {
                return {0};
            }
            vector<int> ret;
            auto l = dfs(node->left);
            for (int x : l) {
                if (++x > distance) {
                    continue;
                }
                ret.push_back(x);
            }
            auto r = dfs(node->right);
            for (int x : r) {
                if (++x > distance) {
                    continue;
                }
                ret.push_back(x);
            }
            for (int i : l) {
                for (int j : r) {
                    ans += (i + j + 2 <= distance);
                }
            }
            return ret;
        };
        dfs(root);
        return ans;
    }
};
// @lc code=end

