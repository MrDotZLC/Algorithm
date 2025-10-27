/*
 * @lc app=leetcode id=1089 lang=cpp
 *
 * [1089] Duplicate Zeros
 *
 * https://leetcode.com/problems/duplicate-zeros/description/
 *
 * algorithms
 * Easy (52.86%)
 * Likes:    2736
 * Dislikes: 773
 * Total Accepted:    505.1K
 * Total Submissions: 955.1K
 * Testcase Example:  '[1,0,2,3,0,4,5,0]'
 *
 * Given a fixed-length integer array arr, duplicate each occurrence of zero,
 * shifting the remaining elements to the right.
 * 
 * Note that elements beyond the length of the original array are not written.
 * Do the above modifications to the input array in place and do not return
 * anything.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,0,2,3,0,4,5,0]
 * Output: [1,0,0,2,3,0,0,4]
 * Explanation: After calling your function, the input array is modified to:
 * [1,0,0,2,3,0,0,4]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,2,3]
 * Output: [1,2,3]
 * Explanation: After calling your function, the input array is modified to:
 * [1,2,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 9
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
    void duplicateZeros(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        while (l < r){
            if (arr[l] == 0) {
                r--;
            }
            l++;
        }
        int i = arr.size() - 1;
        if (arr[r] == 0 && l == r) {
            arr[i--] = 0;
            r--;
        }
        while (i > 0 && r >= 0) {
            if (arr[r] == 0) {
                arr[i] = 0;
                arr[--i] = 0;
            } else {
                arr[i] = arr[r];
            }
            r--;
            i--;
        }
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<int> arr = {1,5,2,0,6,8,0,6,0};
    sol.duplicateZeros(arr);
}