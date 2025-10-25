/*
 * @lc app=leetcode id=820 lang=cpp
 *
 * [820] Short Encoding of Words
 *
 * https://leetcode.com/problems/short-encoding-of-words/description/
 *
 * algorithms
 * Medium (60.58%)
 * Likes:    1775
 * Dislikes: 664
 * Total Accepted:    102.9K
 * Total Submissions: 169.5K
 * Testcase Example:  '["time","me","bell"]'
 *
 * A valid encoding of an array of words is any reference string s and array of
 * indices indices such that:
 * 
 * 
 * words.length == indices.length
 * The reference string s ends with the '#' character.
 * For each index indices[i], the substring of s starting from indices[i] and
 * up to (but not including) the next '#' character is equal to words[i].
 * 
 * 
 * Given an array of words, return the length of the shortest reference string
 * s possible of any valid encoding of words.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["time", "me", "bell"]
 * Output: 10
 * Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2,
 * 5].
 * words[0] = "time", the substring of s starting from indices[0] = 0 to the
 * next '#' is underlined in "time#bell#"
 * words[1] = "me", the substring of s starting from indices[1] = 2 to the next
 * '#' is underlined in "time#bell#"
 * words[2] = "bell", the substring of s starting from indices[2] = 5 to the
 * next '#' is underlined in "time#bell#"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["t"]
 * Output: 2
 * Explanation: A valid encoding would be s = "t#" and indices = [0].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 2000
 * 1 <= words[i].length <= 7
 * words[i] consists of only lowercase letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
struct Node {
    Node* son[26]{};
    bool end = false;
};
class Solution {
public:
    // 排序+字典树
    int minimumLengthEncoding1(vector<string>& words) {
        int ans = 0;
        ranges::sort(words, [](const string& a, const string& b){
            int n = a.length(), m = b.length();
            for (int i = 0; i < min(n, m); i++) {
                if (a[n - 1 - i] != b[m - 1 - i]) {
                    return a[n - 1 - i] < b[m - 1 - i];
                }
            }
            return n > m; 
        });

        Node* root = new Node();
        for (const string& word : words) {
            Node* cur = root;
            ans += word.length() + 1;
            bool flag = true;
            for (int i = word.length() - 1; i >= 0; i--) {
                int idx = word[i] - 'a';
                if (cur->son[idx] == nullptr) {
                    cur->son[idx] = new Node();
                    flag = false;
                }
                cur = cur->son[idx];
            }
            if (flag) {
                ans -= word.size() + 1;
            }
            cur->end = true;
        }
        return ans;
    }

    // 排序+库函数
    int minimumLengthEncoding(vector<string>& words) {
        ranges::sort(words, [](const string& a, const string& b){
            int n = a.length(), m = b.length();
            for (int i = 0; i < min(n, m); i++) {
                if (a[n - 1 - i] != b[m - 1 - i]) {
                    return a[n - 1 - i] < b[m - 1 - i];
                }
            }
            return n < m; 
        });
        int ans = words.back().length() + 1;
        for (int i = 0; i < words.size() - 1; i++) {
            if (!words[i + 1].ends_with(words[i])) {
                ans += words[i].length() + 1;
            }
        }
        return ans;
    }
};
// @lc code=end

