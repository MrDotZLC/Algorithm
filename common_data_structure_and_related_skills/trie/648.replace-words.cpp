/*
 * @lc app=leetcode id=648 lang=cpp
 *
 * [648] Replace Words
 *
 * https://leetcode.com/problems/replace-words/description/
 *
 * algorithms
 * Medium (68.39%)
 * Likes:    3084
 * Dislikes: 219
 * Total Accepted:    308.5K
 * Total Submissions: 450.2K
 * Testcase Example:  '["cat","bat","rat"]\n"the cattle was rattled by the battery"'
 *
 * In English, we have a concept called root, which can be followed by some
 * other word to form another longer word - let's call this word derivative.
 * For example, when the root "help" is followed by the word "ful", we can form
 * a derivative "helpful".
 * 
 * Given a dictionary consisting of many roots and a sentence consisting of
 * words separated by spaces, replace all the derivatives in the sentence with
 * the root forming it. If a derivative can be replaced by more than one root,
 * replace it with the root that has the shortest length.
 * 
 * Return the sentence after the replacement.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled
 * by the battery"
 * Output: "the cat was rat by the bat"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
 * Output: "a a b c"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= dictionary.length <= 1000
 * 1 <= dictionary[i].length <= 100
 * dictionary[i] consists of only lower-case letters.
 * 1 <= sentence.length <= 10^6
 * sentence consists of only lower-case letters and spaces.
 * The number of words in sentence is in the range [1, 1000]
 * The length of each word in sentence is in the range [1, 1000]
 * Every two consecutive words in sentence will be separated by exactly one
 * space.
 * sentence does not have leading or trailing spaces.
 * 
 * 
 */
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
// @lc code=start
struct Node {
    bool end = false;
    Node* son[26];
};
class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Node* root = new Node();
        for (auto &word : dictionary) {
            Node* cur = root;
            for (char c : word) {
                if (cur->son[c - 'a'] == nullptr) {
                    cur->son[c - 'a'] = new Node();
                }
                cur = cur->son[c - 'a'];
            }
            cur->end = true;
        }

        stringstream ss(sentence);
        string s;
        vector<string> words;

        while (getline(ss, s, ' ')) {
            if (s.empty() || s == "") {
                continue;
            }
            words.push_back(find_root(s, root));
        }

        string ans;
        for (auto &w : words) {
            ans += w + " ";
        }
        if (ans.length() > 0) {
            ans.pop_back();
        }
        return ans;
    }

    string find_root(string &word, Node* node) {
        string prefix;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->son[idx]) {
                return word;
            }
            node = node->son[idx];
            prefix += c;
            if (node->end) {
                return prefix;
            }
        }
        return word;
    }
};
// @lc code=end

