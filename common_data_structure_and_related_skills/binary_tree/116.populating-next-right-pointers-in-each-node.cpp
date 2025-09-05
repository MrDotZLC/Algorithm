/*
 * @lc app=leetcode id=116 lang=cpp
 *
 * [116] Populating Next Right Pointers in Each Node
 *
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/
 *
 * algorithms
 * Medium (65.66%)
 * Likes:    10231
 * Dislikes: 319
 * Total Accepted:    1.2M
 * Total Submissions: 1.9M
 * Testcase Example:  '[1,2,3,4,5,6,7]'
 *
 * You are given a perfect binary tree where all leaves are on the same level,
 * and every parent has two children. The binary tree has the following
 * definition:
 * 
 * 
 * struct Node {
 * ⁠ int val;
 * ⁠ Node *left;
 * ⁠ Node *right;
 * ⁠ Node *next;
 * }
 * 
 * 
 * Populate each next pointer to point to its next right node. If there is no
 * next right node, the next pointer should be set to NULL.
 * 
 * Initially, all next pointers are set to NULL.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,4,5,6,7]
 * Output: [1,#,2,3,#,4,5,6,7,#]
 * Explanation: Given the above perfect binary tree (Figure A), your function
 * should populate each next pointer to point to its next right node, just like
 * in Figure B. The serialized output is in level order as connected by the
 * next pointers, with '#' signifying the end of each level.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = []
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 2^12 - 1].
 * -1000 <= Node.val <= 1000
 * 
 * 
 * 
 * Follow-up:
 * 
 * 
 * You may only use constant extra space.
 * The recursive approach is fine. You may assume implicit stack space does not
 * count as extra space for this problem.
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
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    // dfs
    Node* connect1(Node* root) {
        vector<Node*> pre;
        auto dfs = [&](auto &dfs, Node *node, int depth) -> void {
            if (!node) {
                return;
            }
            if (pre.size() == depth) {
                pre.push_back(node);
            } else {
                pre[depth]->next = node;
                pre[depth] = node;
            }
            dfs(dfs, node->left, depth + 1);
            dfs(dfs, node->right, depth + 1);
        };
        dfs(dfs, root, 0);
        return root;
    }

    // bfs
    Node* connect2(Node* root) {
        if (!root) {
            return root;
        }
        deque<Node*> q{root};
        while (!q.empty()) {
            Node *pre = nullptr;
            int i = q.size();
            while (i--) {
                auto node = q.front();
                q.pop_front();
                if (pre) {
                    pre->next = node;
                }
                pre = node;
                if (node->left) {
                    q.push_back(node->left);
                }
                if (node->right) {
                    q.push_back(node->right);
                }
            }
        }
        return root;
    }

    // bfs + linked_list
    Node* connect(Node* root) {
        Node dummy;
        Node *cur = root;
        while (cur) {
            dummy.next = nullptr;
            Node *nxt = &dummy;
            while (cur) {
                if (cur->left) {
                    nxt->next = cur->left;
                    nxt = cur->left;
                }
                if (cur->right) {
                    nxt->next = cur->right;
                    nxt = cur->right;
                }
                cur = cur->next;
            }
            cur = dummy.next;
        }
        return root;
    }
};
// @lc code=end

