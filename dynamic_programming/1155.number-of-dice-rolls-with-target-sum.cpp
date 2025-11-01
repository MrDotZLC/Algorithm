/*
 * @lc app=leetcode id=1155 lang=cpp
 *
 * [1155] Number of Dice Rolls With Target Sum
 *
 * https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/
 *
 * algorithms
 * Medium (61.72%)
 * Likes:    5277
 * Dislikes: 184
 * Total Accepted:    339.4K
 * Total Submissions: 547.9K
 * Testcase Example:  '1\n6\n3'
 *
 * You have n dice, and each dice has k faces numbered from 1 to k.
 * 
 * Given three integers n, k, and target, return the number of possible ways
 * (out of the k^n total ways) to roll the dice, so the sum of the face-up
 * numbers equals target. Since the answer may be too large, return it modulo
 * 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1, k = 6, target = 3
 * Output: 1
 * Explanation: You throw one die with 6 faces.
 * There is only one way to get a sum of 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, k = 6, target = 7
 * Output: 6
 * Explanation: You throw two dice, each with 6 faces.
 * There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 30, k = 30, target = 500
 * Output: 222616187
 * Explanation: The answer must be returned modulo 10^9 + 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n, k <= 30
 * 1 <= target <= 1000
 * 
 * 
 */
#include <vector>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    const int MOD = 1e9+7;
    // DP递归
    int numRollsToTarget1(int n, int k, int target) {
        if (target < n || target > n * k) {
            return 0;
        }
        
        vector<vector<int>> memo(n + 1, vector<int>(target + 1, -1));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i == 0) {
                return j == 0;
            }
            int &ans = memo[i][j];
            if (ans != -1) {
                return ans;
            }
            ans = 0;
            for (int x = 1; x <= k && x <= j; x++) {
                ans = (ans + dfs(i - 1, j - x)) % MOD;
            }
            return ans;
        };
        return dfs(n, target);
    }

    // DP递推
    int numRollsToTarget(int n, int k, int target) {
        if (target < n || target > n * k) {
            return 0;
        }
        
        vector<vector<int>> f(n + 1, vector<int>(target + 1, 0));
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                for (int x = 1; x <= k && x <= j; x++) {
                    f[i][j] = (f[i][j] + f[i - 1][j - x]) % MOD;
                }
            }
        }
        return f[n][target];
    }

};
// @lc code=end

