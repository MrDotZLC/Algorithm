/*
 * @lc app=leetcode id=1593 lang=cpp
 *
 * [1593] Split a String Into the Max Number of Unique Substrings
 *
 * https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/description/
 *
 * algorithms
 * Medium (68.41%)
 * Likes:    1498
 * Dislikes: 73
 * Total Accepted:    145.4K
 * Total Submissions: 212.5K
 * Testcase Example:  '"ababccc"'
 *
 * Given a string s, return the maximum number of unique substrings that the
 * given string can be split into.
 * 
 * You can split string s into any list of non-empty substrings, where the
 * concatenation of the substrings forms the original string. However, you must
 * split the substrings such that all of them are unique.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ababccc"
 * Output: 5
 * Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc'].
 * Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a'
 * and 'b' multiple times.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aba"
 * Output: 2
 * Explanation: One way to split maximally is ['a', 'ba'].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "aa"
 * Output: 1
 * Explanation: It is impossible to split the string any further.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 
 * 1 <= s.length <= 16
 * 
 * 
 * s contains only lower case English letters.
 * 
 * 
 * 
 */
#include <string>
#include <unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxUniqueSplit(string s) {
        int ans = 0, n = s.size();
        unordered_set<string> set;
        auto dfs = [&](auto &dfs, int start) -> void {
            if (start == n) {
                ans = max(ans, (int)set.size());
                return;
            }

            if (n - start + (int)set.size() <= ans) {
                return;
            }

            string cur_s = "";
            for (int j = start; j < n; j++) {
                cur_s = s.substr(start, j - start + 1);
                if (set.count(cur_s) > 0) {
                    continue;
                }
                set.insert(cur_s);
                dfs(dfs, j + 1);
                set.erase(cur_s);
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

