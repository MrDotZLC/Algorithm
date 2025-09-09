/*
 * @lc app=leetcode id=1376 lang=cpp
 *
 * [1376] Time Needed to Inform All Employees
 *
 * https://leetcode.com/problems/time-needed-to-inform-all-employees/description/
 *
 * algorithms
 * Medium (60.28%)
 * Likes:    4208
 * Dislikes: 318
 * Total Accepted:    247.7K
 * Total Submissions: 410.6K
 * Testcase Example:  '1\n0\n[-1]\n[0]'
 *
 * A company has n employees with a unique ID for each employee from 0 to n -
 * 1. The head of the company is the one with headID.
 * 
 * Each employee has one direct manager given in the manager array where
 * manager[i] is the direct manager of the i-th employee, manager[headID] = -1.
 * Also, it is guaranteed that the subordination relationships have a tree
 * structure.
 * 
 * The head of the company wants to inform all the company employees of an
 * urgent piece of news. He will inform his direct subordinates, and they will
 * inform their subordinates, and so on until all employees know about the
 * urgent news.
 * 
 * The i-th employee needs informTime[i] minutes to inform all of his direct
 * subordinates (i.e., After informTime[i] minutes, all his direct subordinates
 * can start spreading the news).
 * 
 * Return the number of minutes needed to inform all the employees about the
 * urgent news.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1, headID = 0, manager = [-1], informTime = [0]
 * Output: 0
 * Explanation: The head of the company is the only employee in the company.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime =
 * [0,0,1,0,0,0]
 * Output: 1
 * Explanation: The head of the company with id = 2 is the direct manager of
 * all the employees in the company and needs 1 minute to inform them all.
 * The tree structure of the employees in the company is shown.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * 0 <= headID < n
 * manager.length == n
 * 0 <= manager[i] < n
 * manager[headID] == -1
 * informTime.length == n
 * 0 <= informTime[i] <= 1000
 * informTime[i] == 0 if employee i has no subordinates.
 * It is guaranteed that all the employees can be informed.
 * 
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    // The sum of path of genaral tree
    // build tree and dfs
    int numOfMinutes1(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            if (manager[i] >= 0) {
                g[manager[i]].push_back(i);
            }
        }

        auto dfs = [&](auto &dfs, int x) -> int {
            int sum = 0;
            for (int c : g[x]) {
                sum = max(sum, dfs(dfs, c));
            }
            return sum + informTime[x];
        };

        return dfs(dfs, headID);
    }

    // build tree and dfs
    int numOfMinutes2(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            if (manager[i] >= 0) {
                g[manager[i]].push_back(i);
            }
        }
        int ans = 0;
        auto dfs = [&](auto &dfs, int x, int sum) -> void {
            sum = sum + informTime[x];
            ans = max(ans, sum);
            for (int c : g[x]) {
                dfs(dfs, c, sum);
            }
        };

        dfs(dfs, headID, 0);
        return ans;
    }

    // memory
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        auto dfs = [&](auto &dfs, int x) -> int {
            if (manager[x] >= 0) {
                informTime[x] += dfs(dfs, manager[x]);
                manager[x] = -1;
            }
            return informTime[x];
        };

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(dfs, i));
        }
        return ans;
    }
};
// @lc code=end

