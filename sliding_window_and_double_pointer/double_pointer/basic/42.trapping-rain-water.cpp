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
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int trap2(vector<int>& height) {
        int ans = 0, n = height.size();
        if (n == 1) {
            return 0;
        }
        int l = 0, r = n - 1, pre_max = 0, suf_max = 0;
        while (l < r) {
            pre_max = max(pre_max, height[l]);
            suf_max = max(suf_max, height[r]);
            ans += pre_max < suf_max ?
                pre_max - height[l++] :
                suf_max - height[r--]; 
        }
        return ans;
    }

    int trap(vector<int>& height) {
        int ans = 0, n = height.size();
        if (n == 1) {
            return 0;
        }
        vector<int> pre_max(n);
        pre_max[0] = height[0];
        vector<int> suf_max(n);
        suf_max[n - 1] = height[n - 1];
        for (int i = 1; i < n; i++) {
            pre_max[i] = max(pre_max[i - 1], height[i]);
            suf_max[n - i - 1] = max(suf_max[n - i], height[n - i - 1]);
        }

        for (int i = 0; i < n; i++) {
            ans += min(pre_max[i], suf_max[i]) - height[i]; 
        }
        return ans;
    }

};
// @lc code=end

