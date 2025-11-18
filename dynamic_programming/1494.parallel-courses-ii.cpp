/*
 * @lc app=leetcode id=1494 lang=cpp
 *
 * [1494] Parallel Courses II
 *
 * https://leetcode.com/problems/parallel-courses-ii/description/
 *
 * algorithms
 * Hard (29.52%)
 * Likes:    1116
 * Dislikes: 77
 * Total Accepted:    24.5K
 * Total Submissions: 81.6K
 * Testcase Example:  '4\n[[2,1],[3,1],[1,4]]\n2'
 *
 * You are given an integer n, which indicates that there are n courses labeled
 * from 1 to n. You are also given an array relations where relations[i] =
 * [prevCoursei, nextCoursei], representing a prerequisite relationship between
 * course prevCoursei and course nextCoursei: course prevCoursei has to be
 * taken before course nextCoursei. Also, you are given the integer k.
 * 
 * In one semester, you can take at most k courses as long as you have taken
 * all the prerequisites in the previous semesters for the courses you are
 * taking.
 * 
 * Return the minimum number of semesters needed to take all courses. The
 * testcases will be generated such that it is possible to take every
 * course.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
 * Output: 3
 * Explanation: The figure above represents the given graph.
 * In the first semester, you can take courses 2 and 3.
 * In the second semester, you can take course 1.
 * In the third semester, you can take course 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5, relations = [[2,1],[3,1],[4,1],[1,5]], k = 2
 * Output: 4
 * Explanation: The figure above represents the given graph.
 * In the first semester, you can only take courses 2 and 3 since you cannot
 * take more than two per semester.
 * In the second semester, you can take course 4.
 * In the third semester, you can take course 1.
 * In the fourth semester, you can take course 5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 15
 * 1 <= k <= n
 * 0 <= relations.length <= n * (n-1) / 2
 * relations[i].length == 2
 * 1 <= prevCoursei, nextCoursei <= n
 * prevCoursei != nextCoursei
 * All the pairs [prevCoursei, nextCoursei] are unique.
 * The given graph is a directed acyclic graph.
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * @brief
 * 子集型状压 DP
 * 考虑子集为 i 的课程安排最少学期数
 * 枚举所有课程安排集合 i ，检索所有课程 j 的前导课 pre(j) 是否属于 i 的补集
 * 若所有符合要求的课程 ii 不超过 k 节，最小学期数 = 其他课程所需学期数 + 1
 * 超过 k 节，则枚举 ii 的所有课数等于 k 的子集 sub，
 * j 的最小学期数 =  其他课程所需学期数 + 1
 * 
 *  f(i) 表示前 i 个课程最少学期数
 *  f(i) = f(i^ii)+1,               pre(i)∈U\i, popcount(ii)<=k
 *         min(f(i),f(i^sub)+1(),   pre(i)∈U\i, popcount(ii)> k, popcount(sub)=k
 * 边界：i=0, f=0
 * 入口：f((1<<n)-1), n为总课程数
 */
class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> pre(n);
        for (auto &r : relations) {
            pre[r[1] - 1] |= 1 << (r[0] - 1);
        }

        int u = 1 << n;
        vector<int> f(u);
        f[0] = 0;
        for (int i = 1; i < u; i++) {
            int ii = 0, ui = (u - 1) ^ i;
            for (int j = 0; j < n; j++) {
                if ((i >> j & 1) && (pre[j] | ui) == ui) {
                    ii |= 1 << j;
                }
            }
            if (popcount((unsigned) ii) <= k) {
                f[i] = f[i ^ ii] + 1;
                continue;
            }
            f[i] = INT_MAX;
            for (int sub = ii; sub; sub = (sub - 1) & ii) {
                if (popcount((unsigned) sub) == k) {
                    f[i] = min(f[i], f[i ^ sub] + 1);
                }
            }
        }
        return f[u - 1];
    }
};
// @lc code=end

