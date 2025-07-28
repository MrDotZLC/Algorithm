/*
 * @lc app=leetcode id=1574 lang=cpp
 *
 * [1574] Shortest Subarray to be Removed to Make Array Sorted
 *
 * https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/description/
 *
 * algorithms
 * Medium (51.42%)
 * Likes:    2402
 * Dislikes: 156
 * Total Accepted:    121.6K
 * Total Submissions: 236.5K
 * Testcase Example:  '[1,2,3,10,4,2,3,5]'
 *
 * Given an integer array arr, remove a subarray (can be empty) from arr such
 * that the remaining elements in arr are non-decreasing.
 * 
 * Return the length of the shortest subarray to remove.
 * 
 * A subarray is a contiguous subsequence of the array.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,3,10,4,2,3,5]
 * Output: 3
 * Explanation: The shortest subarray we can remove is [10,4,2] of length 3.
 * The remaining elements after that will be [1,2,3,3,5] which are sorted.
 * Another correct solution is to remove the subarray [3,10,4].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [5,4,3,2,1]
 * Output: 4
 * Explanation: Since the array is strictly decreasing, we can only keep a
 * single element. Therefore we need to remove a subarray of length 4, either
 * [5,4,3,2] or [4,3,2,1].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [1,2,3]
 * Output: 0
 * Explanation: The array is already non-decreasing. We do not need to remove
 * any elements.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 0 <= arr[i] <= 10^9
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size(), l = 0, r = n - 1;
        while (r > 0 && arr[r - 1] <= arr[r]) {
            r--;
        }
        if (r == 0) return 0;

        int ans = r;
        for (; ; r++) {
            while (r == n || arr[l] <= arr[r]) {
                ans = min(ans, r - l - 1);
                if (arr[l] > arr[l + 1]) {
                    return ans;
                }
                l++;
            }
        }
    }
};
// @lc code=end

