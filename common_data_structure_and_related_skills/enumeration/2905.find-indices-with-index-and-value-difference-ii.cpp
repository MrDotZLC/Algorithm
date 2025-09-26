/*
 * @lc app=leetcode id=2905 lang=cpp
 *
 * [2905] Find Indices With Index and Value Difference II
 *
 * https://leetcode.com/problems/find-indices-with-index-and-value-difference-ii/description/
 *
 * algorithms
 * Medium (31.98%)
 * Likes:    290
 * Dislikes: 11
 * Total Accepted:    21.6K
 * Total Submissions: 67.1K
 * Testcase Example:  '[5,1,4,1]\n2\n4'
 *
 * You are given a 0-indexed integer array nums having length n, an integer
 * indexDifference, and an integer valueDifference.
 * 
 * Your task is to find two indices i and j, both in the range [0, n - 1], that
 * satisfy the following conditions:
 * 
 * 
 * abs(i - j) >= indexDifference, and
 * abs(nums[i] - nums[j]) >= valueDifference
 * 
 * 
 * Return an integer array answer, where answer = [i, j] if there are two such
 * indices, and answer = [-1, -1] otherwise. If there are multiple choices for
 * the two indices, return any of them.
 * 
 * Note: i and j may be equal.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,1,4,1], indexDifference = 2, valueDifference = 4
 * Output: [0,3]
 * Explanation: In this example, i = 0 and j = 3 can be selected.
 * abs(0 - 3) >= 2 and abs(nums[0] - nums[3]) >= 4.
 * Hence, a valid answer is [0,3].
 * [3,0] is also a valid answer.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,1], indexDifference = 0, valueDifference = 0
 * Output: [0,0]
 * Explanation: In this example, i = 0 and j = 0 can be selected.
 * abs(0 - 0) >= 0 and abs(nums[0] - nums[0]) >= 0.
 * Hence, a valid answer is [0,0].
 * Other valid answers are [0,1], [1,0], and [1,1].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3], indexDifference = 2, valueDifference = 4
 * Output: [-1,-1]
 * Explanation: In this example, it can be shown that it is impossible to find
 * two indices that satisfy both conditions.
 * Hence, [-1,-1] is returned.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n == nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 0 <= indexDifference <= 10^5
 * 0 <= valueDifference <= 10^9
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> findIndices(vector<int> &nums, int indexDifference,
                            int valueDifference) {
        int mx_id = 0, mn_id = 0;
        for (int j = indexDifference; j < nums.size(); j++) {
            int i = j - indexDifference;
            if (nums[i] > nums[mx_id]) {
                mx_id = i;
            } else if (nums[i] < nums[mn_id]) {
                mn_id = i;
            }
            if (nums[mx_id] - nums[j] >= valueDifference) {
                return {mx_id, j};
            }
            if (nums[j] - nums[mn_id] >= valueDifference) {
                return {mn_id, j};
            }
        }
        return {-1, -1};
    }

    // 思考题：改成求满足要求的下标对的个数，要怎么做？
    int countPairs(vector<int>& nums, int indexDifference, int valueDifference) {
        int n = nums.size();
        multiset<int> window; // 保存 i 对应的 nums[i]

        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (j > indexDifference) {
                // 把 j - indexDifference - 1 对应的元素加入窗口
                window.insert(nums[j - indexDifference - 1]);
            }
            // 统计 window 中满足条件的元素
            // nums[i] <= nums[j] - valueDifference 或 nums[i] >= nums[j] + valueDifference
            count += distance(window.begin(), window.lower_bound(nums[j] - valueDifference + 1));
            count += distance(window.lower_bound(nums[j] + valueDifference), window.end());
        }
        return count;
    }
};
// @lc code=end

