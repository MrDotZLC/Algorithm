/*
 * @lc app=leetcode id=2071 lang=cpp
 *
 * [2071] Maximum Number of Tasks You Can Assign
 *
 * https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/description/
 *
 * algorithms
 * Hard (50.58%)
 * Likes:    1073
 * Dislikes: 57
 * Total Accepted:    84.2K
 * Total Submissions: 167.3K
 * Testcase Example:  '[3,2,1]\n[0,3,3]\n1\n1'
 *
 * You have n tasks and m workers. Each task has a strength requirement stored
 * in a 0-indexed integer array tasks, with the i^th task requiring tasks[i]
 * strength to complete. The strength of each worker is stored in a 0-indexed
 * integer array workers, with the j^th worker having workers[j] strength. Each
 * worker can only be assigned to a single task and must have a strength
 * greater than or equal to the task's strength requirement (i.e., workers[j]
 * >= tasks[i]).
 * 
 * Additionally, you have pills magical pills that will increase a worker's
 * strength by strength. You can decide which workers receive the magical
 * pills, however, you may only give each worker at most one magical pill.
 * 
 * Given the 0-indexed integer arrays tasks and workers and the integers pills
 * and strength, return the maximum number of tasks that can be completed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
 * Output: 3
 * Explanation:
 * We can assign the magical pill and tasks as follows:
 * - Give the magical pill to worker 0.
 * - Assign worker 0 to task 2 (0 + 1 >= 1)
 * - Assign worker 1 to task 1 (3 >= 2)
 * - Assign worker 2 to task 0 (3 >= 3)
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
 * Output: 1
 * Explanation:
 * We can assign the magical pill and tasks as follows:
 * - Give the magical pill to worker 0.
 * - Assign worker 0 to task 0 (0 + 5 >= 5)
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength =
 * 10
 * Output: 2
 * Explanation:
 * We can assign the magical pills and tasks as follows:
 * - Give the magical pill to worker 0 and worker 1.
 * - Assign worker 0 to task 0 (0 + 10 >= 10)
 * - Assign worker 1 to task 1 (10 + 10 >= 15)
 * The last pill is not given because it will not make any worker strong enough
 * for the last task.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == tasks.length
 * m == workers.length
 * 1 <= n, m <= 5 * 10^4
 * 0 <= pills <= m
 * 0 <= tasks[i], workers[j], strength <= 10^9
 * 
 * 
 */
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        ranges::sort(tasks);
        ranges::sort(workers);
        int m = workers.size();

        auto check = [&](int k) -> bool {
            int i = 0, p = pills; // i枚举tasks，j枚举workers
            deque<int> valid_tasks;
            for (int j = m - k; j < m; j++) {
                int w = workers[j];
                // 吃药能解决的所有任务
                while (i < k && tasks[i] <= w + strength) {
                    valid_tasks.push_back(tasks[i]);
                    i++;
                }

                // 吃药也解决不了任何问题
                if (valid_tasks.empty()) {
                    return false;
                }

                // 弹出不吃药就能解决的
                if (valid_tasks.front() <= w) {
                    valid_tasks.pop_front();
                    continue; // 解决最简单的，枚举下一个工人
                }

                // 嗑药
                if (p == 0) {
                    return false; // 没药了
                }

                p--;

                valid_tasks.pop_back(); // 嗑药解决最难的，利益最大化
            }
            
            return true;
        };

        int l = 0, r = min((int)tasks.size(), m) + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l; // 求最大返回l，l为求true的最大值，r为求false的最小值
    }
};
// @lc code=end

