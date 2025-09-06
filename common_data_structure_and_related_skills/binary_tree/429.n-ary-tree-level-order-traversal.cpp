/*
 * @lc app=leetcode id=429 lang=cpp
 *
 * [429] N-ary Tree Level Order Traversal
 *
 * https://leetcode.com/problems/n-ary-tree-level-order-traversal/description/
 *
 * algorithms
 * Medium (71.28%)
 * Likes:    3714
 * Dislikes: 141
 * Total Accepted:    348.2K
 * Total Submissions: 488.3K
 * Testcase Example:  '[1,null,3,2,4,null,5,6]'
 *
 * Given an n-ary tree, return the level order traversal of its nodes' values.
 * 
 * Nary-Tree input serialization is represented in their level order traversal,
 * each group of children is separated by the null value (See examples).
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [[1],[3,2,4],[5,6]]
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: root =
 * [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 10^4]
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <deque>
using namespace std;
// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    // dfs + double arr
    vector<vector<int>> levelOrder1(Node* root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> ans;
        vector<Node*> cur{root};
        while (cur.size()) {
            vector<Node*> nxt;
            vector<int> vals;
            for (auto node : cur) {
                vals.push_back(node->val);
                nxt.insert(nxt.end(), node->children.begin(), node->children.end());
            }
            ans.emplace_back(vals);
            cur = move(nxt);
        }
        return ans;
    }

    // bfs + queue（deque）
    vector<vector<int>> levelOrder(Node* root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> ans;
        deque<Node*> cur{root};
        while (cur.size()) {
            vector<int> vals;
            for (int i = cur.size(); i > 0; i--) {
                auto node = cur.front();
                cur.pop_front();
                vals.push_back(node->val);
                cur.insert(cur.end(), node->children.begin(), node->children.end());
            }
            ans.emplace_back(vals);
        }
        return ans;
    }
};
// @lc code=end

