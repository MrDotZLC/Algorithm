/*
 * @lc app=leetcode id=1094 lang=cpp
 *
 * [1094] Car Pooling
 *
 * https://leetcode.com/problems/car-pooling/description/
 *
 * algorithms
 * Medium (56.09%)
 * Likes:    4738
 * Dislikes: 116
 * Total Accepted:    290.5K
 * Total Submissions: 517.4K
 * Testcase Example:  '[[2,1,5],[3,3,7]]\n4'
 *
 * There is a car with capacity empty seats. The vehicle only drives east
 * (i.e., it cannot turn around and drive west).
 * 
 * You are given the integer capacity and an array trips where trips[i] =
 * [numPassengersi, fromi, toi] indicates that the i^th trip has numPassengersi
 * passengers and the locations to pick them up and drop them off are fromi and
 * toi respectively. The locations are given as the number of kilometers due
 * east from the car's initial location.
 * 
 * Return true if it is possible to pick up and drop off all passengers for all
 * the given trips, or false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 4
 * Output: false
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 5
 * Output: true
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= trips.length <= 1000
 * trips[i].length == 3
 * 1 <= numPassengersi <= 100
 * 0 <= fromi < toi <= 1000
 * 1 <= capacity <= 10^5
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
// @lc code=start
class Solution {
public:
    // 排序+优先队列
    bool carPooling1(vector<vector<int>>& trips, int capacity) {
        ranges::sort(trips, less{}, [](auto &t) {
            return t[1];
        });
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq;
        for (auto &t : trips) {
            int num   = t[0]; // 乘客数
            int from  = t[1]; // 出发站（包含）
            int to    = t[2]; // 到达站（不包含）
            // 先释放所有已到达（to <= from），把座位加回 capacity
            while (!pq.empty() && pq.top().first <= from) {
                capacity += pq.top().second;
                pq.pop();
            }

            if (capacity < num) {
                return false;
            }
            capacity -= num;
            pq.push({to, num});
        }
        return true;
    }

    // 差分
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // int d[1001]{};
        map<int, int> d;
        for (auto &t : trips) {
            int num   = t[0]; // 乘客数
            int from  = t[1]; // 出发站（包含）
            int to    = t[2]; // 到达站（不包含）
            d[from] += num;
            d[to] -= num;
        }

        int sum = 0;
        for (auto &[_, v] : d) {
            sum += v;
            if (sum > capacity) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

