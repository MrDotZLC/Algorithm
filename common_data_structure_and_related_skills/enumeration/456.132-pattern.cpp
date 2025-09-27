/*
 * @lc app=leetcode id=456 lang=cpp
 *
 * [456] 132 Pattern
 *
 * https://leetcode.com/problems/132-pattern/description/
 *
 * algorithms
 * Medium (34.11%)
 * Likes:    7517
 * Dislikes: 460
 * Total Accepted:    303.8K
 * Total Submissions: 886.8K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given an array of n integers nums, a 132 pattern is a subsequence of three
 * integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] <
 * nums[k] < nums[j].
 * 
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4]
 * Output: false
 * Explanation: There is no 132 pattern in the sequence.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,1,4,2]
 * Output: true
 * Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [-1,3,2,0]
 * Output: true
 * Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1,
 * 3, 0] and [-1, 2, 0].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length
 * 1 <= n <= 2 * 10^5
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <stack>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        int n = nums.size();
        vector<int> mins(n);
        mins[0] = INT_MAX;
        for (int i = 1; i < n; i++) {
            mins[i] = min(mins[i - 1], nums[i - 1]);
        }
        stack<int> st;
        for (int j = nums.size() - 1; j >= 1; j--) {
            int x = nums[j], mn = mins[j];
            if (x <= mn) {
                continue;
            }
            while (!st.empty() && st.top() <= mn) {
                st.pop();
            }
            if (!st.empty() && st.top() < x) {
                return true;
            }
            st.push(x);
        }
        return false;
    }
};
// @lc code=end

