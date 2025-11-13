/*
 * @lc app=leetcode id=403 lang=cpp
 *
 * [403] Frog Jump
 *
 * https://leetcode.com/problems/frog-jump/description/
 *
 * algorithms
 * Hard (46.63%)
 * Likes:    5916
 * Dislikes: 274
 * Total Accepted:    321.4K
 * Total Submissions: 685.3K
 * Testcase Example:  '[0,1,3,5,6,8,12,17]'
 *
 * A frog is crossing a river. The river is divided into some number of units,
 * and at each unit, there may or may not exist a stone. The frog can jump on a
 * stone, but it must not jump into the water.
 * 
 * Given a list of stones positions (in units) in sorted ascending order,
 * determine if the frog can cross the river by landing on the last stone.
 * Initially, the frog is on the first stone and assumes the first jump must be
 * 1 unit.
 * 
 * If the frog's last jump was k units, its next jump must be either k - 1, k,
 * or k + 1 units. The frog can only jump in the forward direction.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: stones = [0,1,3,5,6,8,12,17]
 * Output: true
 * Explanation: The frog can jump to the last stone by jumping 1 unit to the
 * 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone,
 * then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the
 * 8th stone.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: stones = [0,1,2,3,4,8,9,11]
 * Output: false
 * Explanation: There is no way to jump to the last stone as the gap between
 * the 5th and 6th stone is too large.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= stones.length <= 2000
 * 0 <= stones[i] <= 2^31 - 1
 * stones[0] == 0
 * stones is sorted in a strictly increasing order.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化递归
    bool canCross1(vector<int>& stones) {
        int n = stones.size();
        unordered_map<int, int> ss;
        for (int i = 0; i < n; i++) {
            ss[stones[i]] = i;
        }

        if (!ss.contains(1)) {
            return false;
        }

        vector memo(n, vector<int>(n, -1));
        auto dfs = [&](auto &dfs, int i, int step) -> bool {
            if (i == n - 1) {
                return 1;
            }
            int &res = memo[i][step];
            if (res != -1) {
                return res;
            }
            res = 0;
            for (int j = -1; j <= 1; j++) {
                int new_step = step + j;
                if (new_step == 0) {
                    continue;
                }
                int next = stones[i] + new_step;
                if (ss.contains(next)) {
                    res |= dfs(dfs, ss[next], new_step);
                    if (res) {
                        return true;
                    }
                }
            }
            return res;
        };
        return dfs(dfs, 1, 1);
    }

    // DP
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        if (stones[1] != 1) {
            return false;
        }
        vector f(n + 1, vector<int>(n + 1));
        f[1][1] = 1;
        for (int i = 2; i < n; i++) {
            for (int j = 1; j < i; j++) {
                int k = stones[i] - stones[j];
                if (k <= j + 1) {
                    f[i][k] = f[j][k - 1] || f[j][k] || f[j][k + 1];
                }
            }
        }
        for (int i = 1; i < n; i++) {
            if (f[n - 1][i]) {
                return true;
            }
        }
        return false;
    }
};
// @lc code=end

