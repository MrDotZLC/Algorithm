/*
 * @lc app=leetcode id=524 lang=cpp
 *
 * [524] Longest Word in Dictionary through Deleting
 *
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/description/
 *
 * algorithms
 * Medium (51.93%)
 * Likes:    1839
 * Dislikes: 361
 * Total Accepted:    172.3K
 * Total Submissions: 331.4K
 * Testcase Example:  '"abpcplea"\n["ale","apple","monkey","plea"]'
 *
 * Given a string s and a string array dictionary, return the longest string in
 * the dictionary that can be formed by deleting some of the given string
 * characters. If there is more than one possible result, return the longest
 * word with the smallest lexicographical order. If there is no possible
 * result, return the empty string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 * Output: "apple"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abpcplea", dictionary = ["a","b","c"]
 * Output: "a"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * 1 <= dictionary.length <= 1000
 * 1 <= dictionary[i].length <= 1000
 * s and dictionary[i] consist of lowercase English letters.
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
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](string &a, string &b) -> bool {
            if (a.length() != b.length()) {
                return a.length() > b.length(); // descending order by length
            }
            return a < b; // ascending order by char.
        });

        for (auto& sub : dictionary) {
            int i = 0, m = s.size(), j = 0, n = sub.size();
            while (i < m && j < n) {
                if (s[i++] == sub[j]) {
                    ++j;
                } 
            }
            if (j == n) {
                return sub;
            } 
        }
        return "";
    }
};
// @lc code=end

