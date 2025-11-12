/*
 * @lc app=leetcode id=2262 lang=cpp
 *
 * [2262] Total Appeal of A String
 *
 * https://leetcode.com/problems/total-appeal-of-a-string/description/
 *
 * algorithms
 * Hard (55.88%)
 * Likes:    1207
 * Dislikes: 34
 * Total Accepted:    45.1K
 * Total Submissions: 80.3K
 * Testcase Example:  '"abbca"'
 *
 * The appeal of a string is the number of distinct characters found in the
 * string.
 * 
 * 
 * For example, the appeal of "abbca" is 3 because it has 3 distinct
 * characters: 'a', 'b', and 'c'.
 * 
 * 
 * Given a string s, return the total appeal of all of its substrings.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abbca"
 * Output: 28
 * Explanation: The following are the substrings of "abbca":
 * - Substrings of length 1: "a", "b", "b", "c", "a" have an appeal of 1, 1, 1,
 * 1, and 1 respectively. The sum is 5.
 * - Substrings of length 2: "ab", "bb", "bc", "ca" have an appeal of 2, 1, 2,
 * and 2 respectively. The sum is 7.
 * - Substrings of length 3: "abb", "bbc", "bca" have an appeal of 2, 2, and 3
 * respectively. The sum is 7.
 * - Substrings of length 4: "abbc", "bbca" have an appeal of 3 and 3
 * respectively. The sum is 6.
 * - Substrings of length 5: "abbca" has an appeal of 3. The sum is 3.
 * The total sum is 5 + 7 + 7 + 6 + 3 = 28.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "code"
 * Output: 20
 * Explanation: The following are the substrings of "code":
 * - Substrings of length 1: "c", "o", "d", "e" have an appeal of 1, 1, 1, and
 * 1 respectively. The sum is 4.
 * - Substrings of length 2: "co", "od", "de" have an appeal of 2, 2, and 2
 * respectively. The sum is 6.
 * - Substrings of length 3: "cod", "ode" have an appeal of 3 and 3
 * respectively. The sum is 6.
 * - Substrings of length 4: "code" has an appeal of 4. The sum is 4.
 * The total sum is 4 + 6 + 6 + 4 = 20.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 增量法
    long long appealSum1(string s) {
        vector<int> last(26, -1);
        long long ans = 0;
        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            int c = s[i] - 'a';
            sum += i - last[c];
            ans += sum;
            last[c] = i;
        }
        return ans;
    }

    // 贡献法
    long long appealSum(string s) {
        vector<int> last(26, -1);
        long long ans = 0;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            ans += 1LL * (i - last[c]) * (n - i);
            last[c] = i;
        }
        return ans;
    }
};
// @lc code=end

