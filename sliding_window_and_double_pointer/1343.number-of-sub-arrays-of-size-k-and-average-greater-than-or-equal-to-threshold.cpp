/*
 * @lc app=leetcode id=1343 lang=cpp
 *
 * [1343] Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
 *
 * https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/description/
 *
 * algorithms
 * Medium (70.40%)
 * Likes:    1739
 * Dislikes: 106
 * Total Accepted:    147.9K
 * Total Submissions: 210K
 * Testcase Example:  '[2,2,2,2,5,5,5,8]\n3\n4'
 *
 * Given an array of integers arr and two integers k and threshold, return the
 * number of sub-arrays of size k and average greater than or equal to
 * threshold.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
 * Output: 3
 * Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6
 * respectively. All other sub-arrays of size 3 have averages less than 4 (the
 * threshold).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
 * Output: 6
 * Explanation: The first 6 sub-arrays of size 3 have averages greater than 5.
 * Note that averages are not integers.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^4
 * 1 <= k <= arr.length
 * 0 <= threshold <= 10^4
 * 
 * 
 */

#include <vector>
#include <iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        if (threshold == 0) return arr.size() - k + 1;
        int sum = 0, res = 0;
        if (arr.size() == k) {
            for (int i = 0; i < arr.size(); i++) {
                sum += arr[i];
            }

            return sum >= threshold * k ? 1 : 0;
        }

        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];

            if (i < k - 1) {
                continue;
            }

            if (sum >= threshold * k) {
                res++;
            }
            
            sum -= arr[i - k + 1];
        }

        return res;
    }
};
// @lc code=end

