/*
 * @lc app=leetcode id=739 lang=cpp
 *
 * [739] Daily Temperatures
 *
 * https://leetcode.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (67.49%)
 * Likes:    14201
 * Dislikes: 359
 * Total Accepted:    1.5M
 * Total Submissions: 2.2M
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * Given an array of integers temperatures represents the daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to
 * wait after the i^th day to get a warmer temperature. If there is no future
 * day for which this is possible, keep answer[i] == 0 instead.
 * 
 * 
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= temperatures.length <= 10^5
 * 30 <= temperatures[i] <= 100
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 从左向右
    vector<int> dailyTemperatures1(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        vector<int> stk;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && temperatures[stk.back()] < temperatures[i]) {
                int idx = stk.back();
                stk.pop_back();
                ans[idx] = i - idx;
            }
            stk.push_back(i);
        }
        return ans;
    }

    // 从右向左
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        vector<int> stk;
        for (int i = n - 1; i >= 0; i--) {
            int t = temperatures[i];
            while (!stk.empty() && temperatures[stk.back()] <= t) {
                stk.pop_back();
            }
            if (!stk.empty()) {
                ans[i] = stk.back() - i;
            }
            stk.push_back(i);
        }
        return ans;
    }
};
// @lc code=end

