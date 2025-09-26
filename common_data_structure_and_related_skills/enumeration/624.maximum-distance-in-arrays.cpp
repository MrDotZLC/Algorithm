/*
 * @lc app=leetcode id=624 lang=cpp
 *
 * [624] Maximum Distance in Arrays
 *
 * https://leetcode.com/problems/maximum-distance-in-arrays/description/
 *
 * algorithms
 * Medium (45.61%)
 * Likes:    1484
 * Dislikes: 118
 * Total Accepted:    195.5K
 * Total Submissions: 428.7K
 * Testcase Example:  '[[1,2,3],[4,5],[1,2,3]]'
 *
 * You are given m arrays, where each array is sorted in ascending order.
 * 
 * You can pick up two integers from two different arrays (each array picks
 * one) and calculate the distance. We define the distance between two integers
 * a and b to be their absolute difference |a - b|.
 * 
 * Return the maximum distance.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arrays = [[1,2,3],[4,5],[1,2,3]]
 * Output: 4
 * Explanation: One way to reach the maximum distance 4 is to pick 1 in the
 * first or third array and pick 5 in the second array.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arrays = [[1],[1]]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == arrays.length
 * 2 <= m <= 10^5
 * 1 <= arrays[i].length <= 500
 * -10^4 <= arrays[i][j] <= 10^4
 * arrays[i] is sorted in ascending order.
 * There will be at most 10^5 integers in all the arrays.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxDistance1(vector<vector<int>>& arrays) {
        int ans = 0;
        int mn = INT_MAX / 2, mx = INT_MIN / 2;
        for (auto &a : arrays) {
            ans = max({ans, a.back() - mn, mx - a[0]});
            mn = min(mn, a[0]);
            mx = max(mx, a.back());
        }
        return ans;
    }
};
// @lc code=end

