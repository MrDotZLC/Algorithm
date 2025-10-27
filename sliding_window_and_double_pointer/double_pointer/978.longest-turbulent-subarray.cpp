/*
 * @lc app=leetcode id=978 lang=cpp
 *
 * [978] Longest Turbulent Subarray
 *
 * https://leetcode.com/problems/longest-turbulent-subarray/description/
 *
 * algorithms
 * Medium (48.14%)
 * Likes:    2065
 * Dislikes: 251
 * Total Accepted:    124.2K
 * Total Submissions: 257.7K
 * Testcase Example:  '[9,4,2,10,7,8,8,1,9]'
 *
 * Given an integer array arr, return the length of a maximum size turbulent
 * subarray of arr.
 * 
 * A subarray is turbulent if the comparison sign flips between each adjacent
 * pair of elements in the subarray.
 * 
 * More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said
 * to be turbulent if and only if:
 * 
 * 
 * For i <= k < j:
 * 
 * 
 * arr[k] > arr[k + 1] when k is odd, and
 * arr[k] < arr[k + 1] when k is even.
 * 
 * 
 * Or, for i <= k < j:
 * 
 * arr[k] > arr[k + 1] when k is even, and
 * arr[k] < arr[k + 1] when k is odd.
 * 
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [9,4,2,10,7,8,8,1,9]
 * Output: 5
 * Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [4,8,12,16]
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [100]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 4 * 10^4
 * 0 <= arr[i] <= 10^9
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
    int maxTurbulenceSize(vector<int>& arr) {
        int ans = 1, n = arr.size();
        if (n == 1) return ans;
        int i = 0, j = 1;
        bool flag = arr[j] > arr[i];
        while (j < n) {
            int diff = arr[j] - arr[j - 1];
            if (diff == 0) {
                ans = max(ans, j - i);
                i = j;
                if (j + 1 < n) {
                    flag = arr[j + 1] > arr[j];
                }
            } else if (diff > 0 == flag) {
                ans = max(ans, j - i + 1);
                flag = !flag;
                
            } else  if (diff > 0 != flag) {
                ans = max(ans, j - i);
                i = j - 1;
                // flag = diff > 0;
            }
            j++;
        }
        return ans;
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<int> arr = {0,8,45,88,48,68,28,55,17,24};
    sol.maxTurbulenceSize(arr);
}