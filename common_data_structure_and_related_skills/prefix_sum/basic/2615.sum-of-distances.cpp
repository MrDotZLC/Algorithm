/*
 * @lc app=leetcode id=2615 lang=cpp
 *
 * [2615] Sum of Distances
 *
 * https://leetcode.com/problems/sum-of-distances/description/
 *
 * algorithms
 * Medium (31.47%)
 * Likes:    808
 * Dislikes: 95
 * Total Accepted:    26.3K
 * Total Submissions: 82.6K
 * Testcase Example:  '[1,3,1,1,2]'
 *
 * You are given a 0-indexed integer array nums. There exists an array arr of
 * length nums.length, where arr[i] is the sum of |i - j| over all j such that
 * nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.
 * 
 * Return the array arr.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,1,1,2]
 * Output: [5,0,3,4,0]
 * Explanation: 
 * When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] =
 * |0 - 2| + |0 - 3| = 5. 
 * When i = 1, arr[1] = 0 because there is no other index with value 3.
 * When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] =
 * |2 - 0| + |2 - 3| = 3. 
 * When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] =
 * |3 - 0| + |3 - 2| = 4. 
 * When i = 4, arr[4] = 0 because there is no other index with value 2. 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,5,3]
 * Output: [0,0,0]
 * Explanation: Since each element in nums is distinct, arr[i] = 0 for all
 * i.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 
 * 
 * 
 * Note: This question is the same as  2121: Intervals Between Identical
 * Elements.
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < n; i++) {
            groups[nums[i]].push_back(i);
        }

        vector<long long> ans(n);
        vector<long long> sum(n + 1);
        for (auto &[_, a] : groups) {
            int m = a.size();
            for (int i = 0; i < m; i++) {
                sum[i + 1] = sum[i] + a[i];
            }
            for (int i = 0; i < m; i++) {
                long long target = a[i];
                long long left = i * target - sum[i];
                long long right = sum[m] - sum[i] - target * (m - i);
                ans[target] = left + right;
            }
        }
        return ans;
    }
};
// @lc code=end

