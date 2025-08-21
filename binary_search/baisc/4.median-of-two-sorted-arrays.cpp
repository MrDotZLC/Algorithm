/*
 * @lc app=leetcode id=4 lang=cpp
 *
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (44.14%)
 * Likes:    30680
 * Dislikes: 3449
 * Total Accepted:    3.6M
 * Total Submissions: 8.1M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return
 * the median of the two sorted arrays.
 * 
 * The overall run time complexity should be O(log (m+n)).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * Explanation: merged array = [1,2,3] and median is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -10^6 <= nums1[i], nums2[i] <= 10^6
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int m = nums1.size(), n = nums2.size();
        // nums1.insert(nums1.begin(), INT_MIN);
        // nums1.push_back(INT_MAX);
        // nums2.insert(nums2.begin(), INT_MIN);
        // nums2.push_back(INT_MAX);

        int L = -1, R = m; // int L = 0, R = m + 1;
        while (L + 1 < R) {
            int i = L + (R - L) / 2;
            int j = (m + n + 1) / 2 - i - 2; // (m + n + 1) / 2 - i
            (nums1[i] <= nums2[j + 1] ? L : R) = i;
        }

        int i = L;
        int j = (m + n + 1) / 2 - i - 2;  // (m + n + 1) / 2 - i
        int ai = i >= 0 ? nums1[i] : INT_MIN;
        int bj = j >= 0 ? nums2[j] : INT_MIN;
        int ai1 = i + 1 < m ? nums1[i + 1] : INT_MAX;
        int bj1 = j + 1 < n ? nums2[j + 1] : INT_MAX;
        int max1 = max(ai, bj);
        int min2 = min(ai1, bj1);
        return (m + n) % 2 ? max1 : (max1 + min2) / 2.0; 
    }
};
// @lc code=end

