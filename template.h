// template.h
#include <algorithm>
#ifndef TEMPLATE_H
#define TEMPLATE_H

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class DoublyListNode {
public:
    int val;
    DoublyListNode *prev, *next;
    DoublyListNode() : val(0), prev(nullptr), next(nullptr) {}
    DoublyListNode(int _val) : prev(nullptr), next(nullptr) {
        val = _val;
    }
    DoublyListNode(int _val, DoublyListNode *_prev,
                   DoublyListNode *_next) {
        val = _val;
        prev = _prev;
        next = _next;
    }
};

class MyLinkedList {
public:
    MyLinkedList() {
        size = 0;
        dummy = new ListNode();
    }

    ~MyLinkedList() {
        ListNode *cur = dummy;
        while (cur) {
            ListNode *nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    int get(int index) {
        if (index < 0 || index > size - 1) {
            return -1;
        }
        return findPrev(index)->next->val;
    }

    ListNode *findPrev(int index) {
        if (index < 0 || index > size) {
            return nullptr;
        }
        ListNode *pre = dummy;
        while (index--) {
            pre = pre->next;
        }
        return pre;
    }

    void addAtHead(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        ListNode *node = new ListNode(val, dummy->next);
        dummy->next = node;
        size++;
    }

    void addAtTail(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        ListNode *node = new ListNode(val);
        ListNode *cur = dummy;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = node;
        size++;
    }

    void addAtIndex(int index, int val) {
        if (val < 0 || val > 1000 || index < 0 || index > size) {
            return;
        }
        auto pre = findPrev(index);
        ListNode *node = new ListNode(val, pre->next);
        pre->next = node;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > size - 1) {
            return;
        }
        auto pre = findPrev(index);
        ListNode *node = pre->next;
        pre->next = node->next;
        size--;
        delete node;
    }

private:
    int size;
    ListNode *dummy;
};

class MyDoublyLinkedList {
public:
    MyDoublyLinkedList() {
        size = 0;
        dummy = new DoublyListNode();
        tail = new DoublyListNode();
        dummy->next = tail;
        tail->prev = dummy;
    }

    ~MyDoublyLinkedList() {
        DoublyListNode *cur = dummy;
        while (cur) {
            DoublyListNode *nxt = cur->next;
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

    DoublyListNode *findNode(int index) {
        if (index < 0 || index > size) {
            return nullptr;
        }
        DoublyListNode *cur;
        if (index < size / 2) {  // 从前往后
            cur = dummy->next;
            for (int i = 0; i < index; ++i) cur = cur->next;
        } else {  // 从后往前
            cur = tail;
            for (int i = size; i > index; --i) cur = cur->prev;
        }
        return cur;
    }

    void addAtHead(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        DoublyListNode *node =
            new DoublyListNode(val, dummy, dummy->next);
        dummy->next->prev = node;
        dummy->next = node;
        size++;
    }

    void addAtTail(int val) {
        if (val < 0 || val > 1000) {
            return;
        }
        DoublyListNode *node =
            new DoublyListNode(val, tail->prev, tail);
        tail->prev->next = node;
        tail->prev = node;
        size++;
    }

    void addAtIndex(int index, int val) {
        if (val < 0 || val > 1000 || index < 0 || index > size) {
            return;
        }
        auto cur = findNode(index);
        DoublyListNode *node =
            new DoublyListNode(val, cur->prev, cur);
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

#endif