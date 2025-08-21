/*
 * @lc app=leetcode id=1669 lang=cpp
 *
 * [1669] Merge In Between Linked Lists
 *
 * https://leetcode.com/problems/merge-in-between-linked-lists/description/
 *
 * algorithms
 * Medium (82.41%)
 * Likes:    2204
 * Dislikes: 225
 * Total Accepted:    253.6K
 * Total Submissions: 307.5K
 * Testcase Example:  '[10,1,13,6,9,5]\n3\n4\n[1000000,1000001,1000002]'
 *
 * You are given two linked lists: list1 and list2 of sizes n and m
 * respectively.
 * 
 * Remove list1's nodes from the a^th node to the b^th node, and put list2 in
 * their place.
 * 
 * The blue edges and nodes in the following figure indicate the result:
 * 
 * Build the result list and return its head.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 =
 * [1000000,1000001,1000002]
 * Output: [10,1,13,1000000,1000001,1000002,5]
 * Explanation: We remove the nodes 3 and 4 and put the entire list2 in their
 * place. The blue edges and nodes in the above figure indicate the result.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 =
 * [1000000,1000001,1000002,1000003,1000004]
 * Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
 * Explanation: The blue edges and nodes in the above figure indicate the
 * result.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= list1.length <= 10^4
 * 1 <= a <= b < list1.length - 1
 * 1 <= list2.length <= 10^4
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* preA = list1;
        for (int i = 0; i < a - 1; i++) {
            preA = preA->next;   // 定位到 a-1 节点
        }

        // 从 preA->next 开始删除，直到 b 节点
        ListNode* cur = preA->next;
        for (int i = a; i <= b; i++) {
            ListNode* tmp = cur;
            cur = cur->next;
            delete tmp;          // 释放节点
        }
        ListNode* postB = cur;   // 此时 cur 就是 b+1 节点

        // 找 list2 的尾
        ListNode* tail2 = list2;
        while (tail2->next) {
            tail2 = tail2->next;
        }

        // 重新链接
        preA->next = list2;
        tail2->next = postB;

        return list1;
    }
};
// @lc code=end

