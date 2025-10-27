/*
 * @lc app=leetcode id=3186 lang=cpp
 *
 * [3186] Maximum Total Damage With Spell Casting
 *
 * https://leetcode.com/problems/maximum-total-damage-with-spell-casting/description/
 *
 * algorithms
 * Medium (27.90%)
 * Likes:    716
 * Dislikes: 64
 * Total Accepted:    108.8K
 * Total Submissions: 241.8K
 * Testcase Example:  '[1,1,3,4]'
 *
 * A magician has various spells.
 * 
 * You are given an array power, where each element represents the damage of a
 * spell. Multiple spells can have the same damage value.
 * 
 * It is a known fact that if a magician decides to cast a spell with a damage
 * of power[i], they cannot cast any spell with a damage of power[i] - 2,
 * power[i] - 1, power[i] + 1, or power[i] + 2.
 * 
 * Each spell can be cast only once.
 * 
 * Return the maximum possible total damage that a magician can cast.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: power = [1,1,3,4]
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with
 * damage 1, 1, 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: power = [7,1,6,6]
 * 
 * Output: 13
 * 
 * Explanation:
 * 
 * The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with
 * damage 1, 6, 6.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= power.length <= 10^5
 * 1 <= power[i] <= 10^9
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
    long long maximumTotalDamage1(vector<int>& power) {
        unordered_map<int, int> cnt;
        for (int x : power) {
            cnt[x]++;
        }
        vector<pair<int, int>> a(cnt.begin(), cnt.end());
        ranges::sort(a);

        int n = a.size();
        vector<long long> memo(n, -1);
        auto dfs = [&](this auto &&dfs, int i) -> long long {
            if (i < 0) {
                return 0;
            }
            long long &ans = memo[i]; // 使用引用更新memo
            if (ans != -1) {
                return ans;
            }
            auto &[x, c] = a[i];
            int j = i;
            while (j && a[j - 1].first >= x - 2) {
                j--;
            }
            return ans = max(dfs(i - 1), dfs(j - 1) + (long long) x * c);
        };

        return dfs(n - 1);
    }

    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, int> cnt;
        for (int x : power) {
            cnt[x]++;
        }
        vector<pair<int, int>> a(cnt.begin(), cnt.end());
        ranges::sort(a);

        int n = a.size();
        vector<long long> f(n + 1);
        for (int i = 0, j = 0; i < n; i++) {
            auto &[x, c] = a[i];
            while (a[j].first < x - 2) {
                j++;
            }
            f[i + 1] = max(f[i], f[j] + (long long) x * c);
        }
        return f[n];
    }
};
// @lc code=end

