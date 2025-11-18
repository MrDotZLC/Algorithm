/* 
    3670. Maximum Product of Two Integers With No Common Bits
    Medium
    Topics
    premium lock icon
    Companies
    Hint
    You are given an integer array nums.

    Your task is to find two distinct indices i and j such that the product nums[i] * nums[j] is maximized, and the binary representations of nums[i] and nums[j] do not share any common set bits.

    Return the maximum possible product of such a pair. If no such pair exists, return 0.

    

    Example 1:

    Input: nums = [1,2,3,4,5,6,7]

    Output: 12

    Explanation:

    The best pair is 3 (011) and 4 (100). They share no set bits and 3 * 4 = 12.

    Example 2:

    Input: nums = [5,6,4]

    Output: 0

    Explanation:

    Every pair of numbers has at least one common set bit. Hence, the answer is 0.

    Example 3:

    Input: nums = [64,8,32]

    Output: 2048

    Explanation:

    No pair of numbers share a common bit, so the answer is the product of the two maximum elements, 64 and 32 (64 * 32 = 2048).

    

    Constraints:

    2 <= nums.length <= 105
    1 <= nums[i] <= 106
*/
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief 
 * 子集型状压DP
 * 枚举numsi，为使得乘积最大，则numsj应是除numsi的最大值
 * 暴力枚举超时O(n^2)，可预处理numsi补集的来自nums的子集最大值(O(n+UlogU))
 * f(i)表示下标集合i的来自nums的子集最大值
 * f(Ti)=max(f(i^{j})), j∈i
 * ans=max(numsi * numsi补集的来自nums的子集最大值)
 * 边界：f[x]=x
 */
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int n = nums.size(),
            mx = bit_width((unsigned) ranges::max(nums)), m = 1 << mx;
        vector<int> f(m);
        for (int x : nums) {
            f[x] = x;
        }

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < mx; j ++) {
                if (i >> j & 1) {
                    f[i] = max(f[i], f[i ^ 1 << j]);
                }
            }
        }

        long long ans = 0;
        for (int x : nums) {
            ans = max(ans, 1LL * x * f[(m - 1) ^ x]);
        }
        return ans;
    }
};