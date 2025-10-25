/*
 * @lc app=leetcode id=440 lang=cpp
 *
 * [440] K-th Smallest in Lexicographical Order
 *
 * https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/
 *
 * algorithms
 * Hard (45.95%)
 * Likes:    1632
 * Dislikes: 147
 * Total Accepted:    164.7K
 * Total Submissions: 358K
 * Testcase Example:  '13\n2'
 *
 * Given two integers n and k, return the k^th lexicographically smallest
 * integer in the range [1, n].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 13, k = 2
 * Output: 10
 * Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6,
 * 7, 8, 9], so the second smallest number is 10.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1, k = 1
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= n <= 10^9
 * 
 * 
 */
#include <algorithm>
// @lc code=start
class Solution {
public:
    int findKthNumber(int n, int k) {
        // 逐层统计node子树大小
        auto count_subtree_size = [&](int node) -> int {
            int size = 0;
            long long l = node, r = node + 1; // 可能会超出int
            while (l <= n) {
                // 这一层的最小值是l，最大值是min(r, n + 1) - 1
                size += std::min(r, n + 1LL) - 1 - l + 1;
                l *= 10;
                r *= 10;
            }
            return size;
        };

        int node = 1;
        k--;
        while (k > 0) {
            int size = count_subtree_size(node);
            if (size <= k) { // 向右跳
                k -= size;
                node++;
            } else {
                node *= 10; // 向下跳
                k--;
            }
        }
        return node;
    }
};
// @lc code=end

