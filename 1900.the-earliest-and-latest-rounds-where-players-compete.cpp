/*
 * @lc app=leetcode id=1900 lang=cpp
 *
 * [1900] The Earliest and Latest Rounds Where Players Compete
 */

// @lc code=start

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        vector memo(n + 1, vector(n + 1, vector<pair<int, int>>(n + 1)));

        // 1. dfs 
        auto dfs = [&](auto&& dfs, int n, int firstPlayer, int secondPlayer) -> pair<int, int> {
        
            // A and B meet.
            if (firstPlayer + secondPlayer == n + 1) {
                return {1, 1};
            }

            // Ensure that the number of players on the left of A 
            // is less than the number of players on the right of B, 
            // by exchanging the relative positions of A and B.
            if (firstPlayer + secondPlayer > n + 1) {
                // tie(firstPlayer, secondPlayer) = pair(n + 1 - secondPlayer, n + 1 - firstPlayer); 
                int tmp = firstPlayer;
                firstPlayer = n + 1 - secondPlayer;
                secondPlayer = n + 1 - tmp;
            }

            // Memory-based filtering
            auto& res = memo[n][firstPlayer][secondPlayer];
            if (res.first) {
                return res;
            }

            // Calculate the number of players for the next round.
            int m = (n + 1) / 2; 

            // Calculate the maximum and minimum number of players retained between A and B.
            int min_mid = secondPlayer > m ? secondPlayer - n / 2 - 1 : 0;
            int max_mid = secondPlayer > m ? m - firstPlayer - 1 : secondPlayer - firstPlayer - 1;
            int earliest = INT_MAX;
            int latest = 0;

            // Iterate through all scenarios, based on the scope of reservation.
            for (int left = 0; left < firstPlayer; left++){
                for (int mid = min_mid; mid <= max_mid; mid++) {
                    auto [e, l] = dfs(dfs, m, left + 1, left + 1 + mid + 1);
                    earliest = min(earliest, e);
                    latest = max(latest, l);
                }
            }

            // res = count + 1
            memo[n][firstPlayer][secondPlayer] = {earliest + 1, latest + 1};
            return {earliest + 1, latest + 1};
        };

        // 2. return
        auto [earliest, latest] = dfs(dfs, n, firstPlayer, secondPlayer);
        return {earliest, latest};
    }
};
// @lc code=end

