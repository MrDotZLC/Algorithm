/*
 * @lc app=leetcode id=1863 lang=cpp
 *
 * [1863] Sum of All Subset XOR Totals
 *
 * https://leetcode.com/problems/sum-of-all-subset-xor-totals/description/
 *
 * algorithms
 * Easy (90.08%)
 * Likes:    2629
 * Dislikes: 336
 * Total Accepted:    333.2K
 * Total Submissions: 370K
 * Testcase Example:  '[1,3]'
 *
 * The XOR total of an array is defined as the bitwise XOR of all its elements,
 * or 0 if the array is empty.
 * 
 * 
 * For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
 * 
 * 
 * Given an array nums, return the sum of all XOR totals for every subset of
 * nums. 
 * 
 * Note: Subsets with the same elements should be counted multiple times.
 * 
 * An array a is a subset of an array b if a can be obtained from b by deleting
 * some (possibly zero) elements of b.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3]
 * Output: 6
 * Explanation: The 4 subsets of [1,3] are:
 * - The empty subset has an XOR total of 0.
 * - [1] has an XOR total of 1.
 * - [3] has an XOR total of 3.
 * - [1,3] has an XOR total of 1 XOR 3 = 2.
 * 0 + 1 + 3 + 2 = 6
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,1,6]
 * Output: 28
 * Explanation: The 8 subsets of [5,1,6] are:
 * - The empty subset has an XOR total of 0.
 * - [5] has an XOR total of 5.
 * - [1] has an XOR total of 1.
 * - [6] has an XOR total of 6.
 * - [5,1] has an XOR total of 5 XOR 1 = 4.
 * - [5,6] has an XOR total of 5 XOR 6 = 3.
 * - [1,6] has an XOR total of 1 XOR 6 = 7.
 * - [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
 * 0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [3,4,5,6,7,8]
 * Output: 480
 * Explanation: The sum of all XOR totals for every subset is 480.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 12
 * 1 <= nums[i] <= 20
 * 
 * 
 */
#include <vector>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    // 数学：二进制：
    // 若只有01，只要nums中包含1，选偶数个1有2^(i+1)个组合，每个组合的异或结果为1，它们的和为2^(i+1)
    // 回到题目，由于是异或，只要nums有一个元素的第n位为1，则选偶数个第n位为1有2^(i+1)个组合，
    // 每个组合第n位的异或结果为1，它们的和为(2^n)*(2^(i+1))
    // 由此可知，问题的解就是：(所有元素的或) × 2^(i+1)
    // 如用例2：5 + 1 + 6 = 二进制1100，答案即为：(2^2+2^3)*(2^(i+1))=12*(2^(i+1))
    int subsetXORSum1(vector<int>& nums) {
        int or_sum = 0;
        for (int i : nums) {
            or_sum |= i;
        }
        return or_sum << (nums.size() - 1);
        // return reduce(nums.begin(), nums.end(), 0, bit_or()) << (nums.size() - 1);
    }

    // 回溯解法：选或不选
    int subsetXORSum2(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int xor_sum = 0;

        auto dfs = [&](this auto &&dfs, int i) -> void {
            if (i == n) {
                ans += xor_sum;
                return;
            }

            dfs(i + 1);

            xor_sum ^= nums[i];
            dfs(i + 1);
            xor_sum ^= nums[i];
        };
        dfs(0);
        return ans;
    }

    // 回溯解法：枚举哪一个
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int xor_sum = 0;

        auto dfs = [&](this auto &&dfs, int i) -> void {
            ans += xor_sum;

            for (int j = i; j < n; j++) {
                xor_sum ^= nums[j];
                dfs(j + 1);
                xor_sum ^= nums[j];
            }
        };
        dfs(0);
        return ans;
    }
};
// @lc code=end

