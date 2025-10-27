/*
 * @lc app=leetcode id=1552 lang=cpp
 *
 * [1552] Magnetic Force Between Two Balls
 *
 * https://leetcode.com/problems/magnetic-force-between-two-balls/description/
 *
 * algorithms
 * Medium (71.44%)
 * Likes:    3085
 * Dislikes: 265
 * Total Accepted:    197.9K
 * Total Submissions: 276.7K
 * Testcase Example:  '[1,2,3,4,7]\n3'
 *
 * In the universe Earth C-137, Rick discovered a special form of magnetic
 * force between two balls if they are put in his new invented basket. Rick has
 * n empty baskets, the i^th basket is at position[i], Morty has m balls and
 * needs to distribute the balls into the baskets such that the minimum
 * magnetic force between any two balls is maximum.
 * 
 * Rick stated that magnetic force between two different balls at positions x
 * and y is |x - y|.
 * 
 * Given the integer array position and the integer m. Return the required
 * force.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: position = [1,2,3,4,7], m = 3
 * Output: 3
 * Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the
 * magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is
 * 3. We cannot achieve a larger minimum magnetic force than 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: position = [5,4,3,2,1,1000000000], m = 2
 * Output: 999999999
 * Explanation: We can use baskets 1 and 1000000000.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == position.length
 * 2 <= n <= 10^5
 * 1 <= position[i] <= 10^9
 * All integers in position are distinct.
 * 2 <= m <= position.length
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        ranges::sort(position);
        auto check = [&](int target) -> bool {
            int cnt = 1, pre = position[0];
            for (int x : position) {
                if (x - pre >= target) {
                    cnt++;
                    pre = x;
                }
                if (cnt >= m) {
                    return true;
                }
            }
            return false;
        };

        int L = 0;
        int R = (position.back() - position[0]) / (m - 1) + 1;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(mid) ? L : R) = mid;
        }
        return L;
    }
};
// @lc code=end

