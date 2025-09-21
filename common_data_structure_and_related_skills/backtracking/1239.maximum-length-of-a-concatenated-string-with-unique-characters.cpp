/*
 * @lc app=leetcode id=1239 lang=cpp
 *
 * [1239] Maximum Length of a Concatenated String with Unique Characters
 *
 * https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/description/
 *
 * algorithms
 * Medium (54.30%)
 * Likes:    4525
 * Dislikes: 338
 * Total Accepted:    310.6K
 * Total Submissions: 571.3K
 * Testcase Example:  '["un","iq","ue"]'
 *
 * You are given an array of strings arr. A string s is formed by the
 * concatenation of a subsequence of arr that has unique characters.
 * 
 * Return the maximum possible length of s.
 * 
 * A subsequence is an array that can be derived from another array by deleting
 * some or no elements without changing the order of the remaining elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = ["un","iq","ue"]
 * Output: 4
 * Explanation: All the valid concatenations are:
 * - ""
 * - "un"
 * - "iq"
 * - "ue"
 * - "uniq" ("un" + "iq")
 * - "ique" ("iq" + "ue")
 * Maximum length is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = ["cha","r","act","ers"]
 * Output: 6
 * Explanation: Possible longest valid concatenations are "chaers" ("cha" +
 * "ers") and "acters" ("act" + "ers").
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
 * Output: 26
 * Explanation: The only string in arr has all 26 characters.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 16
 * 1 <= arr[i].length <= 26
 * arr[i] contains only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxLength(vector<string>& arr) {
        int n = arr.size();

        int ans = 0;
        unordered_map<int, int> cnt;
        auto dfs = [&](this auto &&dfs, int i) -> void {
            if (i == n) {
                ans = max(ans, (int)cnt.size());
                return;
            }

            dfs(i + 1);
            bool can_choose = true;
            for (char c : arr[i]) {
                if (++cnt[c - 'a'] > 1) {
                    can_choose = false;
                }
            }
            if (can_choose) {
                dfs(i + 1);
            }
            for (char c : arr[i]) {
                if (--cnt[c - 'a'] == 0) {
                    cnt.erase(c - 'a');
                }
            }
        };
        dfs(0);
        return ans;
    }
};
// @lc code=end

