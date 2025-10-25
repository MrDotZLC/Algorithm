/*
 * @lc app=leetcode id=208 lang=cpp
 *
 * [208] Implement Trie (Prefix Tree)
 *
 * https://leetcode.com/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (68.16%)
 * Likes:    12253
 * Dislikes: 158
 * Total Accepted:    1.4M
 * Total Submissions: 2.1M
 * Testcase Example:  '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 *
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to
 * efficiently store and retrieve keys in a dataset of strings. There are
 * various applications of this data structure, such as autocomplete and
 * spellchecker.
 * 
 * Implement the Trie class:
 * 
 * 
 * Trie() Initializes the trie object.
 * void insert(String word) Inserts the string word into the trie.
 * boolean search(String word) Returns true if the string word is in the trie
 * (i.e., was inserted before), and false otherwise.
 * boolean startsWith(String prefix) Returns true if there is a previously
 * inserted string word that has the prefix prefix, and false otherwise.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 * [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 * Output
 * [null, null, true, false, true, null, true]
 * 
 * Explanation
 * Trie trie = new Trie();
 * trie.insert("apple");
 * trie.search("apple");   // return True
 * trie.search("app");     // return False
 * trie.startsWith("app"); // return True
 * trie.insert("app");
 * trie.search("app");     // return True
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= word.length, prefix.length <= 2000
 * word and prefix consist only of lowercase English letters.
 * At most 3 * 10^4 calls in total will be made to insert, search, and
 * startsWith.
 * 
 * 
 */
#include <string>
using namespace std;
// @lc code=start
struct Node {
    Node* son[26];
    bool end = false;
};
class Trie {
public:
    Trie() {
        
    }

    ~Trie() {
        destory(root);
    }
    
    void insert(string word) {
        Node *cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) {
                cur->son[c] = new Node();
            }
            cur = cur->son[c];
        }
        cur->end = true;
    }
    
    bool search(string word) {
        return find(word) == 2;
    }
    
    bool startsWith(string prefix) {
        return find(prefix) != 0;
    }
private:
    Node *root = new Node();
    int find(string word) {
        Node *cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) {
                return 0;
            }
            cur = cur->son[c];
        }
        return cur->end ? 2 : 1; // 2为完全匹配，1为前缀匹配
    }

    void destory(Node *node) {
        if (node == nullptr) {
            return;
        }
        for (Node *son : node->son) {
            if (son) {
                destory(son);
            }
            delete son;
        }
    }   
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

