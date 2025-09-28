/*
 * @lc app=leetcode id=3152 lang=cpp
 *
 * [3152] Special Array II
 *
 * https://leetcode.com/problems/special-array-ii/description/
 *
 * algorithms
 * Medium (45.69%)
 * Likes:    905
 * Dislikes: 67
 * Total Accepted:    135.9K
 * Total Submissions: 297.5K
 * Testcase Example:  '[3,4,1,2,6]\n[[0,4]]'
 *
 * An array is considered special if every pair of its adjacent elements
 * contains two numbers with different parity.
 * 
 * You are given an array of integer nums and a 2D integer matrix queries,
 * where for queries[i] = [fromi, toi] your task is to check that subarray
 * nums[fromi..toi] is special or not.
 * 
 * Return an array of booleans answer such that answer[i] is true if
 * nums[fromi..toi] is special.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,4,1,2,6], queries = [[0,4]]
 * 
 * Output: [false]
 * 
 * Explanation:
 * 
 * The subarray is [3,4,1,2,6]. 2 and 6 are both even.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
 * 
 * Output: [false,true]
 * 
 * Explanation:
 * 
 * 
 * The subarray is [4,3,1]. 3 and 1 are both odd. So the answer to this query
 * is false.
 * The subarray is [1,6]. There is only one pair: (1,6) and it contains numbers
 * with different parity. So the answer to this query is true.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 1 <= queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> presum(nums.size());
        for (int i = 1; i < nums.size(); i++) {
            presum[i] = presum[i - 1] + (nums[i - 1] % 2 == nums[i] % 2);
        }
        vector<bool> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            auto &q = queries[i];
            ans[i] = presum[q[0]] == presum[q[1]];
        }
        return ans;
    }
};
// @lc code=end

