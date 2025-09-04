/*
 * @lc app=leetcode id=2471 lang=cpp
 *
 * [2471] Minimum Number of Operations to Sort a Binary Tree by Level
 *
 * https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/
 *
 * algorithms
 * Medium (74.27%)
 * Likes:    1220
 * Dislikes: 44
 * Total Accepted:    110.4K
 * Total Submissions: 148.7K
 * Testcase Example:  '[1,4,3,7,6,8,5,null,null,null,null,9,null,10]'
 *
 * You are given the root of a binary tree with unique values.
 * 
 * In one operation, you can choose any two nodes at the same level and swap
 * their values.
 * 
 * Return the minimum number of operations needed to make the values at each
 * level sorted in a strictly increasing order.
 * 
 * The level of a node is the number of edges along the path between it and the
 * root node.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
 * Output: 3
 * Explanation:
 * - Swap 4 and 3. The 2^nd level becomes [3,4].
 * - Swap 7 and 5. The 3^rd level becomes [5,6,8,7].
 * - Swap 8 and 7. The 3^rd level becomes [5,6,7,8].
 * We used 3 operations so return 3.
 * It can be proven that 3 is the minimum number of operations needed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,3,2,7,6,5,4]
 * Output: 3
 * Explanation:
 * - Swap 3 and 2. The 2^nd level becomes [2,3].
 * - Swap 7 and 4. The 3^rd level becomes [4,6,5,7].
 * - Swap 6 and 5. The 3^rd level becomes [4,5,6,7].
 * We used 3 operations so return 3.
 * It can be proven that 3 is the minimum number of operations needed.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = [1,2,3,4,5,6]
 * Output: 0
 * Explanation: Each level is already sorted in increasing order so return
 * 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 10^5].
 * 1 <= Node.val <= 10^5
 * All the values of the tree are unique.
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
    int minimumOperations(TreeNode* root) {
        int ans = 0;
        deque<TreeNode*> q{root};
        while (!q.empty()) {
            vector<int> floor, sorted_idx;
            int idx = 0, n = q.size();
            for (int i = 0; i < n; i++) {
                auto node = q.front();
                q.pop_front();
                floor.push_back(node->val);
                sorted_idx.push_back(idx++);
                if (node->left) {
                    q.push_back(node->left);
                }
                if (node->right) {
                    q.push_back(node->right);
                }
            }
            ranges::sort(sorted_idx, [&](int a, int b) { return floor[a] < floor[b];});
            vector<bool> vis(n, false);
            for (int x : sorted_idx) {
                if (vis[x]) {
                    continue;
                }
                while (!vis[x]) {
                    vis[x] = true;
                    x = sorted_idx[x];
                }
                idx--;
            }
            ans += idx;
        }
        return ans;
    }
};
// @lc code=end

