/*
 * @lc app=leetcode id=275 lang=cpp
 *
 * [275] H-Index II
 *
 * https://leetcode.com/problems/h-index-ii/description/
 *
 * algorithms
 * Medium (38.88%)
 * Likes:    467
 * Dislikes: 138
 * Total Accepted:    245.1K
 * Total Submissions: 629.7K
 * Testcase Example:  '[0,1,3,5,6]'
 *
 * Given an array of integers citations where citations[i] is the number of
 * citations a researcher received for their i^th paper and citations is sorted
 * in non-descending order, return the researcher's h-index.
 * 
 * According to the definition of h-index on Wikipedia: The h-index is defined
 * as the maximum value of h such that the given researcher has published at
 * least h papers that have each been cited at least h times.
 * 
 * You must write an algorithm that runs in logarithmic time.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: citations = [0,1,3,5,6]
 * Output: 3
 * Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each
 * of them had received 0, 1, 3, 5, 6 citations respectively.
 * Since the researcher has 3 papers with at least 3 citations each and the
 * remaining two with no more than 3 citations each, their h-index is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: citations = [1,2,100]
 * Output: 2
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == citations.length
 * 1 <= n <= 10^5
 * 0 <= citations[i] <= 1000
 * citations is sorted in ascending order.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int L = 1, R = n;
        while (L <= R) {
            int mid = L + (R - L) / 2;
            if (citations[n - mid] >= mid) {
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        return R; // L - 1 = R
    }

    int hIndex2(vector<int>& citations) {
        int n = citations.size();
        int L = 1, R = n + 1;
        while (L < R) {
            int mid = L + (R - L) / 2;
            if (citations[n - mid] >= mid) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        return R - 1; // L - 1 = R - 1 
    }

    int hIndex3(vector<int>& citations) {
        int n = citations.size();
        int L = 0, R = n;
        while (L < R) {
            int mid = L + (R - L) + 1 / 2; // 保证mid在区间内
            if (citations[n - mid] >= mid) {
                L = mid;
            } else {
                R = mid - 1;
            }
        }
        return L; // L = R
    }

    int hIndex4(vector<int>& citations) {
        int n = citations.size();
        int L = 0, R = n + 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2; // 保证mid在区间内
            if (citations[n - mid] >= mid) {
                L = mid;
            } else {
                R = mid;
            }
        }
        return R - 1; // L = R - 1
    }

};
// @lc code=end

