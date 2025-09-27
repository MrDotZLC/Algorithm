/*
 * @lc app=leetcode id=447 lang=cpp
 *
 * [447] Number of Boomerangs
 *
 * https://leetcode.com/problems/number-of-boomerangs/description/
 *
 * algorithms
 * Medium (56.51%)
 * Likes:    879
 * Dislikes: 1038
 * Total Accepted:    112.3K
 * Total Submissions: 198K
 * Testcase Example:  '[[0,0],[1,0],[2,0]]'
 *
 * You are given n points in the plane that are all distinct, where points[i] =
 * [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance
 * between i and j equals the distance between i and k (the order of the tuple
 * matters).
 * 
 * Return the number of boomerangs.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: points = [[0,0],[1,0],[2,0]]
 * Output: 2
 * Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and
 * [[1,0],[2,0],[0,0]].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: points = [[1,1],[2,2],[3,3]]
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: points = [[1,1]]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == points.length
 * 1 <= n <= 500
 * points[i].length == 2
 * -10^4 <= xi, yi <= 10^4
 * All the points are unique.
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
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int ans = 0;
        unordered_map<int, int> cnt;
        for (auto &p1 : points){
            cnt.clear();
            for (auto &p2 : points) {
                int d = (p2[0] - p1[0]) * (p2[0] - p1[0]) + (p2[1] - p1[1]) * (p2[1] - p1[1]);
                ans += cnt[d]++ * 2;
            }
        }
        return ans;
    }
};
// @lc code=end

