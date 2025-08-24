/*
 * @lc app=leetcode id=2074 lang=cpp
 *
 * [2074] Reverse Nodes in Even Length Groups
 *
 * https://leetcode.com/problems/reverse-nodes-in-even-length-groups/description/
 *
 * algorithms
 * Medium (61.48%)
 * Likes:    823
 * Dislikes: 362
 * Total Accepted:    38.5K
 * Total Submissions: 62.3K
 * Testcase Example:  '[5,2,6,3,9,1,7,3,8,4]'
 *
 * You are given the head of a linked list.
 * 
 * The nodes in the linked list are sequentially assigned to non-empty groups
 * whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...).
 * The length of a group is the number of nodes assigned to it. In other
 * words,
 * 
 * 
 * The 1^st node is assigned to the first group.
 * The 2^nd and the 3^rd nodes are assigned to the second group.
 * The 4^th, 5^th, and 6^th nodes are assigned to the third group, and so on.
 * 
 * 
 * Note that the length of the last group may be less than or equal to 1 + the
 * length of the second to last group.
 * 
 * Reverse the nodes in each group with an even length, and return the head of
 * the modified linked list.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [5,2,6,3,9,1,7,3,8,4]
 * Output: [5,6,2,3,9,1,4,8,3,7]
 * Explanation:
 * - The length of the first group is 1, which is odd, hence no reversal
 * occurs.
 * - The length of the second group is 2, which is even, hence the nodes are
 * reversed.
 * - The length of the third group is 3, which is odd, hence no reversal
 * occurs.
 * - The length of the last group is 4, which is even, hence the nodes are
 * reversed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [1,1,0,6]
 * Output: [1,0,1,6]
 * Explanation:
 * - The length of the first group is 1. No reversal occurs.
 * - The length of the second group is 2. The nodes are reversed.
 * - The length of the last group is 1. No reversal occurs.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: head = [1,1,0,6,5]
 * Output: [1,0,1,5,6]
 * Explanation:
 * - The length of the first group is 1. No reversal occurs.
 * - The length of the second group is 2. The nodes are reversed.
 * - The length of the last group is 2. The nodes are reversed.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the list is in the range [1, 10^5].
 * 0 <= Node.val <= 10^5
 * 
 * 
 */
#include "template.h"
#include <vector>
// #include <algorithm>
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
    ListNode* reverseEvenLengthGroups1(ListNode* head) {
        ListNode dummy(0, head);
        ListNode *cur = head, *p = &dummy;
        int group_size = 1;
        while (cur) {
            ListNode *next_group_start = cur;
            int cnt = 0;
            while (next_group_start && cnt < group_size) {
                next_group_start = next_group_start->next;
                cnt++;
            }

            if (cnt % 2) {
                for (int i = 0; i < cnt; i++) {
                    p = cur;
                    cur = cur->next;
                }
            } else {
                ListNode *pre = next_group_start;
                ListNode *cur_0 = cur;
                for (int i = 0; i < cnt; i++) {
                    ListNode *nxt = cur_0->next;
                    cur_0->next = pre;
                    pre = cur_0;
                    cur_0 = nxt;
                }
                p->next = pre;
                p = cur;
                cur = next_group_start;
            }
            group_size++;
        }
        return dummy.next;
    }

    ListNode* reverseEvenLengthGroups(ListNode* head) {
        vector<ListNode*> v;
        ListNode *cur = head;
        int num = 1;
        while (cur) {
            v.emplace_back(cur);
            if (v.size() == num || cur->next == nullptr) {
                int n = v.size();
                if (n % 2 == 0) {
                    for (int i = 0; i < n / 2; i++) {
                        swap(v[i]->val, v[n - 1 - i]->val);
                    }
                }
                v.clear();
                ++num;
            }
            cur = cur->next;
        }
        return head;
    }
};
// @lc code=end

