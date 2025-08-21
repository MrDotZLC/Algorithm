/*
 * @lc app=leetcode id=1290 lang=cpp
 *
 * [1290] Convert Binary Number in a Linked List to Integer
 *
 * https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/description/
 *
 * algorithms
 * Easy (82.26%)
 * Likes:    4614
 * Dislikes: 177
 * Total Accepted:    681.8K
 * Total Submissions: 828.5K
 * Testcase Example:  '[1,0,1]'
 *
 * Given head which is a reference node to a singly-linked list. The value of
 * each node in the linked list is either 0 or 1. The linked list holds the
 * binary representation of a number.
 * 
 * Return the decimal value of the number in the linked list.
 * 
 * The most significant bit is at the head of the linked list.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [1,0,1]
 * Output: 5
 * Explanation: (101) in base 2 = (5) in base 10
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [0]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The Linked List is not empty.
 * Number of nodes will not exceed 30.
 * Each node's value is either 0 or 1.
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
    int getDecimalValue(ListNode* head) {
        int ans = 0;
        ListNode* cur = head;
        while (head) {
            ans = (ans << 1) + head->val;
            head = head->next;
        }
        return ans;
    }
};
// @lc code=end

