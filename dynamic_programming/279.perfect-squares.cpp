/*
 * @lc app=leetcode id=279 lang=cpp
 *
 * [279] Perfect Squares
 *
 * https://leetcode.com/problems/perfect-squares/description/
 *
 * algorithms
 * Medium (55.77%)
 * Likes:    11690
 * Dislikes: 488
 * Total Accepted:    1M
 * Total Submissions: 1.8M
 * Testcase Example:  '12'
 *
 * Given an integer n, return the least number of perfect square numbers that
 * sum to n.
 * 
 * A perfect square is an integer that is the square of an integer; in other
 * words, it is the product of some integer with itself. For example, 1, 4, 9,
 * and 16 are perfect squares while 3 and 11 are not.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^4
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
// @lc code=start
// 写在外面，多个测试数据之间可以共享，减少计算量
int memo[101][10001];

auto init1 = [] {
    memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
    return 0;
}();
// DP递归
int dfs(int i, int j) {
    if (i == 0) {
        return j == 0 ? 0 : INT_MAX;
    }
    int& res = memo[i][j]; // 注意这里是引用
    if (res != -1) { // 之前计算过
        return res;
    }
    if (j < i * i) {
        res = dfs(i - 1, j); // 只能不选
    } else {
        res = min(dfs(i - 1, j), dfs(i, j - i * i) + 1); // 不选 vs 选
    }
    return res;
}

const int N = 10000;
int f[N + 1];

// DP递推+空间优化
auto init = [] {
    ranges::fill(f, INT_MAX);
    f[0] = 0;
    for (int i = 1; i * i <= N; i++) {
        for (int j = i * i; j <= N; j++) {
            f[j] = min(f[j], f[j - i * i] + 1);
        }
    }
    return 0;
}();

class Solution {
public:
    int numSquares1(int n) {
        return dfs(sqrt(n), n);
    }

    int numSquares(int n) {
        return f[n];
    }
};
// @lc code=end

