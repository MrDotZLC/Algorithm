/*
 * @lc app=leetcode id=2181 lang=cpp
 *
 * [2181] Merge Nodes in Between Zeros
 *
 * https://leetcode.com/problems/merge-nodes-in-between-zeros/description/
 *
 * algorithms
 * Medium (89.57%)
 * Likes:    2442
 * Dislikes: 50
 * Total Accepted:    318.1K
 * Total Submissions: 355.1K
 * Testcase Example:  '[0,3,1,0,4,5,2,0]'
 *
 * You are given the head of a linked list, which contains a series of integers
 * separated by 0's. The beginning and end of the linked list will have
 * Node.val == 0.
 * 
 * For every two consecutive 0's, merge all the nodes lying in between them
 * into a single node whose value is the sum of all the merged nodes. The
 * modified list should not contain any 0's.
 * 
 * Return the head of the modified linked list.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [0,3,1,0,4,5,2,0]
 * Output: [4,11]
 * Explanation: 
 * The above figure represents the given linked list. The modified list
 * contains
 * - The sum of the nodes marked in green: 3 + 1 = 4.
 * - The sum of the nodes marked in red: 4 + 5 + 2 = 11.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [0,1,0,3,0,2,2,0]
 * Output: [1,3,4]
 * Explanation: 
 * The above figure represents the given linked list. The modified list
 * contains
 * - The sum of the nodes marked in green: 1 = 1.
 * - The sum of the nodes marked in red: 3 = 3.
 * - The sum of the nodes marked in yellow: 2 + 2 = 4.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the list is in the range [3, 2 * 10^5].
 * 0 <= Node.val <= 1000
 * There are no two consecutive nodes with Node.val == 0.
 * The beginning and end of the linked list have Node.val == 0.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <algorithm>
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
class Solution {
public:
    ListNode* mergeNodes1(ListNode* head) {
        int sum = 0;
        ListNode* pre = head, *cur = head->next;
        while (cur) {
            if (cur->val) {
                sum += cur->val;
            } else {
                ListNode* new_node = new ListNode(sum);
                if (head->val == 0) {
                    head = new_node;
                    pre = head;
                } else {
                    pre->next = new_node;
                    pre = new_node;
                }
                sum = 0;
            }
            cur = cur->next;
        }
        return head;
    }

    ListNode* mergeNodes(ListNode* head) {
        ListNode* tail = head;
        for (auto cur = head->next; cur->next; cur = cur->next) {
            if (cur->val) {
                tail->val += cur->val;
            } else {
                tail = tail->next;
                tail->val = 0;
            }
        }
        tail->next = nullptr;
        return head;
    }
};
// @lc code=end

