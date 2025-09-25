/*
 * @lc app=leetcode id=212 lang=cpp
 *
 * [212] Word Search II
 *
 * https://leetcode.com/problems/word-search-ii/description/
 *
 * algorithms
 * Hard (37.43%)
 * Likes:    9981
 * Dislikes: 501
 * Total Accepted:    832.4K
 * Total Submissions: 2.2M
 * Testcase Example:  '[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]\n' +
  '["oath","pea","eat","rain"]'
 *
 * Given an m x n board of characters and a list of strings words, return all
 * words on the board.
 * 
 * Each word must be constructed from letters of sequentially adjacent cells,
 * where adjacent cells are horizontally or vertically neighboring. The same
 * letter cell may not be used more than once in a word.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: board =
 * [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
 * words = ["oath","pea","eat","rain"]
 * Output: ["eat","oath"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == board.length
 * n == board[i].length
 * 1 <= m, n <= 12
 * board[i][j] is a lowercase English letter.
 * 1 <= words.length <= 3 * 10^4
 * 1 <= words[i].length <= 10
 * words[i] consists of lowercase English letters.
 * All the strings of words are unique.
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
struct TrieNode {
    bool _is_word;
    unordered_map<char, TrieNode *> _childrens;
};

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



class Solution {
public:
    // hash + dfs
    vector<string> findWords1(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size(), n = board[0].size(), N = 10;
        vector<string> ans;
        string path;
        unordered_set<string> set(words.begin(), words.end());
        vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        auto dfs = [&](auto &dfs, int r, int c) -> void {
            if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] == '0' || path.length() > 10){
                return;
            }

            int x = board[r][c];
            path += x;
            board[r][c] = '0';
            if (set.find(path) != set.end()) {
                ans.emplace_back(path);
                set.erase(path);
            }
            for (auto &[row, col] : dir) {
                int nr = r + row, nc = c + col;
                dfs(dfs, nr, nc);
            }
            board[r][c] = x;
            path.pop_back();
        };

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                dfs(dfs, r, c);
            }
        }
        return ans;
    }

    // Tire + dfs
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size(), n = board[0].size();
        vector<string> ans;
        string path;
        vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};


        Trie *root = new Trie();
        for (string &w : words) {
            root->insert_word(w);
        }

        auto dfs = [&](auto &dfs, int r, int c, TrieNode *node) -> void {
            if (r < 0 || r >= m || c < 0 || c >= n){
                return;
            }
            
            int x = board[r][c];

            if (x == '0' || !node->_childrens.count(x)) {
                return;
            }

            node = node->_childrens[x];
            path.push_back(x);

            if (node->_is_word) {
                ans.emplace_back(path);
                node->_is_word = false;
            }

            board[r][c] = '0';
            for (auto &[row, col] : dir) {
                int nr = r + row, nc = c + col;
                dfs(dfs, nr, nc, node);
            }
            board[r][c] = x;
            path.pop_back();
        };

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                dfs(dfs, r, c, root->get_root());
            }
        }
        return ans;
    }
};
// @lc code=end

