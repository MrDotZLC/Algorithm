/*
 * @lc app=leetcode id=1986 lang=cpp
 *
 * [1986] Minimum Number of Work Sessions to Finish the Tasks
 *
 * https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/description/
 *
 * algorithms
 * Medium (33.84%)
 * Likes:    1178
 * Dislikes: 70
 * Total Accepted:    32.8K
 * Total Submissions: 95.8K
 * Testcase Example:  '[1,2,3]\n3'
 *
 * There are n tasks assigned to you. The task times are represented as an
 * integer array tasks of length n, where the i^th task takes tasks[i] hours to
 * finish. A work session is when you work for at most sessionTime consecutive
 * hours and then take a break.
 * 
 * You should finish the given tasks in a way that satisfies the following
 * conditions:
 * 
 * 
 * If you start a task in a work session, you must complete it in the same work
 * session.
 * You can start a new task immediately after finishing the previous one.
 * You may complete the tasks in any order.
 * 
 * 
 * Given tasks and sessionTime, return the minimum number of work sessions
 * needed to finish all the tasks following the conditions above.
 * 
 * The tests are generated such that sessionTime is greater than or equal to
 * the maximum element in tasks[i].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: tasks = [1,2,3], sessionTime = 3
 * Output: 2
 * Explanation: You can finish the tasks in two work sessions.
 * - First work session: finish the first and the second tasks in 1 + 2 = 3
 * hours.
 * - Second work session: finish the third task in 3 hours.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: tasks = [3,1,3,1,1], sessionTime = 8
 * Output: 2
 * Explanation: You can finish the tasks in two work sessions.
 * - First work session: finish all the tasks except the last one in 3 + 1 + 3
 * + 1 = 8 hours.
 * - Second work session: finish the last task in 1 hour.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: tasks = [1,2,3,4,5], sessionTime = 15
 * Output: 1
 * Explanation: You can finish all the tasks in one work session.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == tasks.length
 * 1 <= n <= 14
 * 1 <= tasks[i] <= 10
 * max(tasks[i]) <= sessionTime <= 15
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * @brief 
 * 子集型状压DP
 * 用mask表示任务完成情况，mask∈[0,(1<<n)-1]
 * f(i)表示任务下标集合为i时的最小工作时间段
 * 枚举每个情况i的任务子集j，如果j的所有任务耗时小于sessionTime，
 * 则f(i)=f(i^j)+1
 * 边界：i=0,f=0;
 * 入口：f((1<<n)-1)
 */
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size(), m = 1 << n;
        vector<int> sum(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    sum[i] += tasks[j];
                }
            }
        }

        vector<int> f(m, n);
        f[0] = 0;
        for (int i = 1; i < m; i++) {
            for (int j = i; j; j = (j - 1) & i) {
                if (sum[j] <= sessionTime) {
                    f[i] = min(f[i], f[i ^ j] + 1);
                }
            }
        }
        return f.back();
    }
};
// @lc code=end

