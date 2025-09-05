/*
 * @lc app=leetcode id=109 lang=cpp
 *
 * [109] Convert Sorted List to Binary Search Tree
 *
 * https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/
 *
 * algorithms
 * Medium (64.67%)
 * Likes:    7753
 * Dislikes: 169
 * Total Accepted:    630.1K
 * Total Submissions: 969K
 * Testcase Example:  '[-10,-3,0,5,9]'
 *
 * Given the head of a singly linked list where elements are sorted in
 * ascending order, convert it to a height-balanced binary search tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [-10,-3,0,5,9]
 * Output: [0,-3,9,-10,null,5]
 * Explanation: One possible answer is [0,-3,9,-10,null,5], which represents
 * the shown height balanced BST.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = []
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in head is in the range [0, 2 * 10^4].
 * -10^5 <= Node.val <= 10^5
 * 
 * 
 */
#include "template.h"
using namespace std;
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    TreeNode *sortedListToBST1(ListNode *head) {
        if (!head) {
            return nullptr;
        }
        if (!head->next) {
            return new TreeNode(head->val);
        }

        ListNode *f = head, *s = head, *pre = nullptr;
        while (f && f->next) {
            pre = s;
            s = s->next;
            f = f->next->next;
        }
        pre->next = nullptr;

        return new TreeNode(s->val, sortedListToBST(head),
                            sortedListToBST(s->next));
    }

    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) {
            return nullptr;
        }

        int len = 0;
        ListNode *h = head;
        while (head) {
            len++;
            head = head->next;
        }

        auto dfs = [&](this auto &&dfs, int s, int e) -> TreeNode* {
            if (s > e) {
                return nullptr;
            }
            int mid = s + (e - s) / 2;
            auto l = dfs(s, mid - 1);
            TreeNode *root = new TreeNode(h->val, l, nullptr);
            h = h->next;
            auto r = dfs(mid + 1, e);
            root->right = r;
            return root;
        };
        return dfs(0, len - 1);
    }
};
// @lc code=end

