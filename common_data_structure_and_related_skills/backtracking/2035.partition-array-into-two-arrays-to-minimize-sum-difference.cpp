/*
 * @lc app=leetcode id=2035 lang=cpp
 *
 * [2035] Partition Array Into Two Arrays to Minimize Sum Difference
 *
 * https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
 *
 * algorithms
 * Hard (22.02%)
 * Likes:    3593
 * Dislikes: 242
 * Total Accepted:    49.9K
 * Total Submissions: 222.6K
 * Testcase Example:  '[3,9,7,3]'
 *
 * You are given an integer array nums of 2 * n integers. You need to partition
 * nums into two arrays of length n to minimize the absolute difference of the
 * sums of the arrays. To partition nums, put each element of nums into one of
 * the two arrays.
 * 
 * Return the minimum possible absolute difference.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,9,7,3]
 * Output: 2
 * Explanation: One optimal partition is: [3,9] and [7,3].
 * The absolute difference between the sums of the arrays is abs((3 + 9) - (7 +
 * 3)) = 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-36,36]
 * Output: 72
 * Explanation: One optimal partition is: [-36] and [36].
 * The absolute difference between the sums of the arrays is abs((-36) - (36))
 * = 72.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,-1,0,4,-2,-9]
 * Output: 0
 * Explanation: One optimal partition is: [2,4,-9] and [-1,0,-2].
 * The absolute difference between the sums of the arrays is abs((2 + 4 + -9) -
 * (-1 + 0 + -2)) = 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 15
 * nums.length == 2 * n
 * -10^7 <= nums[i] <= 10^7
 * 
 * 
 */
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size(), cnt = 0;
        vector<vector<int>> q(n / 2 + 1);
        function<void(int, int, int)> dfs = [&](int i, int sum, int cnt) {
            if (i == n / 2) {
                q[cnt].push_back(sum);
                return;
            }

            dfs(i + 1, sum - nums[i], cnt);
            dfs(i + 1, sum + nums[i], cnt + 1);
        };
        dfs(0, 0, 0);

        for (int i = 0; i <= n / 2; i++) {
            ranges::sort(q[i]);
        }

        int ans = INT_MAX;
        function<void(int, int, int)> dfs2 = [&](int i, int sum, int cnt) {
            if (cnt > n / 2) {
                return;
            }
            if (i == n) {
                auto &cur = q[cnt];
                int size = cur.size();
                int l = 0, r = size;
                while (l < r) {
                    int mid = l + (r - l) / 2;
                    if (cur[mid] < sum) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }
                }
                if (l < size) {
                    ans = min(ans, abs(sum - cur[l]));
                }
                if (l - 1 >= 0) {
                    ans = min(ans, abs(sum - cur[l - 1]));
                }
                return;
            }

            dfs2(i + 1, sum - nums[i], cnt);
            dfs2(i + 1, sum + nums[i], cnt + 1);
        };
        dfs2(n / 2, 0, 0);

        return ans;
    }
};
// @lc code=end

