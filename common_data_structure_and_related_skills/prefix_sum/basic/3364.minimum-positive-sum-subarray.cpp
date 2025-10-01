/*
 * @lc app=leetcode id=3364 lang=cpp
 *
 * [3364] Minimum Positive Sum Subarray 
 *
 * https://leetcode.com/problems/minimum-positive-sum-subarray/description/
 *
 * algorithms
 * Easy (44.51%)
 * Likes:    133
 * Dislikes: 29
 * Total Accepted:    39.3K
 * Total Submissions: 88.5K
 * Testcase Example:  '[3,-2,1,4]\n2\n3'
 *
 * You are given an integer array nums and two integers l and r. Your task is
 * to find the minimum sum of a subarray whose size is between l and r
 * (inclusive) and whose sum is greater than 0.
 * 
 * Return the minimum sum of such a subarray. If no such subarray exists,
 * return -1.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3, -2, 1, 4], l = 2, r = 3
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * The subarrays of length between l = 2 and r = 3 where the sum is greater
 * than 0 are:
 * 
 * 
 * [3, -2] with a sum of 1
 * [1, 4] with a sum of 5
 * [3, -2, 1] with a sum of 2
 * [-2, 1, 4] with a sum of 3
 * 
 * 
 * Out of these, the subarray [3, -2] has a sum of 1, which is the smallest
 * positive sum. Hence, the answer is 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-2, 2, -3, 1], l = 2, r = 3
 * 
 * Output: -1
 * 
 * Explanation:
 * 
 * There is no subarray of length between l and r that has a sum greater than
 * 0. So, the answer is -1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1, 2, 3, 4], l = 2, r = 4
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The subarray [1, 2] has a length of 2 and the minimum sum greater than 0.
 * So, the answer is 3.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= l <= r <= nums.length
 * -1000 <= nums[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <set>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int ans = __INT_MAX__, n = nums.size();
        vector<int> sum(n + 1);
        multiset<int> st;
        for (int j = 1; j < n + 1; j++) {
            sum[j] = sum[j -1] + nums[j - 1];
            if (j < l) {
                continue;
            }
            st.insert(sum[j - l]);
            auto it = st.lower_bound(sum[j]);
            if (it != st.begin()) {
                ans = min(ans, sum[j] - *--it);
            }
            if (j >= r) {
                st.erase(st.find(sum[j - r]));
            }
        }
        return ans == __INT_MAX__ ? -1 : ans;
    }
};
// @lc code=end

