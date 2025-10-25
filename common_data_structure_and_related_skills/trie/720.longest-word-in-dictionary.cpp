/*
 * @lc app=leetcode id=720 lang=cpp
 *
 * [720] Longest Word in Dictionary
 *
 * https://leetcode.com/problems/longest-word-in-dictionary/description/
 *
 * algorithms
 * Medium (53.60%)
 * Likes:    2054
 * Dislikes: 1504
 * Total Accepted:    180.8K
 * Total Submissions: 335K
 * Testcase Example:  '["w","wo","wor","worl","world"]'
 *
 * Given an array of strings words representing an English Dictionary, return
 * the longest word in words that can be built one character at a time by other
 * words in words.
 * 
 * If there is more than one possible answer, return the longest word with the
 * smallest lexicographical order. If there is no answer, return the empty
 * string.
 * 
 * Note that the word should be built from left to right with each additional
 * character being added to the end of a previous word. 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["w","wo","wor","worl","world"]
 * Output: "world"
 * Explanation: The word "world" can be built one character at a time by "w",
 * "wo", "wor", and "worl".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["a","banana","app","appl","ap","apply","apple"]
 * Output: "apple"
 * Explanation: Both "apply" and "apple" can be built from other words in the
 * dictionary. However, "apple" is lexicographically smaller than "apply".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 1000
 * 1 <= words[i].length <= 30
 * words[i] consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Trie {
public:
    Trie() {
        this->children = vector<Trie*>(26, nullptr);
        this->end = false;
    }

    void insert(const string& word) {
        Trie* node = this;
        for (char c : word) {
            int idx = c -'a';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new Trie();
            }
            node = node->children[idx];
        }
        node->end = true;
    }

    bool search(const string& word) {
        Trie* node = this;
        for (char c : word) {
            int idx = c -'a';
            if (node->children[idx] == nullptr || !node->children[idx]->end) {
                return false;
            }
            node = node->children[idx];
        }
        return node && node->end;
    }

private:
    vector<Trie*> children;
    bool end;
};
class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for (auto &word : words) {
            trie.insert(word);
        }
        string ans = "";
        for (auto &word : words) {
            if (trie.search(word) && (word.size() > ans.size() ||
                (word.size() == ans.size() && word < ans))) {
                ans = word;
            }
        }
        return ans;
    }
};
// @lc code=end

