/*
 * @lc app=leetcode id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 *
 * https://leetcode.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (65.40%)
 * Likes:    34576
 * Dislikes: 619
 * Total Accepted:    3M
 * Total Submissions: 4.5M
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
 * section) are being trapped.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 前缀和
    int trap1(vector<int>& height) {
        int ans = 0, n = height.size();
        int pre_max = height[0];
        vector<int> suf_max(n);
        suf_max[n - 1] = height[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suf_max[i] = max(suf_max[i + 1], height[i]);
        }

        for (int i = 0; i < n; i++) {
            pre_max = max(pre_max, height[i]);
            ans += min(pre_max, suf_max[i]) - height[i];
        }
        return ans;
    }

    // 双指针
    int trap2(vector<int>& height) {
        int ans = 0, pre_max = 0, suf_max = 0;
        int l = 0, r = height.size() - 1;
        
        while (l < r) { // 相等时，为最高的柱子，接不到水
            pre_max = max(pre_max, height[l]);
            suf_max = max(suf_max, height[r]);
            if (pre_max < suf_max) {
                ans += pre_max - height[l++];
            } else {
                ans += suf_max - height[r--];
            }
        }

        return ans;
    }

    // 单调栈
    int trap(vector<int>& height) {
        int ans = 0, n = height.size();
        vector<int> stk;

        for (int r = 0; r < n; r++) {
            int h = height[r];
            while (!stk.empty() && height[stk.back()] <= h) {
                int bottom_h = height[stk.back()];
                stk.pop_back();
                if (stk.empty()) {
                    break;
                }
                int l = stk.back();
                ans += (min(height[l], h) - bottom_h) * (r - l - 1);
            }
            stk.push_back(r);
        }
        
        return ans;
    }
};
// @lc code=end

