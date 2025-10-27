/*
 * @lc app=leetcode id=1855 lang=cpp
 *
 * [1855] Maximum Distance Between a Pair of Values
 *
 * https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/description/
 *
 * algorithms
 * Medium (53.94%)
 * Likes:    1244
 * Dislikes: 30
 * Total Accepted:    58K
 * Total Submissions: 107.5K
 * Testcase Example:  '[55,30,5,4,2]\n[100,20,10,10,5]'
 *
 * You are given two non-increasing 0-indexed integer arrays nums1​​​​​​ and
 * nums2​​​​​​.
 * 
 * A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j <
 * nums2.length, is valid if both i <= j and nums1[i] <= nums2[j]. The distance
 * of the pair is j - i​​​​.
 * 
 * Return the maximum distance of any valid pair (i, j). If there are no valid
 * pairs, return 0.
 * 
 * An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i <
 * arr.length.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
 * Output: 2
 * Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4),
 * and (4,4).
 * The maximum distance is 2 with pair (2,4).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [2,2,2], nums2 = [10,10,1]
 * Output: 1
 * Explanation: The valid pairs are (0,0), (0,1), and (1,1).
 * The maximum distance is 1 with pair (0,1).
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
 * Output: 2
 * Explanation: The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
 * The maximum distance is 2 with pair (2,4).
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 10^5
 * 1 <= nums1[i], nums2[j] <= 10^5
 * Both nums1 and nums2 are non-increasing.
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
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int ans = 0;
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (j < i) j = i;
            if (n - i - 1 <= ans) break;
            if (nums1[i] > nums2[j]) {
                i++;
            } else {
                ans = max(ans, j - i);
                j++;;
            }
        }
        return ans;
    }
};
// @lc code=end

int main() {
    Solution sol;
    vector<int> nums1 = {9819,9508,7398,7347,6337,5756,5493,5446,5123,3215,1597,774,368,313};
    vector<int> nums2 = {9933,9813,9770,9697,9514,9490,9441,9439,8939,8754,8665,8560};
    sol.maxDistance(nums1, nums2);
}