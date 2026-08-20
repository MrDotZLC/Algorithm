#include <string>
using namespace std;

struct Node {
    Node* son[26];
    bool is_end = false;
};

class Trie {
private:
    Node*root = new Node();

    int find(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) {
                return 0;
            }
            cur = cur->son[c];
        }
        return cur->is_end ? 2 : 1; // 2为完全匹配，1为前缀匹配，0为不匹配
    }

    void destory(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (Node* son : node->son) {
            destory(son);
        }
        delete node;
    }

public:    
    Trie() {}

    ~Trie() {
        destory(root);
    }

    void insert(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) {
                cur->son[c] = new Node();
            }
            cur = cur->son[c];
        }
        cur->is_end = true;
    }

    bool search(string word) {
        return find(word) == 2;
    }

    bool starts_with(string prefix) {
        return find(prefix);
    }

};