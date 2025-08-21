/*
 * @lc app=leetcode id=817 lang=cpp
 *
 * [817] Linked List Components
 *
 * https://leetcode.com/problems/linked-list-components/description/
 *
 * algorithms
 * Medium (57.29%)
 * Likes:    1166
 * Dislikes: 2278
 * Total Accepted:    114.1K
 * Total Submissions: 198.9K
 * Testcase Example:  '[0,1,2,3]\n[0,1,3]'
 *
 * You are given the head of a linked list containing unique integer values and
 * an integer array nums that is a subset of the linked list values.
 * 
 * Return the number of connected components in nums where two values are
 * connected if they appear consecutively in the linked list.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [0,1,2,3], nums = [0,1,3]
 * Output: 2
 * Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected
 * components.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [0,1,2,3,4], nums = [0,3,1,4]
 * Output: 2
 * Explanation: 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3,
 * 4] are the two connected components.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the linked list is n.
 * 1 <= n <= 10^4
 * 0 <= Node.val < n
 * All the values Node.val are unique.
 * 1 <= nums.length <= n
 * 0 <= nums[i] < n
 * All the values of nums are unique.
 * 
 * 
 */
#include "template.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
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
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> set(nums.begin(), nums.end());
        bool flag = false;
        int ans = 0;
        while (head) {
            if (set.count(head->val) && !(head->next && set.count(head->next->val))) {
                ans++;
            }
            head = head->next;
        }
        return ans;
    }
};
// @lc code=end

