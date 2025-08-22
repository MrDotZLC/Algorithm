/* LCR 029. 循环有序列表的插入
 同步题目状态

中等
相关标签
premium lock icon
相关企业
给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素
insertVal ，使这个列表仍然是循环升序的。

给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。

如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。

如果列表为空（给定的节点是
null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。



示例 1：




输入：head = [3,4,1], insertVal = 2
输出：[3,4,1,2]
解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3
的节点的指针，我们需要向表中插入元素 2 。新插入的节点应该在 1 和 3
之间，插入之后，整个列表如上图所示，最后返回节点 3 。


示例 2：

输入：head = [], insertVal = 1
输出：[1]
解释：列表为空（给定的节点是
null），创建一个循环有序列表并返回这个节点。 示例 3：

输入：head = [1], insertVal = 0
输出：[1,0]


提示：

0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6


注意：本题与主站 708 题相同：
https://leetcode-cn.com/problems/insert-into-a-sorted-circular-linked-list/
(会员题) */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
#include "template.h"

class Solution {
    public:
    Node *insert(Node *head, int insertVal) {
        Node *node = new Node(insertVal);
        if (!head) {
            node->next = node;
            return node;
        }
        if (head->next == head) {
            head->next = node;
            node->next = head;
            return head;
        }

        Node *cur = head;
        while (cur->next != head) {
            if (cur->val > cur->next->val) {
                if (insertVal >= cur->val || insertVal <= cur->next->val) {
                    break;
                }
            } else {
                if (insertVal >= cur->val && insertVal <= cur->next->val) {
                    break;
                }
            }
            cur = cur->next;
        }
        node->next = cur->next;
        cur->next = node;
        return head;
    }
};