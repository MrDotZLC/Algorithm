/*
 * @lc app=leetcode id=2707 lang=cpp
 *
 * [2707] Extra Characters in a String
 *
 * https://leetcode.com/problems/extra-characters-in-a-string/description/
 *
 * algorithms
 * Medium (57.09%)
 * Likes:    2608
 * Dislikes: 137
 * Total Accepted:    193.8K
 * Total Submissions: 339K
 * Testcase Example:  '"leetscode"\n["leet","code","leetcode"]'
 *
 * You are given a 0-indexed string s and a dictionary of words dictionary. You
 * have to break s into one or more non-overlapping substrings such that each
 * substring is present in dictionary. There may be some extra characters in s
 * which are not present in any of the substrings.
 * 
 * Return the minimum number of extra characters left over if you break up s
 * optimally.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
 * Output: 1
 * Explanation: We can break s in two substrings: "leet" from index 0 to 3 and
 * "code" from index 5 to 8. There is only 1 unused character (at index 4), so
 * we return 1.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "sayhelloworld", dictionary = ["hello","world"]
 * Output: 3
 * Explanation: We can break s in two substrings: "hello" from index 3 to 7 and
 * "world" from index 8 to 12. The characters at indices 0, 1, 2 are not used
 * in any substring and thus are considered as extra characters. Hence, we
 * return 3.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 50
 * 1 <= dictionary.length <= 50
 * 1 <= dictionary[i].length <= 50
 * dictionary[i] and s consists of only lowercase English letters
 * dictionary contains distinct words
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <string>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    // 递归+记忆化搜索
    int minExtraChar1(string s, vector<string>& dictionary) {
        int n = s.length();
        unordered_set<string> dic(dictionary.begin(), dictionary.end());
        vector<int> memo(n, -1);
        function<int(int)> dfs = [&](int i) -> int {
            if (i < 0) {
                return 0;
            }
            int &res = memo[i];
            if (res != -1) {
                return res;
            }
            res = dfs(i - 1) + 1;
            for (int j = 0; j <= i; j++) {
                if (dic.contains(s.substr(j, i - j + 1))) {
                    res = min(res, dfs(j - 1));
                }
            }
            return res;
        };
        return dfs(n - 1);
    }

    // DP递推
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.length();
        unordered_set<string> dic(dictionary.begin(), dictionary.end());
        vector<int> f(n + 1);
        for (int i = 0; i < n; i++) {
            f[i + 1] = f[i] + 1;
            for (int j = 0; j <= i; j++) {
                if (dic.contains(s.substr(j, i - j + 1))) {
                    f[i + 1] = min(f[i + 1], f[j]);
                }
            }
        }
        return f[n];
    }
};
// @lc code=end

