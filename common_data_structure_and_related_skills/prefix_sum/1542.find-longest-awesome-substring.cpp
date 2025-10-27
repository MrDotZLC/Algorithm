/*
 * @lc app=leetcode id=1542 lang=cpp
 *
 * [1542] Find Longest Awesome Substring
 *
 * https://leetcode.com/problems/find-longest-awesome-substring/description/
 *
 * algorithms
 * Hard (45.44%)
 * Likes:    870
 * Dislikes: 15
 * Total Accepted:    18.7K
 * Total Submissions: 40.7K
 * Testcase Example:  '"3242415"'
 *
 * You are given a string s. An awesome substring is a non-empty substring of s
 * such that we can make any number of swaps in order to make it a palindrome.
 * 
 * Return the length of the maximum length awesome substring of s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "3242415"
 * Output: 5
 * Explanation: "24241" is the longest awesome substring, we can form the
 * palindrome "24142" with some swaps.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "12345678"
 * Output: 1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "213123"
 * Output: 6
 * Explanation: "213123" is the longest awesome substring, we can form the
 * palindrome "231132" with some swaps.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists only of digits.
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
    int longestAwesome(string s) {
        int ans = 1, n = s.length(), sum = 0;
        unordered_map<int, int> cnt;
        cnt[0] = -1;
        for (int i = 0; i < n; i++) {
            int bit = 1 << (s[i] - '0');
            sum ^= bit;

            for (int k = 0; k < 10; k++) {
                int sub = sum ^ (1 << k);
                if (cnt.count(sub)) {
                    ans = max(ans , i - cnt[sub]);
                }
            }

            if (cnt.count(sum)) {
                ans = max(ans , i - cnt[sum]);
            } else {
                cnt[sum] = i;
            }

        }
        return ans;
    }
};
// @lc code=end

