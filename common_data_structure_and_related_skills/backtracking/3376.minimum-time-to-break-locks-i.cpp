/*
 * @lc app=leetcode id=3376 lang=cpp
 *
 * [3376] Minimum Time to Break Locks I
 *
 * https://leetcode.com/problems/minimum-time-to-break-locks-i/description/
 *
 * algorithms
 * Medium (30.62%)
 * Likes:    99
 * Dislikes: 22
 * Total Accepted:    12.8K
 * Total Submissions: 41.2K
 * Testcase Example:  '[3,4,1]\n1'
 *
 * Bob is stuck in a dungeon and must break n locks, each requiring some amount
 * of energy to break. The required energy for each lock is stored in an array
 * called strength where strength[i] indicates the energy needed to break the
 * i^th lock.
 * 
 * To break a lock, Bob uses a sword with the following characteristics:
 * 
 * 
 * The initial energy of the sword is 0.
 * The initial factor x by which the energy of the sword increases is 1.
 * Every minute, the energy of the sword increases by the current factor x.
 * To break the i^th lock, the energy of the sword must reach at least
 * strength[i].
 * After breaking a lock, the energy of the sword resets to 0, and the factor x
 * increases by a given value k.
 * 
 * 
 * Your task is to determine the minimum time in minutes required for Bob to
 * break all n locks and escape the dungeon.
 * 
 * Return the minimum time required for Bob to break all n locks.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: strength = [3,4,1], k = 1
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Time
 * Energy
 * x
 * Action
 * Updated x
 * 
 * 
 * 0
 * 0
 * 1
 * Nothing
 * 1
 * 
 * 
 * 1
 * 1
 * 1
 * Break 3^rd Lock
 * 2
 * 
 * 
 * 2
 * 2
 * 2
 * Nothing
 * 2
 * 
 * 
 * 3
 * 4
 * 2
 * Break 2^nd Lock
 * 3
 * 
 * 
 * 4
 * 3
 * 3
 * Break 1^st Lock
 * 3
 * 
 * 
 * 
 * 
 * The locks cannot be broken in less than 4 minutes; thus, the answer is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: strength = [2,5,4], k = 2
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Time
 * Energy
 * x
 * Action
 * Updated x
 * 
 * 
 * 0
 * 0
 * 1
 * Nothing
 * 1
 * 
 * 
 * 1
 * 1
 * 1
 * Nothing
 * 1
 * 
 * 
 * 2
 * 2
 * 1
 * Break 1^st Lock
 * 3
 * 
 * 
 * 3
 * 3
 * 3
 * Nothing
 * 3
 * 
 * 
 * 4
 * 6
 * 3
 * Break 2^n^d Lock
 * 5
 * 
 * 
 * 5
 * 5
 * 5
 * Break 3^r^d Lock
 * 7
 * 
 * 
 * 
 * 
 * The locks cannot be broken in less than 5 minutes; thus, the answer is
 * 5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == strength.length
 * 1 <= n <= 8
 * 1 <= K <= 10
 * 1 <= strength[i] <= 10^6
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int findMinimumTime(vector<int>& strength, int k) {
        int n = strength.size();
        int ans = INT_MAX;
        vector<int> done(n);
        auto dfs = [&](auto &dfs, int i, int time) -> void {
            if (time >= ans) {
                return;
            }
            if (i == n) {
                ans = time;
                return;
            }

            int x = 1 + k * i;
            for (int j = 0; j < n; j++) {
                if (!done[j]) {
                    done[j] = 1;
                    dfs(dfs, i + 1, time + (strength[j] - 1) / x + 1);
                    done[j] = 0;
                }
            }
        };
        dfs(dfs, 0, 0);
        return ans;
    }
};
// @lc code=end

