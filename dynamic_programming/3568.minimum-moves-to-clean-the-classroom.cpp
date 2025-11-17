/*
 * @lc app=leetcode id=3568 lang=cpp
 *
 * [3568] Minimum Moves to Clean the Classroom
 *
 * https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/description/
 *
 * algorithms
 * Medium (25.52%)
 * Likes:    122
 * Dislikes: 15
 * Total Accepted:    8.5K
 * Total Submissions: 32.7K
 * Testcase Example:  '["S.", "XL"]\n2'
 *
 * You are given an m x n grid classroom where a student volunteer is tasked
 * with cleaning up litter scattered around the room. Each cell in the grid is
 * one of the following:
 * 
 * 
 * 'S': Starting position of the student
 * 'L': Litter that must be collected (once collected, the cell becomes
 * empty)
 * 'R': Reset area that restores the student's energy to full capacity,
 * regardless of their current energy level (can be used multiple times)
 * 'X': Obstacle the student cannot pass through
 * '.': Empty space
 * 
 * 
 * You are also given an integer energy, representing the student's maximum
 * energy capacity. The student starts with this energy from the starting
 * position 'S'.
 * 
 * Each move to an adjacent cell (up, down, left, or right) costs 1 unit of
 * energy. If the energy reaches 0, the student can only continue if they are
 * on a reset area 'R', which resets the energy to its maximum capacity
 * energy.
 * 
 * Return the minimum number of moves required to collect all litter items, or
 * -1 if it's impossible.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: classroom = ["S.", "XL"], energy = 2
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * The student starts at cell (0, 0) with 2 units of energy.
 * Since cell (1, 0) contains an obstacle 'X', the student cannot move directly
 * downward.
 * A valid sequence of moves to collect all litter is as follows:
 * 
 * Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit
 * remaining.
 * Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
 * 
 * 
 * The student collects all the litter using 2 moves. Thus, the output is 2.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: classroom = ["LS", "RL"], energy = 4
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * The student starts at cell (0, 1) with 4 units of energy.
 * A valid sequence of moves to collect all litter is as follows:
 * 
 * Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of
 * energy used and 3 units remaining.
 * Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to
 * 4.
 * Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
 * 
 * 
 * The student collects all the litter using 3 moves. Thus, the output is 3.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: classroom = ["L.S", "RXL"], energy = 3
 * 
 * Output: -1
 * 
 * Explanation:
 * 
 * No valid path collects all 'L'.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m == classroom.length <= 20
 * 1 <= n == classroom[i].length <= 20
 * classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
 * 1 <= energy <= 50
 * There is exactly one 'S' in the grid.
 * There are at most 10 'L' cells in the grid.
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    static constexpr int dir[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    struct Node {
        int x, y, e, mask;
    };
    int minMoves1(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        // 将垃圾编号
        vector idx(m, vector<int>(n));
        int cnt_l = 0, sx = 0, sy = 0;
        for (int i = 0; i < m; i++) {
            auto &row = classroom[i];
            for (int j = 0; j < n; j++) {
                char ch = row[j];
                if (ch == 'L') {
                    idx[i][j] = 1 << cnt_l++;
                } else if (ch == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        // cnt_l代表垃圾数量
        int u = 1 << cnt_l;
        // 访问记录/状态转移f
        vector vis(m, vector(n, vector(energy + 1, vector<bool>(u))));
        // 起点
        vis[sx][sy][energy][0] = true;
        vector<Node> q = {{sx, sy, energy, 0}};

        for (int ans = 0; !q.empty(); ans++) {
            auto tmp = q;
            q.clear();
            for (auto &[x, y, e, mask] : tmp) {
                // 边界：所有垃圾被清除
                if (mask == u - 1) {
                    return ans;
                }
                // 没能量，趴窝了
                if (e == 0) {
                    continue;
                }
                // 遍历相邻教室
                for (auto &[dx, dy] : dir) {
                    int nx = x + dx, ny = y + dy;
                    // 当前教室可进入且，则进入该教室
                    if (0 <= nx && nx < m && 0 <= ny && ny < n &&
                        classroom[nx][ny] != 'X') {
                        // 判断是否恢复能量
                        int ne =
                            classroom[nx][ny] == 'R' ? energy : e - 1;
                        // 记录当前教室被清理，没有垃圾则不变
                        int nmask = mask | idx[nx][ny];
                        // 记录当前教室已被访问
                        if (!vis[nx][ny][ne][nmask]) {
                            vis[nx][ny][ne][nmask] = true;
                            q.emplace_back(nx, ny, ne, nmask);
                        }
                    }
                }
            }
        }
        return -1;
    }

    // 状压DP：优化：
    //vis改为max_energy，去掉e维度，相同x,y,mask只允许更高的e入栈
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        // 将垃圾编号
        vector idx(m, vector<int>(n));
        int cnt_l = 0, sx = 0, sy = 0;
        for (int i = 0; i < m; i++) {
            auto &row = classroom[i];
            for (int j = 0; j < n; j++) {
                char ch = row[j];
                if (ch == 'L') {
                    idx[i][j] = 1 << cnt_l++;
                } else if (ch == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        // cnt_l代表垃圾数量
        int u = 1 << cnt_l;
        // 访问记录/状态转移f
        vector max_energy(m, vector(n, vector<int>(u, -1)));
        // 起点
        max_energy[sx][sy][0] = energy;
        vector<Node> q = {{sx, sy, energy, 0}};

        for (int ans = 0; !q.empty(); ans++) {
            auto tmp = q;
            q.clear();
            for (auto &[x, y, e, mask] : tmp) {
                // 边界：所有垃圾被清除
                if (mask == u - 1) {
                    return ans;
                }
                // 没能量，趴窝了
                if (e == 0) {
                    continue;
                }
                // 遍历相邻教室
                for (auto &[dx, dy] : dir) {
                    int nx = x + dx, ny = y + dy;
                    // 当前教室可进入且，则进入该教室
                    if (0 <= nx && nx < m && 0 <= ny && ny < n &&
                        classroom[nx][ny] != 'X') {
                        // 判断是否恢复能量
                        int ne =
                            classroom[nx][ny] == 'R' ? energy : e - 1;
                        // 记录当前教室被清理，没有垃圾则不变
                        int nmask = mask | idx[nx][ny];
                        // 记录当前教室已被访问
                        if (ne > max_energy[nx][ny][nmask]) {
                            max_energy[nx][ny][nmask] = ne;
                            q.emplace_back(nx, ny, ne, nmask);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
// @lc code=end

