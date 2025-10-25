/*
 * @lc app=leetcode id=1268 lang=cpp
 *
 * [1268] Search Suggestions System
 *
 * https://leetcode.com/problems/search-suggestions-system/description/
 *
 * algorithms
 * Medium (65.06%)
 * Likes:    5059
 * Dislikes: 261
 * Total Accepted:    416.5K
 * Total Submissions: 639.4K
 * Testcase Example:  '["mobile","mouse","moneypot","monitor","mousepad"]\n"mouse"'
 *
 * You are given an array of strings products and a string searchWord.
 * 
 * Design a system that suggests at most three product names from products
 * after each character of searchWord is typed. Suggested products should have
 * common prefix with searchWord. If there are more than three products with a
 * common prefix return the three lexicographically minimums products.
 * 
 * Return a list of lists of the suggested products after each character of
 * searchWord is typed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: products = ["mobile","mouse","moneypot","monitor","mousepad"],
 * searchWord = "mouse"
 * Output:
 * [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
 * Explanation: products sorted lexicographically =
 * ["mobile","moneypot","monitor","mouse","mousepad"].
 * After typing m and mo all products match and we show user
 * ["mobile","moneypot","monitor"].
 * After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: products = ["havana"], searchWord = "havana"
 * Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
 * Explanation: The only word "havana" will be always suggested while typing
 * the search word.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= products.length <= 1000
 * 1 <= products[i].length <= 3000
 * 1 <= sum(products[i].length) <= 2 * 10^4
 * All the strings of products are unique.
 * products[i] consists of lowercase English letters.
 * 1 <= searchWord.length <= 1000
 * searchWord consists of lowercase English letters.
 * 
 * 
 */
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
struct Node {
    Node* son[26]{};
    priority_queue<string> pq;
};
class Solution {
public:
    // 字典树+最小堆
    vector<vector<string>> suggestedProducts1(vector<string>& products, string searchWord) {
        Node* root = new Node();
        // 初始化字典树
        for (const string& word : products) {
            Node* cur = root;
            for (char c : word) {
                c -= 'a';
                if (cur->son[c] == nullptr) {
                    cur->son[c] = new Node();
                }
                cur = cur->son[c];
                cur->pq.push(word);
                if (cur->pq.size() > 3) {
                    cur->pq.pop();
                }
            }
        }

        vector<vector<string>> ans;
        Node* cur = root;
        bool flag = false;
        for (char c : searchWord) {
            c -= 'a';
            if (flag || !cur->son[c]) {
                ans.emplace_back();
                flag = true;
            } else {
                cur = cur->son[c];
                vector<string> selected;
                while (!cur->pq.empty()) {
                    selected.push_back(cur->pq.top());
                    cur->pq.pop();
                }
                ranges::reverse(selected);
                ans.push_back(selected);
            }
        }
        return ans;
    }

    // 排序+二分
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        ranges::sort(products);
        int n = products.size();
        vector<vector<string>> ans;
        for (int i = 0; i < searchWord.size(); i++) {
            string cur = searchWord.substr(0, i + 1);
            int l = -1, r = n;
            while (l + 1 < r) {
                int mid = l + (r - l) / 2;
                (products[mid] >= cur ? r : l) = mid;
            }
            vector<string> selected;
            for (int j = r; j <= min(n - 1, r + 2); j++) {
                if (!products[j].starts_with(cur)) {
                    break;
                }
                selected.push_back(products[j]);
            }
            ans.push_back(selected);
        }
        return ans;
    }
};
// @lc code=end

