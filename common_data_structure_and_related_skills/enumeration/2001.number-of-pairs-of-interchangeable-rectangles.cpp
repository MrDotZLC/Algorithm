/*
 * @lc app=leetcode id=2001 lang=cpp
 *
 * [2001] Number of Pairs of Interchangeable Rectangles
 *
 * https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/description/
 *
 * algorithms
 * Medium (51.69%)
 * Likes:    568
 * Dislikes: 49
 * Total Accepted:    53.7K
 * Total Submissions: 103.9K
 * Testcase Example:  '[[4,8],[3,6],[10,20],[15,30]]'
 *
 * You are given n rectangles represented by a 0-indexed 2D integer array
 * rectangles, where rectangles[i] = [widthi, heighti] denotes the width and
 * height of the i^th rectangle.
 * 
 * Two rectangles i and j (i < j) are considered interchangeable if they have
 * the same width-to-height ratio. More formally, two rectangles are
 * interchangeable if widthi/heighti == widthj/heightj (using decimal division,
 * not integer division).
 * 
 * Return the number of pairs of interchangeable rectangles in rectangles.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
 * Output: 6
 * Explanation: The following are the interchangeable pairs of rectangles by
 * index (0-indexed):
 * - Rectangle 0 with rectangle 1: 4/8 == 3/6.
 * - Rectangle 0 with rectangle 2: 4/8 == 10/20.
 * - Rectangle 0 with rectangle 3: 4/8 == 15/30.
 * - Rectangle 1 with rectangle 2: 3/6 == 10/20.
 * - Rectangle 1 with rectangle 3: 3/6 == 15/30.
 * - Rectangle 2 with rectangle 3: 10/20 == 15/30.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: rectangles = [[4,5],[7,8]]
 * Output: 0
 * Explanation: There are no interchangeable pairs of rectangles.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == rectangles.length
 * 1 <= n <= 10^5
 * rectangles[i].length == 2
 * 1 <= widthi, heighti <= 10^5
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
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        long long ans = 0;
        unordered_map<double, int> idx;
        for (int j = 0; j < rectangles.size(); j++) {
            double ratio = (rectangles[j][0] + 0.0) / rectangles[j][1];
            ans += idx[ratio]++;
        }
        return ans;
    }
};
// @lc code=end

