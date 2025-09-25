/*
 * @lc app=leetcode id=3566 lang=cpp
 *
 * [3566] Partition Array into Two Equal Product Subsets
 *
 * https://leetcode.com/problems/partition-array-into-two-equal-product-subsets/description/
 *
 * algorithms
 * Medium (34.76%)
 * Likes:    71
 * Dislikes: 16
 * Total Accepted:    31.5K
 * Total Submissions: 90.3K
 * Testcase Example:  '[3,1,6,8,4]\n24'
 *
 * You are given an integer array nums containing distinct positive integers
 * and an integer target.
 * 
 * Determine if you can partition nums into two non-empty disjoint subsets,
 * with each element belonging to exactly one subset, such that the product of
 * the elements in each subset is equal to target.
 * 
 * Return true if such a partition exists and false otherwise.
 * A subset of an array is a selection of elements of the array.
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,1,6,8,4], target = 24
 * 
 * Output: true
 * 
 * Explanation: The subsets [3, 8] and [1, 6, 4] each have a product of 24.
 * Hence, the output is true.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,5,3,7], target = 15
 * 
 * Output: false
 * 
 * Explanation: There is no way to partition nums into two non-empty disjoint
 * subsets such that both subsets have a product of 15. Hence, the output is
 * false.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 12
 * 1 <= target <= 10^15
 * 1 <= nums[i] <= 100
 * All elements of nums are distinct.
 * 
 * 
 */
#include <vector>
#include <numeric>
#include <cmath>
#include <set>
using namespace std;
// @lc code=start
class Solution {
public:
    bool checkEqualPartitions1(vector<int>& nums, long long target) {
        int n = nums.size();

        auto dfs = [&](this auto &&dfs, int i, long long cur1, long long cur2) -> bool {
            if (cur1 > target || cur2 > target) {
                return false;
            }
            if (i == n) {
                return cur1 == target && cur2 == target;
            }

            return dfs(i + 1, cur1 * nums[i], cur2) || dfs(i + 1, cur1, cur2 * nums[i]);
        };

        return dfs(0, 1, 1);
    }

    // half + enum
    // 分成两个数组A、B，A选一些数到子集1，这些元素积为a1，同理得a2、b1、b2，
    // 有提议得：(a1 / a2) == (b1 / b2)，使用set维护等式左右，存在交集则结果为true
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        __int128_t prod_all = 1;
        for (int x : nums) {
            prod_all *= x;
        }

        if (prod_all != (__int128_t) target * target) {
            return false;
        }

        int m = nums.size() / 2;
        auto set1 = calc({nums.begin(), nums.begin() + m}, target);
        auto set2 = calc({nums.begin() + m, nums.end()}, target);

        for (auto &p : set1) {
            if (set2.contains(p)) {
                return true;
            }
        }
        
        return false;
    }

    set<pair<long long, long long>> calc(const vector<int> &nums, long long target) {
        set<pair<long long, long long>> set;
        auto dfs = [&](auto &dfs, int i, long long mult1, long long mult2) -> void {
            if (mult1 > target || mult2 > target) {
                return;
            }
            if (i == nums.size()) {
                long long g = gcd(mult1, mult2);
                set.emplace(mult1 / g, mult2 / g);
                return;
            }

            dfs(dfs, i + 1, mult1 * nums[i], mult2);
            dfs(dfs, i + 1, mult1, mult2 * nums[i]);
        };
        dfs(dfs, 0, 1, 1);
        return set;
    }
};
// @lc code=end

