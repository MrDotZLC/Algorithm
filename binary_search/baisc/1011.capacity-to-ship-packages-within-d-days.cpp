/*
 * @lc app=leetcode id=1011 lang=cpp
 *
 * [1011] Capacity To Ship Packages Within D Days
 *
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/
 *
 * algorithms
 * Medium (72.42%)
 * Likes:    10427
 * Dislikes: 268
 * Total Accepted:    610.6K
 * Total Submissions: 841.7K
 * Testcase Example:  '[1,2,3,4,5,6,7,8,9,10]\n5'
 *
 * A conveyor belt has packages that must be shipped from one port to another
 * within days days.
 * 
 * The i^th package on the conveyor belt has a weight of weights[i]. Each day,
 * we load the ship with packages on the conveyor belt (in the order given by
 * weights). We may not load more weight than the maximum weight capacity of
 * the ship.
 * 
 * Return the least weight capacity of the ship that will result in all the
 * packages on the conveyor belt being shipped within days days.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
 * Output: 15
 * Explanation: A ship capacity of 15 is the minimum to ship all the packages
 * in 5 days like this:
 * 1st day: 1, 2, 3, 4, 5
 * 2nd day: 6, 7
 * 3rd day: 8
 * 4th day: 9
 * 5th day: 10
 * 
 * Note that the cargo must be shipped in the order given, so using a ship of
 * capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6,
 * 7), (8), (9), (10) is not allowed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: weights = [3,2,2,4,1,4], days = 3
 * Output: 6
 * Explanation: A ship capacity of 6 is the minimum to ship all the packages in
 * 3 days like this:
 * 1st day: 3, 2
 * 2nd day: 2, 4
 * 3rd day: 1, 4
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: weights = [1,2,3,1,1], days = 4
 * Output: 3
 * Explanation:
 * 1st day: 1
 * 2nd day: 2
 * 3rd day: 3
 * 4th day: 1, 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= days <= weights.length <= 5 * 10^4
 * 1 <= weights[i] <= 500
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// @lc code=start
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        auto check = [&](int mid) -> bool {
            int sum = 0, count = days;
            for (int i : weights) {
                sum += i;
                if (sum > mid) {
                    count--;
                    sum = i;
                }
                if (count <= 0) {
                    return true;
                }
            }
            return false;
        };

        int L = 0, R = 0;
        for (int i : weights) {
            L = max(L, i);
            R += i;
        }

        while (L < R) { // [ , )
            int mid = L + (R - L) / 2;
            if (check(mid)) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        return R;
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
    sol.shipWithinDays(weights, 5);
}