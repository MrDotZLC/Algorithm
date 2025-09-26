/*
 * @lc app=leetcode id=3623 lang=cpp
 *
 * [3623] Count Number of Trapezoids I
 *
 * https://leetcode.com/problems/count-number-of-trapezoids-i/description/
 *
 * algorithms
 * Medium (29.09%)
 * Likes:    67
 * Dislikes: 10
 * Total Accepted:    25.3K
 * Total Submissions: 84.1K
 * Testcase Example:  '[[1,0],[2,0],[3,0],[2,2],[3,2]]'
 *
 * You are given a 2D integer array points, where points[i] = [xi, yi]
 * represents the coordinates of the i^th point on the Cartesian plane.
 * 
 * A horizontal trapezoid is a convex quadrilateral with at least one pair of
 * horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if
 * and only if they have the same slope.
 * 
 * Return the  number of unique horizontal trapezoids that can be formed by
 * choosing any four distinct points from points.
 * 
 * Since the answer may be very large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * ⁠ 
 * 
 * There are three distinct ways to pick four points that form a horizontal
 * trapezoid:
 * 
 * 
 * Using points [1,0], [2,0], [3,2], and [2,2].
 * Using points [2,0], [3,0], [3,2], and [2,2].
 * Using points [1,0], [3,0], [3,2], and [2,2].
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: points = [[0,0],[1,0],[0,1],[2,1]]
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * 
 * 
 * There is only one horizontal trapezoid that can be formed.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 4 <= points.length <= 10^5
 * –10^8 <= xi, yi <= 10^8
 * All points are pairwise distinct.
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
    int countTrapezoids1(vector<vector<int>>& points) {
        int MOD = 1e9 + 7;
        unordered_map<int, int> cnt;
        for (auto &p : points) {
            cnt[p[1]]++;
        }

        long long ans = 0, s = 0;
        for (auto &[_, c] : cnt) {
            long long k = 1LL * c * (c - 1) / 2;
            ans += s * k;
            s += k;
        }
        return ans % MOD;
    }

    // 存在重复点
    int countTrapezoids(vector<vector<int>>& points) {
        int MOD = 1e9 + 7;
        unordered_map<int, vector<int>> row; // 按 y 分组
        for (auto &p : points) {
            row[p[1]].push_back(p[0]);
        }

        long long ans = 0, s = 0;
        for (auto &[_, xs] : row) {
            long long total = xs.size();
            long long rowPairs = total * (total - 1) / 2;

            unordered_map<int, int> freq;
            for (int x : xs) freq[x]++;
            for (auto &[x, c] : freq) {
                rowPairs -= 1LL * c * (c - 1) / 2; // 减去同 x 点对
            }

            ans += s * rowPairs;
            s += rowPairs;
            ans %= MOD;
            s %= MOD;
        }
        return ans;
    }
};
// @lc code=end

