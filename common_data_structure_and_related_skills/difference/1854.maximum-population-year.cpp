/*
 * @lc app=leetcode id=1854 lang=cpp
 *
 * [1854] Maximum Population Year
 *
 * https://leetcode.com/problems/maximum-population-year/description/
 *
 * algorithms
 * Easy (62.82%)
 * Likes:    1489
 * Dislikes: 278
 * Total Accepted:    103K
 * Total Submissions: 163.3K
 * Testcase Example:  '[[1993,1999],[2000,2010]]'
 *
 * You are given a 2D integer array logs where each logs[i] = [birthi, deathi]
 * indicates the birth and death years of the i^th person.
 * 
 * The population of some year x is the number of people alive during that
 * year. The i^th person is counted in year x's population if x is in the
 * inclusive range [birthi, deathi - 1]. Note that the person is not counted in
 * the year that they die.
 * 
 * Return the earliest year with the maximum population.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: logs = [[1993,1999],[2000,2010]]
 * Output: 1993
 * Explanation: The maximum population is 1, and 1993 is the earliest year with
 * this population.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
 * Output: 1960
 * Explanation: 
 * The maximum population is 2, and it had happened in years 1960 and 1970.
 * The earlier year between them is 1960.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= logs.length <= 100
 * 1950 <= birthi < deathi <= 2050
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> diff(2051);
        for (auto &interval : logs) {
            diff[interval[0]]++;
            diff[interval[1]]--;
        }

        int ans = 1950, sum = 0, max = 0;
        for (int i = 1950; i < diff.size(); i++) {
            sum += diff[i];
            if (sum > max) {
                max = sum;
                ans = i;
            }
        }
        return ans;
    }
};
// @lc code=end

