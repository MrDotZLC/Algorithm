/*
 * @lc app=leetcode id=3143 lang=cpp
 *
 * [3143] Maximum Points Inside the Square
 *
 * https://leetcode.com/problems/maximum-points-inside-the-square/description/
 *
 * algorithms
 * Medium (38.32%)
 * Likes:    163
 * Dislikes: 24
 * Total Accepted:    19.8K
 * Total Submissions: 51.5K
 * Testcase Example:  '[[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]]\n"abdca"'
 *
 * You are given a 2D array points and a string s where, points[i] represents
 * the coordinates of point i, and s[i] represents the tag of point i.
 * 
 * A valid square is a square centered at the origin (0, 0), has edges parallel
 * to the axes, and does not contain two points with the same tag.
 * 
 * Return the maximum number of points contained in a valid square.
 * 
 * Note:
 * 
 * 
 * A point is considered to be inside the square if it lies on or within the
 * square's boundaries.
 * The side length of the square can be zero.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * The square of side length 4 covers two points points[0] and points[1].
 * 
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: points = [[1,1],[-2,-2],[-2,2]], s = "abb"
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * The square of side length 2 covers one point, which is points[0].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: points = [[1,1],[-1,-1],[2,-2]], s = "ccd"
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * It's impossible to make any valid squares centered at the origin such that
 * it covers only one point among points[0] and points[1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length, points.length <= 10^5
 * points[i].length == 2
 * -10^9 <= points[i][0], points[i][1] <= 10^9
 * s.length == points.length
 * points consists of distinct coordinates.
 * s consists only of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = points.size(), ans = 0;
        auto check = [&](int mid) -> bool {
            int cnt[26] = {0};
            int counter = 0;
            for (int i = 0; i < points.size(); i++) {
                if (abs(points[i][0]) <= mid && abs(points[i][1]) <= mid) {
                    char c = s[i] - 'a';
                    if (cnt[s[i] - 'a'] > 0) {
                        return false;
                    }
                    cnt[s[i] - 'a'] = 1;
                    counter++;
                }
            }
            ans = counter;
            return true;
        };

        int L = -1, R = 1e9 + 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid;
        }
        return ans;
    }

};
// @lc code=end

