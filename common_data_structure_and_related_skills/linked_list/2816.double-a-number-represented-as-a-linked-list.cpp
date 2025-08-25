/*
 * @lc app=leetcode id=2816 lang=cpp
 *
 * [2816] Double a Number Represented as a Linked List
 *
 * https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/description/
 *
 * algorithms
 * Medium (61.22%)
 * Likes:    1226
 * Dislikes: 30
 * Total Accepted:    190.2K
 * Total Submissions: 310.6K
 * Testcase Example:  '[1,8,9]'
 *
 * You are given the head of a non-empty linked list representing a
 * non-negative integer without leading zeroes.
 * 
 * Return the head of the linked list after doubling it.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [1,8,9]
 * Output: [3,7,8]
 * Explanation: The figure above corresponds to the given linked list which
 * represents the number 189. Hence, the returned linked list represents the
 * number 189 * 2 = 378.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [9,9,9]
 * Output: [1,9,9,8]
 * Explanation: The figure above corresponds to the given linked list which
 * represents the number 999. Hence, the returned linked list reprersents the
 * number 999 * 2 = 1998. 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the list is in the range [1, 10^4]
 * 0 <= Node.val <= 9
 * The input is generated such that the list represents a number that does not
 * have leading zeros, except the number 0 itself.
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
    ListNode* doubleIt(ListNode* head) {
        return reverse(doubleIt(reverse(head), 0));
    }

    ListNode* doubleIt(ListNode* head, int carry) {
        if (!head) {
            return carry ? new ListNode(carry) : nullptr;
        }
        int val = head->val * 2 + carry;
        head->val = val % 10;
        head->next = doubleIt(head->next, val / 10);
        return head;
    }

    ListNode *reverse(ListNode *head) {
        ListNode *cur = head, *pre = nullptr;
        while (cur) {
            ListNode *nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};
// @lc code=end

