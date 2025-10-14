/*
 * @lc app=leetcode id=84 lang=cpp
 *
 * [84] Largest Rectangle in Histogram
 *
 * https://leetcode.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (47.72%)
 * Likes:    18858
 * Dislikes: 363
 * Total Accepted:    1.3M
 * Total Submissions: 2.8M
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle
 * in the histogram.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 * Explanation: The above is a histogram where width of each bar is 1.
 * The largest rectangle is shown in the red area, which has an area = 10
 * units.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: heights = [2,4]
 * Output: 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= heights.length <= 10^5
 * 0 <= heights[i] <= 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int largestRectangleArea1(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n, -1); // i左侧小于height[i]
        // i右侧小于等于height[i]，哪怕有重复元素，
        // 其中一个元素一定不会算漏，如此就能一次循环得到左右两边的最小下标
        // 如：13531，第一个3会算漏得3*2，第二个则不会得3*3
        vector<int> right(n, n); // i右侧小于等于height[i]
        vector<int> stk;

        for (int i = 0; i < n; i++) {
            int h = heights[i];
            while (!stk.empty() && h <= heights[stk.back()]) {
                right[stk.back()] = i;
                stk.pop_back();
            }
            if (!stk.empty()) {
                left[i] = stk.back();
            }
            stk.push_back(i);
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, heights[i] * (right[i] - 1 - left[i])); // 宽度为r-1-(l+1)+1=r-l-1;
        }
        return ans;
    }

    // 一次遍历，遍历栈顶右侧最近更小高度，栈顶左侧最近更小高度即是栈顶下的值，
    // 初始化将-1压入栈和heights，保证找到左界和栈有效值清空
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(-1);
        int n = heights.size();
        // i右侧小于等于height[i]，哪怕有重复元素，
        // 其中一个元素一定不会算漏，如此就能一次循环得到左右两边的最小下标
        // 如：13531，第一个3会算漏得3*2，第二个则不会得3*3
        vector<int> stk;
        stk.push_back(-1);
        int ans = 0;

        for (int r = 0; r < n; r++) {
            int h = heights[r];
            while (stk.size() > 1 && h <= heights[stk.back()]) {
                int i = stk.back(); // 矩形高
                stk.pop_back();
                int l = stk.back();
                ans = max(ans, heights[i] * (r - l - 1)); // 宽度为r-1-(l+1)+1=r-l-1;
            }
            stk.push_back(r);
        }

        return ans;
    }
};
// @lc code=end

