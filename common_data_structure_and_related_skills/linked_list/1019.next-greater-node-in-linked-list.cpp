/*
 * @lc app=leetcode id=1019 lang=cpp
 *
 * [1019] Next Greater Node In Linked List
 *
 * https://leetcode.com/problems/next-greater-node-in-linked-list/description/
 *
 * algorithms
 * Medium (62.47%)
 * Likes:    3454
 * Dislikes: 124
 * Total Accepted:    196.6K
 * Total Submissions: 314K
 * Testcase Example:  '[2,1,5]'
 *
 * You are given the head of a linked list with n nodes.
 * 
 * For each node in the list, find the value of the next greater node. That is,
 * for each node, find the value of the first node that is next to it and has a
 * strictly larger value than it.
 * 
 * Return an integer array answer where answer[i] is the value of the next
 * greater node of the i^th node (1-indexed). If the i^th node does not have a
 * next greater node, set answer[i] = 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [2,1,5]
 * Output: [5,5,0]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [2,7,4,3,5]
 * Output: [7,0,5,5,0]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the list is n.
 * 1 <= n <= 10^4
 * 1 <= Node.val <= 10^9
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <stack>
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
    vector<int> nextLargerNodes1(ListNode* head) {
        vector<int> ans;
        stack<int> st;
        for (ListNode *cur = head; cur; cur = cur->next) {
            while (!st.empty() && ans[st.top()] < cur->val) {
                ans[st.top()] = cur->val;
                st.pop();
            }
            st.emplace(ans.size());
            ans.push_back(cur->val);
        }
        while (!st.empty()) {
            ans[st.top()] = 0;
            st.pop();
        }
        return ans;
    }

    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> ans;
        stack<int> st;
        nextLargerNodes(head, 0, ans, st);
        return ans;
    }

    void nextLargerNodes(ListNode* node, int i, vector<int> &ans, stack<int> &st) {
        if (node == nullptr) {
            ans.resize(i);
            return;
        }
        nextLargerNodes(node->next, i + 1, ans, st);
        while (!st.empty() && st.top() <= node->val) {
            st.pop();
        }
        if (!st.empty()) {
            ans[i] = st.top();
        }
        st.push(node->val);
    }
};
// @lc code=end

