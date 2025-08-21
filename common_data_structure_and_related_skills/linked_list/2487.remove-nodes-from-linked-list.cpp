/*
 * @lc app=leetcode id=2487 lang=cpp
 *
 * [2487] Remove Nodes From Linked List
 *
 * https://leetcode.com/problems/remove-nodes-from-linked-list/description/
 *
 * algorithms
 * Medium (74.41%)
 * Likes:    2300
 * Dislikes: 82
 * Total Accepted:    238.9K
 * Total Submissions: 321K
 * Testcase Example:  '[5,2,13,3,8]'
 *
 * You are given the head of a linked list.
 *
 * Remove every node which has a node with a greater value anywhere to the
 * right side of it.
 *
 * Return the head of the modified linked list.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [5,2,13,3,8]
 * Output: [13,8]
 * Explanation: The nodes that should be removed are 5, 2 and 3.
 * - Node 13 is to the right of node 5.
 * - Node 13 is to the right of node 2.
 * - Node 8 is to the right of node 3.
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,1,1,1]
 * Output: [1,1,1,1]
 * Explanation: Every node has value 1, so no nodes are removed.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of the nodes in the given list is in the range [1, 10^5].
 * 1 <= Node.val <= 10^5
 *
 *
 */
#include "template.h"
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
class Solution {
public:
    ListNode *removeNodes1(ListNode *head) {
        if (head->next == nullptr) {
            return head;
        }
        ListNode *node = removeNodes1(head->next);  // The returned head must be teh largest.
        if (node->val > head->val) {
            return node;  // delete head
        }
        head->next = node;
        return head;
    }

    // reverse linked_list
    ListNode *reverse(ListNode *head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur) {
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    ListNode *removeNodes(ListNode *head) {
        head = reverse(head);
        ListNode *cur = head;
        while (cur->next) {
            if (cur->val > cur->next->val) {
                cur->next = cur->next->next;
            } else {
                cur = cur->next;
            }
        }
        return reverse(head);
    }
};
// @lc code=end
