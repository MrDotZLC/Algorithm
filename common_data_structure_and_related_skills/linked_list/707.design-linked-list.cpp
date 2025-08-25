/*
 * @lc app=leetcode id=707 lang=cpp
 *
 * [707] Design Linked List
 *
 * https://leetcode.com/problems/design-linked-list/description/
 *
 * algorithms
 * Medium (29.17%)
 * Likes:    2908
 * Dislikes: 1663
 * Total Accepted:    431.5K
 * Total Submissions: 1.5M
 * Testcase Example:  '["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]\n' +
  '[[],[1],[3],[1,2],[1],[1],[1]]'
 *
 * Design your implementation of the linked list. You can choose to use a
 * singly or doubly linked list.
 * A node in a singly linked list should have two attributes: val and next. val
 * is the value of the current node, and next is a pointer/reference to the
 * next node.
 * If you want to use the doubly linked list, you will need one more attribute
 * prev to indicate the previous node in the linked list. Assume all nodes in
 * the linked list are 0-indexed.
 * 
 * Implement the MyLinkedList class:
 * 
 * 
 * MyLinkedList() Initializes the MyLinkedList object.
 * int get(int index) Get the value of the index^th node in the linked list. If
 * the index is invalid, return -1.
 * void addAtHead(int val) Add a node of value val before the first element of
 * the linked list. After the insertion, the new node will be the first node of
 * the linked list.
 * void addAtTail(int val) Append a node of value val as the last element of
 * the linked list.
 * void addAtIndex(int index, int val) Add a node of value val before the
 * index^th node in the linked list. If index equals the length of the linked
 * list, the node will be appended to the end of the linked list. If index is
 * greater than the length, the node will not be inserted.
 * void deleteAtIndex(int index) Delete the index^th node in the linked list,
 * if the index is valid.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get",
 * "deleteAtIndex", "get"]
 * [[], [1], [3], [1, 2], [1], [1], [1]]
 * Output
 * [null, null, null, null, 2, null, 3]
 * 
 * Explanation
 * MyLinkedList myLinkedList = new MyLinkedList();
 * myLinkedList.addAtHead(1);
 * myLinkedList.addAtTail(3);
 * myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
 * myLinkedList.get(1);              // return 2
 * myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
 * myLinkedList.get(1);              // return 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= index, val <= 1000
 * Please do not use the built-in LinkedList library.
 * At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and
 * deleteAtIndex.
 * 
 * 
 */
#include "template.h"
#include <iostream>
using namespace std;
// @lc code=start
class DoublyListNode {
public:
    int val;
    DoublyListNode *prev, *next;
    DoublyListNode () : val(0), prev(nullptr), next(nullptr) {}
    DoublyListNode (int _val) : prev(nullptr), next(nullptr) {
        val = _val;
    }
    DoublyListNode (int _val, DoublyListNode* _prev, DoublyListNode* _next) {
        val = _val;
        prev = _prev;
        next = _next;
    }
};
class MyLinkedList {
public:

    MyLinkedList() {
        size = 0;
        dummy = new DoublyListNode();
        tail = new DoublyListNode();
        dummy->next = tail;
        tail->prev = dummy;
    }

    ~MyLinkedList() {
        DoublyListNode* cur = dummy;
        while (cur) {
            DoublyListNode* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    
    int get(int index) {
        if (index < 0 || index > size - 1) {
            return -1;
        }
        return findNode(index)->val;
    }

    DoublyListNode* findNode(int index) {
        if (index < 0 || index > size) {
            return nullptr;
        }
        DoublyListNode *cur;
        if (index < size / 2) { // 从前往后
            cur = dummy->next;
            for (int i = 0; i < index; ++i) cur = cur->next;
        } else { // 从后往前
            cur = tail;
            for (int i = size; i > index; --i) cur = cur->prev;
        }
        return cur;
    }
    
    void addAtHead(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        DoublyListNode *node = new DoublyListNode(val, dummy, dummy->next);
        dummy->next->prev = node;
        dummy->next = node;
        size++;
    }
    
    void addAtTail(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        DoublyListNode *node = new DoublyListNode(val, tail->prev, tail);
        tail->prev->next = node;
        tail->prev = node;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (val < 0 || val > 1000 || index < 0 || index > size) {
            return;
        }
        auto cur = findNode(index);
        DoublyListNode *node = new DoublyListNode(val, cur->prev, cur);
        cur->prev->next = node;
        cur->prev = node;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index > size - 1) {
            return;
        }
        auto cur = findNode(index);
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        size--;
        delete cur;
    }
private:
    int size;
    DoublyListNode *dummy;
    DoublyListNode *tail;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
// @lc code=end

int main() {
    MyLinkedList* obj = new MyLinkedList();
    obj->addAtHead(5);
    // obj->addAtTail(val);
    obj->addAtIndex(1, 2);
    auto ans = obj->get(1);
    obj->addAtIndex(0, 20);
    obj->addAtIndex(1, 30);
    // obj->deleteAtIndex(index);
    
    cout << ans << endl;
}