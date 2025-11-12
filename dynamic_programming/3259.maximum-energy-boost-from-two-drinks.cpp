/*
 * @lc app=leetcode id=3259 lang=cpp
 *
 * [3259] Maximum Energy Boost From Two Drinks
 *
 * https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/description/
 *
 * algorithms
 * Medium (49.47%)
 * Likes:    172
 * Dislikes: 13
 * Total Accepted:    34.5K
 * Total Submissions: 69.4K
 * Testcase Example:  '[1,3,1]\n[3,1,1]'
 *
 * You are given two integer arrays energyDrinkA and energyDrinkB of the same
 * length n by a futuristic sports scientist. These arrays represent the energy
 * boosts per hour provided by two different energy drinks, A and B,
 * respectively.
 * 
 * You want to maximize your total energy boost by drinking one energy drink
 * per hour. However, if you want to switch from consuming one energy drink to
 * the other, you need to wait for one hour to cleanse your system (meaning you
 * won't get any energy boost in that hour).
 * 
 * Return the maximum total energy boost you can gain in the next n hours.
 * 
 * Note that you can start consuming either of the two energy drinks.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * To gain an energy boost of 5, drink only the energy drink A (or only B).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: energyDrinkA = [4,1,1], energyDrinkB = [1,1,3]
 * 
 * Output: 7
 * 
 * Explanation:
 * 
 * To gain an energy boost of 7:
 * 
 * 
 * Drink the energy drink A for the first hour.
 * Switch to the energy drink B and we lose the energy boost of the second
 * hour.
 * Gain the energy boost of the drink B in the third hour.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == energyDrinkA.length == energyDrinkB.length
 * 3 <= n <= 10^5
 * 1 <= energyDrinkA[i], energyDrinkB[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 记忆化递归
    long long maxEnergyBoost1(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        vector<array<long long, 2>> memo(n, {-1, -1});
        auto dfs = [&](this auto &&dfs, int i, bool drink) -> long long {
            if (i < 0) {
                return 0;
            }
            long long &res = memo[i][drink];
            if (res != -1) {
                return res;
            }
            int energy = drink ? energyDrinkA[i] : energyDrinkB[i];
            return res = max(dfs(i - 1, drink), dfs(i - 2, !drink)) + energy;
        };
        return max(dfs(n - 1, true), dfs(n - 1, false));
    }

    // DP+空间优化
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        long long prev0 = 0LL, prev1 = 0LL;
        vector<array<long long, 2>> f(2);
        f[0][0] = energyDrinkA[0];
        f[0][1] = energyDrinkB[0];
        for (int i = 1; i < n; i++) {
            prev0 = f[(i - 1) % 2][0];
            prev1 = f[(i - 1) % 2][1];
            f[i % 2][0] = max(prev0 + energyDrinkA[i], prev1);
            f[i % 2][1] = max(prev1 + energyDrinkB[i], prev0);
        }
        return ranges::max(f[(n - 1) % 2]);
    }
};
// @lc code=end

