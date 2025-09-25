// template.h
#include <algorithm>
#include <vector>
#include <unordered_map>
#ifndef TEMPLATE_H
#define TEMPLATE_H

// 通用树节点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// 通用链表节点
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 通用节点
class Node {
public:
    int val;
    bool isLeaf;
    Node *left;
    Node *right;
    Node *next;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;
    vector<Node *> children;

    Node()
        : val(0),
          isLeaf(false),
          left(NULL),
          right(NULL),
          next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(bool _val, bool _isLeaf)
        : val(_val),
          isLeaf(_isLeaf),
          topLeft(nullptr),
          topRight(nullptr),
          bottomLeft(nullptr),
          bottomRight(nullptr) {}

    Node(int _val, Node *_next) : val(_val), next(_next) {}

    Node(int _val, vector<Node *> _children)
        : val(_val), children(_children) {}

    Node(int _val, Node *_left, Node *_right)
        : val(_val), left(_left), right(_right) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight,
         Node *_bottomLeft, Node *_bottomRight)
        : val(_val),
          isLeaf(_isLeaf),
          topLeft(_topLeft),
          topRight(_topRight),
          bottomLeft(_bottomLeft),
          bottomRight(_bottomRight) {}
};

// 双向链表节点
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

// 链表
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

// 双向链表
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

// 字典树节点
struct TrieNode {
    bool _is_word;
    unordered_map<char, TrieNode *> _childrens;
};
// 字典树
class Trie {
private:
    TrieNode *_root;

public:
    Trie() {
        _root = new TrieNode();
    }

    // 插入单词
    void insert_word(const string &word){
        TrieNode *node = _root;
        for (char c : word) {
            if (!node->_childrens[c]) {
                node->_childrens[c] = new TrieNode();
            }
            node = node->_childrens[c];
        }
        node->_is_word = true;
    }

    // 单词是否存在
    bool search(const string &word) {
        TrieNode *node = _root;
        for (char c : word) {
            if (!node->_childrens[c]) {
                return false;
            }
            node = node->_childrens[c];
        }
        return node->_is_word;
    }

    // 以prefix为前缀的单词是否存在
    bool search_by_prefix(const string &prefix) {
        TrieNode *node = _root;
        for (char c : prefix) {
            if (!node->_childrens[c]) {
                return false;
            }
            node = node->_childrens[c];
        }
        return true;
    }

    TrieNode *get_root() {
        return _root;
    }
};

#endif