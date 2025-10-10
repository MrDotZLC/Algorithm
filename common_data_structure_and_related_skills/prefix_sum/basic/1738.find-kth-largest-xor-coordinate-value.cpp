/*
 * @lc app=leetcode id=1738 lang=cpp
 *
 * [1738] Find Kth Largest XOR Coordinate Value
 *
 * https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/description/
 *
 * algorithms
 * Medium (63.25%)
 * Likes:    532
 * Dislikes: 84
 * Total Accepted:    28.6K
 * Total Submissions: 44.9K
 * Testcase Example:  '[[5,2],[1,6]]\n1'
 *
 * You are given a 2D matrix of size m x n, consisting of non-negative
 * integers. You are also given an integer k.
 * 
 * The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j]
 * where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
 * 
 * Find the k^th largest value (1-indexed) of all the coordinates of matrix.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: matrix = [[5,2],[1,6]], k = 1
 * Output: 7
 * Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the
 * largest value.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: matrix = [[5,2],[1,6]], k = 2
 * Output: 5
 * Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd
 * largest value.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: matrix = [[5,2],[1,6]], k = 3
 * Output: 4
 * Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd
 * largest value.
 * 
 * 
 * Constraints:
 * 
 * 
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 1000
 * 0 <= matrix[i][j] <= 10^6
 * 1 <= k <= m * n
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> a;
        vector<vector<int>> s(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                s[i + 1][j + 1] = s[i + 1][j] ^ s[i][j + 1] ^ s[i][j] ^ matrix[i][j];
                // a.push_back(s[i + 1][j + 1]);
            }
            a.insert(a.end(), s[i + 1].begin() + 1, s[i + 1].end());
        }
        ranges::nth_element(a, a.end() - k);
        // sort(a.begin(), a.end(), greater<int>());
        // return a[k - 1]
        return a[a.size() - k];
    }
};
// @lc code=end

