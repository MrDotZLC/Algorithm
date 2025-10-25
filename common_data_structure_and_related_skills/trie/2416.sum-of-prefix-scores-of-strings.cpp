/*
 * @lc app=leetcode id=2416 lang=cpp
 *
 * [2416] Sum of Prefix Scores of Strings
 *
 * https://leetcode.com/problems/sum-of-prefix-scores-of-strings/description/
 *
 * algorithms
 * Hard (60.72%)
 * Likes:    1186
 * Dislikes: 111
 * Total Accepted:    118.8K
 * Total Submissions: 195.4K
 * Testcase Example:  '["abc","ab","bc","b"]'
 *
 * You are given an array words of size n consisting of non-empty strings.
 * 
 * We define the score of a string term as the number of strings words[i] such
 * that term is a prefix of words[i].
 * 
 * 
 * For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is
 * 2, since "ab" is a prefix of both "ab" and "abc".
 * 
 * 
 * Return an array answer of size n where answer[i] is the sum of scores of
 * every non-empty prefix of words[i].
 * 
 * Note that a string is considered as a prefix of itself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["abc","ab","bc","b"]
 * Output: [5,4,3,2]
 * Explanation: The answer for each string is the following:
 * - "abc" has 3 prefixes: "a", "ab", and "abc".
 * - There are 2 strings with the prefix "a", 2 strings with the prefix "ab",
 * and 1 string with the prefix "abc".
 * The total is answer[0] = 2 + 2 + 1 = 5.
 * - "ab" has 2 prefixes: "a" and "ab".
 * - There are 2 strings with the prefix "a", and 2 strings with the prefix
 * "ab".
 * The total is answer[1] = 2 + 2 = 4.
 * - "bc" has 2 prefixes: "b" and "bc".
 * - There are 2 strings with the prefix "b", and 1 string with the prefix
 * "bc".
 * The total is answer[2] = 2 + 1 = 3.
 * - "b" has 1 prefix: "b".
 * - There are 2 strings with the prefix "b".
 * The total is answer[3] = 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["abcd"]
 * Output: [4]
 * Explanation:
 * "abcd" has 4 prefixes: "a", "ab", "abc", and "abcd".
 * Each prefix has a score of one, so the total is answer[0] = 1 + 1 + 1 + 1 =
 * 4.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 1000
 * 1 <= words[i].length <= 1000
 * words[i] consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        struct Trie {
            Trie* son[26]{};
            int score = 0;
        };
        Trie* root = new Trie();

        for (auto &word : words) {
            auto cur = root;
            for (char c : word) {
                c -= 'a';
                if (cur->son[c] == nullptr) {
                    cur->son[c] = new Trie();
                }
                cur = cur->son[c];
                ++cur->score;
            }
        }

        int n = words.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            auto cur = root;
            for (char c : words[i]) {
                cur = cur->son[c - 'a'];
                ans[i] += cur->score;
            }
        }
        return ans;
    }
};
// @lc code=end

