/*
 * @lc app=leetcode id=2266 lang=cpp
 *
 * [2266] Count Number of Texts
 *
 * https://leetcode.com/problems/count-number-of-texts/description/
 *
 * algorithms
 * Medium (49.01%)
 * Likes:    921
 * Dislikes: 36
 * Total Accepted:    27.4K
 * Total Submissions: 55.4K
 * Testcase Example:  '"22233"'
 *
 * Alice is texting Bob using her phone. The mapping of digits to letters is
 * shown in the figure below.
 * 
 * In order to add a letter, Alice has to press the key of the corresponding
 * digit i times, where i is the position of the letter in the key.
 * 
 * 
 * For example, to add the letter 's', Alice has to press '7' four times.
 * Similarly, to add the letter 'k', Alice has to press '5' twice.
 * Note that the digits '0' and '1' do not map to any letters, so Alice does
 * not use them.
 * 
 * 
 * However, due to an error in transmission, Bob did not receive Alice's text
 * message but received a string of pressed keys instead.
 * 
 * 
 * For example, when Alice sent the message "bob", Bob received the string
 * "2266622".
 * 
 * 
 * Given a string pressedKeys representing the string received by Bob, return
 * the total number of possible text messages Alice could have sent.
 * 
 * Since the answer may be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: pressedKeys = "22233"
 * Output: 8
 * Explanation:
 * The possible text messages Alice could have sent are:
 * "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae", and "ce".
 * Since there are 8 possible messages, we return 8.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: pressedKeys = "222222222222222222222222222222222222"
 * Output: 82876089
 * Explanation:
 * There are 2082876103 possible text messages Alice could have sent.
 * Since we need to return the answer modulo 10^9 + 7, we return 2082876103 %
 * (10^9 + 7) = 82876089.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= pressedKeys.length <= 10^5
 * pressedKeys only consists of digits from '2' - '9'.
 * 
 * 
 */
#include <vector>
#include <string>
#include <numeric>
using namespace std;
// @lc code=start
const int MOD = 1e9 + 7;
const int MX = 1e5;

long long f[MX + 1], g[MX + 1];

int init = []() {
    f[0] = g[0] = 1;
    f[1] = g[1] = 1;
    f[2] = g[2] = 2;
    f[3] = g[3] = 4;
    for (int i = 4; i <= MX; i++) {
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % MOD;
        g[i] = (g[i - 1] + g[i - 2] + g[i - 3] + g[i - 4]) % MOD;
    }
    return 0;
}();

class Solution {
public:
    int countTexts1(string pressedKeys) {
        char cur = pressedKeys[0];
        int ans = 1, n = 0;
        for (int i = 0; i < pressedKeys.length(); i++) {
            char c = pressedKeys[i];
            n++;
            if (c != cur || i == pressedKeys.length() - 1) {
                n -= c != cur;
                ans = (1LL * ans *
                       dp(n, cur == '7' || cur == '9' ? 4 : 3)) %
                      MOD;
                cur = c;
                n = 1;
            }
        }
        return ans;
    }

    int dp(int n, int k) {
        vector<int> f(n + 1), nums(k);
        f[0] = 1;
        ranges::iota(nums, 1);
        for (int i = 1; i <= n; i++) {
            for (int x : nums) {
                if (x <= i) {
                    f[i] = (long long)(f[i] + f[i - x]) % MOD;
                }
            }
        }
        return f[n];
    }

    int countTexts(string pressedKeys) {
        char cur = pressedKeys[0];
        int ans = 1, n = 0;
        for (int i = 0; i < pressedKeys.length(); i++) {
            char c = pressedKeys[i];
            n++;
            if (c != cur || i == pressedKeys.length() - 1) {
                n -= c != cur;
                ans = (ans *
                       ((cur == '7' || cur == '9') ? g[n] : f[n])) %
                      MOD;
                cur = c;
                n = 1;
            }
        }
        return ans;
    }
};
// @lc code=end

