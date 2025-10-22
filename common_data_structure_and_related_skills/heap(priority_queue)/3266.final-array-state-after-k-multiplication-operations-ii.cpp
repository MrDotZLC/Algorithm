/*
 * @lc app=leetcode id=3266 lang=cpp
 *
 * [3266] Final Array State After K Multiplication Operations II
 *
 * https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/description/
 *
 * algorithms
 * Hard (11.90%)
 * Likes:    173
 * Dislikes: 23
 * Total Accepted:    10K
 * Total Submissions: 83.3K
 * Testcase Example:  '[2,1,3,5,6]\n5\n2'
 *
 * You are given an integer array nums, an integer k, and an integer
 * multiplier.
 * 
 * You need to perform k operations on nums. In each operation:
 * 
 * 
 * Find the minimum value x in nums. If there are multiple occurrences of the
 * minimum value, select the one that appears first.
 * Replace the selected minimum value x with x * multiplier.
 * 
 * 
 * After the k operations, apply modulo 10^9 + 7 to every value in nums.
 * 
 * Return an integer array denoting the final state of nums after performing
 * all k operations and then applying the modulo.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
 * 
 * Output: [8,4,6,5,6]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Operation
 * Result
 * 
 * 
 * After operation 1
 * [2, 2, 3, 5, 6]
 * 
 * 
 * After operation 2
 * [4, 2, 3, 5, 6]
 * 
 * 
 * After operation 3
 * [4, 4, 3, 5, 6]
 * 
 * 
 * After operation 4
 * [4, 4, 6, 5, 6]
 * 
 * 
 * After operation 5
 * [8, 4, 6, 5, 6]
 * 
 * 
 * After applying modulo
 * [8, 4, 6, 5, 6]
 * 
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [100000,2000], k = 2, multiplier = 1000000
 * 
 * Output: [999999307,999999993]
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Operation
 * Result
 * 
 * 
 * After operation 1
 * [100000, 2000000000]
 * 
 * 
 * After operation 2
 * [100000000000, 2000000000]
 * 
 * 
 * After applying modulo
 * [999999307, 999999993]
 * 
 * 
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^4
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= 10^9
 * 1 <= multiplier <= 10^6
 * 
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int MOD = 1'000'000'007;
    vector<int> getFinalState1(vector<int>& nums, int k, int multiplier) {
        if (multiplier == 1) {
            return move(nums);
        }
        
        int n = nums.size(), mx = ranges::max(nums);

        vector<pair<long long, int>> h(n);
        for (int i = 0; i < nums.size(); i++) {
            h[i] = {nums[i], i};
        }
        ranges::make_heap(h, greater<>());

        for (; k && h[0].first < mx; k--) {
            ranges::pop_heap(h, greater<>());
            h.back().first *= multiplier;
            ranges::push_heap(h, greater<>());
        }

        ranges::sort(h);
        for (int i = 0; i < n; i++) {
            auto &[x, j] = h[i];
            nums[j] =
                x % MOD * qpow(multiplier, k / n + (i < k % n)) % MOD;
        }

        return move(nums);
    }

    long long qpow(long long a, long long n, long long MOD = 1'000'000'007) {
        long long res = 1 % MOD;
        a %= MOD;
        while (n > 0) {
            if (n & 1) {
                res = res * a % MOD;
            }
            a = a * a % MOD;
            n >>= 1;
        }
        return res;
    }
};
// @lc code=end

