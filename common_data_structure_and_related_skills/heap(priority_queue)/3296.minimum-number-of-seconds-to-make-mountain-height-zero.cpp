/*
 * @lc app=leetcode id=3296 lang=cpp
 *
 * [3296] Minimum Number of Seconds to Make Mountain Height Zero
 *
 * https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/
 *
 * algorithms
 * Medium (36.09%)
 * Likes:    228
 * Dislikes: 32
 * Total Accepted:    24.3K
 * Total Submissions: 66.8K
 * Testcase Example:  '4\n[2,1,1]'
 *
 * You are given an integer mountainHeight denoting the height of a mountain.
 * 
 * You are also given an integer array workerTimes representing the work time
 * of workers in seconds.
 * 
 * The workers work simultaneously to reduce the height of the mountain. For
 * worker i:
 * 
 * 
 * To decrease the mountain's height by x, it takes workerTimes[i] +
 * workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For
 * example:
 * 
 * 
 * To reduce the height of the mountain by 1, it takes workerTimes[i]
 * seconds.
 * To reduce the height of the mountain by 2, it takes workerTimes[i] +
 * workerTimes[i] * 2 seconds, and so on.
 * 
 * 
 * 
 * 
 * Return an integer representing the minimum number of seconds required for
 * the workers to make the height of the mountain 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mountainHeight = 4, workerTimes = [2,1,1]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * One way the height of the mountain can be reduced to 0 is:
 * 
 * 
 * Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
 * Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2
 * = 3 seconds.
 * Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
 * 
 * 
 * Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3
 * seconds.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mountainHeight = 10, workerTimes = [3,2,2,4]
 * 
 * Output: 12
 * 
 * Explanation:
 * 
 * 
 * Worker 0 reduces the height by 2, taking workerTimes[0] + workerTimes[0] * 2
 * = 9 seconds.
 * Worker 1 reduces the height by 3, taking workerTimes[1] + workerTimes[1] * 2
 * + workerTimes[1] * 3 = 12 seconds.
 * Worker 2 reduces the height by 3, taking workerTimes[2] + workerTimes[2] * 2
 * + workerTimes[2] * 3 = 12 seconds.
 * Worker 3 reduces the height by 2, taking workerTimes[3] + workerTimes[3] * 2
 * = 12 seconds.
 * 
 * 
 * The number of seconds needed is max(9, 12, 12, 12) = 12 seconds.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: mountainHeight = 5, workerTimes = [1]
 * 
 * Output: 15
 * 
 * Explanation:
 * 
 * There is only one worker in this example, so the answer is workerTimes[0] +
 * workerTimes[0] * 2 + workerTimes[0] * 3 + workerTimes[0] * 4 +
 * workerTimes[0] * 5 = 15.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= mountainHeight <= 10^5
 * 1 <= workerTimes.length <= 10^4
 * 1 <= workerTimes[i] <= 10^6
 * 
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
// @lc code=start
class Solution {
public:
    // 堆
    long long minNumberOfSeconds2(int mountainHeight,
                                 vector<int> &workerTimes) {
        priority_queue<tuple<long long, long long, int>,
                       vector<tuple<long long, long long, int>>,
                       greater<tuple<long long, long long, int>>>
            pq;
        for (int t : workerTimes) {
            pq.emplace(t, t, t);
        }

        long long ans = 0;
        while (mountainHeight--) {
            auto [nxt, cur, base] = pq.top();
            pq.pop();
            ans = nxt; // nxt总是越来越大的，可以同时开工，所以nxt就是总耗时
            pq.emplace(nxt + cur + base, cur + base, base);
        }
        return ans;
    }

    // 二分答案
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        auto check = [&](long long m) {
            int left_h = mountainHeight;
            for (int t : workerTimes) {
                left_h -= ((int) sqrt(m / t * 8 + 1) - 1) / 2; // 每个工人单干花费m秒能够降低的高度
                if (left_h <= 0) {
                    return false;
                }
            }
            return true;
        };
        
        int n = workerTimes.size();
        int h = (mountainHeight + n - 1) / n; // 取天花板，平均每人花费的时间
        auto [min_t, max_t] = std::minmax_element(workerTimes.begin(), workerTimes.end());
        long long L = (long long) *min_t * h * (h + 1) / 2 - 1; // 下界-最少耗时：最高效率每人的耗时
        long long R = (long long) *max_t * h * (h + 1) / 2 + 1; // 上界-最多耗时：最低效率每人的耗时
        while (L + 1 < R) {
            long long mid = L + (R - L) / 2;
            if (check(mid)) {
                L = mid;
            } else {
                R = mid;
            }
        }
        return R;
    }
};
// @lc code=end

