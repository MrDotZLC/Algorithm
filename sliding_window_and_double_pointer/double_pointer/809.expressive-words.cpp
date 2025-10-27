/*
 * @lc app=leetcode id=809 lang=cpp
 *
 * [809] Expressive Words
 *
 * https://leetcode.com/problems/expressive-words/description/
 *
 * algorithms
 * Medium (46.43%)
 * Likes:    896
 * Dislikes: 1938
 * Total Accepted:    129.4K
 * Total Submissions: 278.6K
 * Testcase Example:  '"heeellooo"\n["hello", "hi", "helo"]'
 *
 * Sometimes people repeat letters to represent extra feeling. For
 * example:
 * 
 * 
 * "hello" -> "heeellooo"
 * "hi" -> "hiiii"
 * 
 * 
 * In these strings like "heeellooo", we have groups of adjacent letters that
 * are all the same: "h", "eee", "ll", "ooo".
 * 
 * You are given a string s and an array of query strings words. A query word
 * is stretchy if it can be made to be equal to s by any number of applications
 * of the following extension operation: choose a group consisting of
 * characters c, and add some number of characters c to the group so that the
 * size of the group is three or more.
 * 
 * 
 * For example, starting with "hello", we could do an extension on the group
 * "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has a
 * size less than three. Also, we could do another extension like "ll" ->
 * "lllll" to get "helllllooo". If s = "helllllooo", then the query word
 * "hello" would be stretchy because of these two extension operations: query =
 * "hello" -> "hellooo" -> "helllllooo" = s.
 * 
 * 
 * Return the number of query strings that are stretchy.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "heeellooo", words = ["hello", "hi", "helo"]
 * Output: 1
 * Explanation: 
 * We can extend "e" and "o" in the word "hello" to get "heeellooo".
 * We can't extend "helo" to get "heeellooo" because the group "ll" is not size
 * 3 or more.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "zzzzzyyyyy", words = ["zzyy","zy","zyy"]
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length, words.length <= 100
 * 1 <= words[i].length <= 100
 * s and words[i] consist of lowercase letters.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        auto check = [](string&s, string& t) -> int {
            int m = s.size(), n = t.size();
            if (n > m) return 0;
            int i = 0, j = 0;
            while (i < m && j < n) {
                if (s[i] != t[j]) return 0;
                int k = i;
                while (k < m && s[k] == s[i]) ++k;
                int c1 = k - i;
                i = k, k = j;
                while (k < n && t[k] == t[j]) ++k;
                int c2 = k - j;
                j = k;
                if (c1 < c2 || (c1 < 3 && c1 != c2)) return 0;
            }
            return i == m && j == n;
        };

        int ans = 0;
        for (string &word : words) {
            ans += check(s, word);
        }
        return ans;
    }

};
// @lc code=end

int main() {
    Solution sol;

    // vector<string> words = {"dinnssoo","ddinso","ddiinnso","ddiinnssoo","ddiinso","dinsoo","ddiinsso","dinssoo","dinso"};
    // sol.expressiveWords("dddiiiinnssssssoooo", words);
    vector<string> words = {"hellllo"};
    sol.expressiveWords("heeelllooo", words);
}