/*
 * @lc app=leetcode id=3180 lang=cpp
 *
 * [3180] Maximum Total Reward Using Operations I
 *
 * https://leetcode.com/problems/maximum-total-reward-using-operations-i/description/
 *
 * algorithms
 * Medium (30.07%)
 * Likes:    205
 * Dislikes: 17
 * Total Accepted:    29.6K
 * Total Submissions: 97.6K
 * Testcase Example:  '[1,1,3,3]'
 *
 * You are given an integer array rewardValues of length n,
 * representing the values of rewards.
 *
 * Initially, your total reward x is 0, and all indices are unmarked.
 * You are allowed to perform the following operation any number of
 * times:
 *
 *
 * Choose an unmarked index i from the range [0, n - 1].
 * If rewardValues[i] is greater than your current total reward x,
 * then add rewardValues[i] to x (i.e., x = x + rewardValues[i]), and
 * mark the index i.
 *
 *
 * Return an integer denoting the maximum total reward you can collect
 * by performing the operations optimally.
 *
 *
 * Example 1:
 *
 *
 * Input: rewardValues = [1,1,3,3]
 *
 * Output: 4
 *
 * Explanation:
 *
 * During the operations, we can choose to mark the indices 0 and 2 in
 * order, and the total reward will be 4, which is the maximum.
 *
 *
 * Example 2:
 *
 *
 * Input: rewardValues = [1,6,4,3,2]
 *
 * Output: 11
 *
 * Explanation:
 *
 * Mark the indices 0, 2, and 1 in order. The total reward will then
 * be 11, which is the maximum.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= rewardValues.length <= 2000
 * 1 <= rewardValues[i] <= 2000
 *
 *
 */
#include <vector>
#include <unordered_map>
#include <bitset>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP递归
    int maxTotalReward1(vector<int> &rewardValues) {
        ranges::sort(rewardValues);
        rewardValues.erase(ranges::unique(rewardValues).begin(), rewardValues.end());
        
        int n = rewardValues.size(),
            m = rewardValues.back() * 2 - 1;
        vector<vector<int>> memo(n, vector<int>(m + 1, -1));
        auto dfs = [&](auto &dfs, int i, int t) -> int {
            if (i == n) {
                return t;
            }
            int &ans = memo[i][t];
            if (ans != -1) {
                return ans;
            }
            // 不选
            ans = dfs(dfs, i + 1, t);
            // 选
            int v = rewardValues[i];
            if (v > t && v + t <= m) {
                ans = max(ans, dfs(dfs, i + 1, t + v));
            }
            return ans;
        };
        return dfs(dfs, 0, 0);
    }

    // DP递推
    int maxTotalReward2(vector<int> &rewardValues) {
        ranges::sort(rewardValues);
        rewardValues.erase(ranges::unique(rewardValues).begin(), rewardValues.end());
        
        int n = rewardValues.size(),
            m = rewardValues.back() * 2 - 1;
        vector<vector<int>> f(n + 1, vector<int>(m + 1));
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            int v = rewardValues[i - 1];
            for (int j = m; j >= 0; j--) {
                f[i][j] |= f[i - 1][j];
                if (v <= j && v > j - v) {
                    f[i][j] |= f[i - 1][j - v];
                }
            }
        }
        for (int j = m; ; j--) {
            if (f[n][j]) {
                return j;
            }
        }
    }

    // DP递推+空间优化+剪枝
    int maxTotalReward3(vector<int> &rewardValues) {
        int mx = ranges::max(rewardValues);
        // 剪枝1：数组包含m - 1，因为m之前的元素和至多为m - 1，所以直接返回答案2 * m - 1
        // 剪枝2：元素和至多为m - 1，直接返回答案2 * m - 1
        unordered_map<int, int> cnt;
        int sum = 0;
        for (int x : rewardValues) {
            if (cnt.contains(x)) {
                continue;
            }
            if (x == mx - 1 || cnt.contains(mx - 1 - x)) {
                return 2 * mx - 1;
            }
        }

        
        ranges::sort(rewardValues);
         // 剪枝3： 所选的值总是递增的，重复的值一定不会选
        rewardValues.erase(ranges::unique(rewardValues).begin(), rewardValues.end());
        
        int n = rewardValues.size(),
            m = mx * 2 - 1; // 剪枝4：最大值mx，已选和至多mx-1，即最大元素和至多为mx-1
        vector<int> f(m + 1, 0); // 元素和j是否为最大值
        f[0] = 1;
        for (int i = 0; i < n; i++) {
            int v = rewardValues[i];
            for (int j = m; j >= v; j--) {
                if (v > j - v) {
                    f[j] |= f[j - v];
                }
            }
        }
        for (int j = m; ; j--) {
            if (f[j]) {
                return j;
            }
        }
    }

    // DP递推+空间优化+剪枝+bit压缩
    int maxTotalReward(vector<int> &rewardValues) {
        int mx = ranges::max(rewardValues);
        // 剪枝1：数组包含m - 1，因为m之前的元素和至多为m - 1，所以直接返回答案2 * m - 1
        // 剪枝2：元素和至多为m - 1，直接返回答案2 * m - 1
        unordered_map<int, int> cnt;
        int sum = 0;
        for (int x : rewardValues) {
            if (cnt.contains(x)) {
                continue;
            }
            if (x == mx - 1 || cnt.contains(mx - 1 - x)) {
                return 2 * mx - 1;
            }
        }

        
        ranges::sort(rewardValues);
         // 剪枝3： 所选的值总是递增的，重复的值一定不会选
        rewardValues.erase(ranges::unique(rewardValues).begin(), rewardValues.end());
        
        bitset<100000> f{1}; 
        for (int v : rewardValues) {
            // 将f[0:v]左移size-v位，去掉高size-v位
            // 再右移size-v-v位，使得f[0:v]移到f[v:v+v]
            // 最后与f,实现f[0:v]与f[v:v+v]
            int shift = f.size() - v;
            // 左移 shift 再右移 shift，把所有 >= v 的比特位置 0
            // f |= f << shift >> shift << v;
            f |= f << shift >> (shift - v); // 简化上式
        }
        for (int j = mx * 2 - 1; ; j--) {
            if (f[j]) {
                return j;
            }
        }
    }
};
// @lc code=end
