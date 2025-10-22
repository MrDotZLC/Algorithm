/*
 * @lc app=leetcode id=2208 lang=cpp
 *
 * [2208] Minimum Operations to Halve Array Sum
 *
 * https://leetcode.com/problems/minimum-operations-to-halve-array-sum/description/
 *
 * algorithms
 * Medium (49.05%)
 * Likes:    664
 * Dislikes: 30
 * Total Accepted:    49.4K
 * Total Submissions: 99.7K
 * Testcase Example:  '[5,19,8,1]'
 *
 * You are given an array nums of positive integers. In one operation, you can
 * choose any number from nums and reduce it to exactly half the number. (Note
 * that you may choose this reduced number in future operations.)
 * 
 * Return the minimum number of operations to reduce the sum of nums by at
 * least half.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,19,8,1]
 * Output: 3
 * Explanation: The initial sum of nums is equal to 5 + 19 + 8 + 1 = 33.
 * The following is one of the ways to reduce the sum by at least half:
 * Pick the number 19 and reduce it to 9.5.
 * Pick the number 9.5 and reduce it to 4.75.
 * Pick the number 8 and reduce it to 4.
 * The final array is [5, 4.75, 4, 1] with a total sum of 5 + 4.75 + 4 + 1 =
 * 14.75. 
 * The sum of nums has been reduced by 33 - 14.75 = 18.25, which is at least
 * half of the initial sum, 18.25 >= 33/2 = 16.5.
 * Overall, 3 operations were used so we return 3.
 * It can be shown that we cannot reduce the sum by at least half in less than
 * 3 operations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,8,20]
 * Output: 3
 * Explanation: The initial sum of nums is equal to 3 + 8 + 20 = 31.
 * The following is one of the ways to reduce the sum by at least half:
 * Pick the number 20 and reduce it to 10.
 * Pick the number 10 and reduce it to 5.
 * Pick the number 3 and reduce it to 1.5.
 * The final array is [1.5, 8, 5] with a total sum of 1.5 + 8 + 5 = 14.5. 
 * The sum of nums has been reduced by 31 - 14.5 = 16.5, which is at least half
 * of the initial sum, 16.5 >= 31/2 = 15.5.
 * Overall, 3 operations were used so we return 3.
 * It can be shown that we cannot reduce the sum by at least half in less than
 * 3 operations.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^7
 * 
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    int halveArray(vector<int>& nums) {
        int ans = 0;
        priority_queue<long long> pq;
        long long half = 0;
        for (int i = 0; i < nums.size(); i++) {
            // 乘2^20为了避免浮点运算造成的精度损失
            // 证明：设最大x减半t次，所有数不大于x/2^(t-1)，总和<=n*x/2^(t-1)，
            // 原始和的一半至少为x/2，n*x/2^(t-1) > x/2，得t < log2(n) + 2
            // n最大为10^5，则任意值乘上大于等于2^19的数，即可保证整数运算
            pq.push(nums[i] * pow(2, 20));
            half += nums[i] * pow(2, 20);
        }
        half /= 2;
        while (half > 0) {
            long long x = pq.top() / 2;
            pq.pop();
            half -= x;
            pq.push(x);
            ans++;
        }
        return ans;
    }
};
// @lc code=end

