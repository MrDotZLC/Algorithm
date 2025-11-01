/*
 * @lc app=leetcode id=2902 lang=cpp
 *
 * [2902] Count of Sub-Multisets With Bounded Sum
 *
 * https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/description/
 *
 * algorithms
 * Hard (20.75%)
 * Likes:    159
 * Dislikes: 26
 * Total Accepted:    5.5K
 * Total Submissions: 26K
 * Testcase Example:  '[1,2,2,3]\n6\n6'
 *
 * You are given a 0-indexed array nums of non-negative integers, and two
 * integers l and r.
 * 
 * Return the count of sub-multisets within nums where the sum of elements in
 * each subset falls within the inclusive range of [l, r].
 * 
 * Since the answer may be large, return it modulo 10^9 + 7.
 * 
 * A sub-multiset is an unordered collection of elements of the array in which
 * a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the
 * number of occurrences of x in the array.
 * 
 * Note that:
 * 
 * 
 * Two sub-multisets are the same if sorting both sub-multisets results in
 * identical multisets.
 * The sum of an empty multiset is 0.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,2,3], l = 6, r = 6
 * Output: 1
 * Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,1,4,2,7], l = 1, r = 5
 * Output: 7
 * Explanation: The subsets of nums that have a sum within the range [1, 5] are
 * {1}, {2}, {4}, {2, 2}, {1, 2}, {1, 4}, and {1, 2, 2}.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,1,3,5,2], l = 3, r = 5
 * Output: 9
 * Explanation: The subsets of nums that have a sum within the range [3, 5] are
 * {3}, {5}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {1, 1, 2}, {1, 1, 3}, and {1, 2,
 * 2}.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * 0 <= nums[i] <= 2 * 10^4
 * Sum of nums does not exceed 2 * 10^4.
 * 0 <= l <= r <= 2 * 10^4
 * 
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        const int MOD = 1e9+7;
        int total = 0;
        unordered_map<int, int> cnt;
        for (int x : nums) {
            cnt[x]++;
            total += x;
        }
        if (l > total) {
            return 0;
        }
        r = min(r, total);
        vector<int> f(r + 1);
        f[0] = cnt[0] + 1;
        cnt.erase(0);

        int sum = 0;
        for (auto [x, c] : cnt) {
            auto f1 = f;
            sum = min(sum + x * c, r); // 
            for (int j = x; j <= sum; j++) {
                f1[j] = (f1[j] + f1[j - x]) % MOD;
                if (j >= (c + 1) * x) {
                    f1[j] = (f1[j] - f[j - (c + 1) * x] + MOD) % MOD;
                }
            }
            f = move(f1);
        }
        
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans = (ans + f[i]) % MOD;
        }
        return ans;
    }
};
// @lc code=end

