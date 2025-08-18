/*
 * @lc app=leetcode id=786 lang=cpp
 *
 * [786] K-th Smallest Prime Fraction
 *
 * https://leetcode.com/problems/k-th-smallest-prime-fraction/description/
 *
 * algorithms
 * Medium (68.59%)
 * Likes:    2100
 * Dislikes: 121
 * Total Accepted:    163.7K
 * Total Submissions: 238.5K
 * Testcase Example:  '[1,2,3,5]\n3'
 *
 * You are given a sorted integer array arr containing 1 and prime numbers,
 * where all the integers of arr are unique. You are also given an integer k.
 * 
 * For every i and j where 0 <= i < j < arr.length, we consider the fraction
 * arr[i] / arr[j].
 * 
 * Return the k^th smallest fraction considered. Return your answer as an array
 * of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,3,5], k = 3
 * Output: [2,5]
 * Explanation: The fractions to be considered in sorted order are:
 * 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
 * The third fraction is 2/5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,7], k = 1
 * Output: [1,7]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= arr.length <= 1000
 * 1 <= arr[i] <= 3 * 10^4
 * arr[0] == 1
 * arr[i] is a prime number for i > 0.
 * All the numbers of arr are unique and sorted in strictly increasing
 * order.
 * 1 <= k <= arr.length * (arr.length - 1) / 2
 * 
 * 
 * 
 * Follow up: Can you solve the problem with better than O(n^2) complexity?
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        double eps = 1e-8;
        int a = 0, b = 0;
        auto check = [&](double x) -> bool {
            int cnt = 0;
            for (int i = 0, j = 1; j < arr.size(); j++) {
                while (arr[i + 1] * 1.0 / arr[j] <= x) i++;
                if (arr[i] * 1.0 / arr[j] <= x) {
                    cnt += i + 1;
                }
                if (abs(arr[i] * 1.0 / arr[j] - x) < eps) {
                    a = arr[i];
                    b = arr[j];
                }
            }
            return cnt < k;
        };
        double L = 0;
        double R = 1;
        while (L + eps < R) {
            double mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid; 
        }
        return {a, b};
    }
};
// @lc code=end

