/*
 * @lc app=leetcode id=375 lang=cpp
 *
 * [375] Guess Number Higher or Lower II
 *
 * https://leetcode.com/problems/guess-number-higher-or-lower-ii/description/
 *
 * algorithms
 * Medium (51.34%)
 * Likes:    2300
 * Dislikes: 2160
 * Total Accepted:    152.6K
 * Total Submissions: 293.7K
 * Testcase Example:  '10'
 *
 * We are playing the Guessing Game. The game will work as follows:
 * 
 * 
 * I pick a number between 1 and n.
 * You guess a number.
 * If you guess the right number, you win the game.
 * If you guess the wrong number, then I will tell you whether the number I
 * picked is higher or lower, and you will continue guessing.
 * Every time you guess a wrong number x, you will pay x dollars. If you run
 * out of money, you lose the game.
 * 
 * 
 * Given a particular n, return the minimum amount of money you need to
 * guarantee a win regardless of what number I pick.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 10
 * Output: 16
 * Explanation: The winning strategy is as follows:
 * - The range is [1,10]. Guess 7.
 * - If this is my number, your total is $0. Otherwise, you pay $7.
 * - If my number is higher, the range is [8,10]. Guess 9.
 * - If this is my number, your total is $7. Otherwise, you pay $9.
 * - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 =
 * $16.
 * - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9 =
 * $16.
 * - If my number is lower, the range is [1,6]. Guess 3.
 * - If this is my number, your total is $7. Otherwise, you pay $3.
 * - If my number is higher, the range is [4,6]. Guess 5.
 * - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay
 * $5.
 * - If my number is higher, it must be 6. Guess 6. Your total is $7 + $3 + $5
 * = $15.
 * - If my number is lower, it must be 4. Guess 4. Your total is $7 + $3 + $5 =
 * $15.
 * - If my number is lower, the range is [1,2]. Guess 1.
 * - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay
 * $1.
 * - If my number is higher, it must be 2. Guess 2. Your total is $7 + $3 + $1
 * = $11.
 * The worst case in all these scenarios is that you pay $16. Hence, you only
 * need $16 to guarantee a win.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 0
 * Explanation: There is only one possible number, so you can guess 1 and not
 * have to pay anything.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 2
 * Output: 1
 * Explanation: There are two possible numbers, 1 and 2.
 * - Guess 1.
 * - If this is my number, your total is $0. Otherwise, you pay $1.
 * - If my number is higher, it must be 2. Guess 2. Your total is $1.
 * The worst case is that you pay $1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 200
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 方法一：记忆化搜索/DP
 * 看似求最小代价，实则是最小最大代价
 * f(i,j)表示[i,j]区间内猜测所有结果的最小代价
 * f(i,j)=min{i+f(i+1,j), max{f(i,k-1),f(k+1,j)}+k, f(i,j-1)+j}, k∈(i,j)
 * 边界：i==j时，只有一个数字，一定能猜中，代价为0
 *      i>=j ，f(i,j)=0
 * 入口：f(1,n)
 * 
 * 方法二：单调栈
 * 自底向上构建树，遍历叶子节点，三个相邻的叶子节点，一定是最小与次小先求代价
 * 用单调栈可实现上述功能，栈顶最小，
 * 节点入栈前，先计算栈顶2个元素和当前节点值，优先计算最小与次小节点的代价，依次弹出，直到当前元素为栈顶
 * 此时，根的左子节点就是最大值节点，依次计算栈顶两个最小节点的代价并逐个弹出，真没元素小于2，则树构建完成
 */
class Solution {
public:
    // 记忆化搜索
    int getMoneyAmount1(int n) {
        vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i >= j) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = INT_MAX;
            for (int k = i; k <= j; k++) {
                res = min(res, max(dfs(dfs, i, k - 1), dfs(dfs, k + 1, j)) + k);
            }
            return res;
        };
        return dfs(dfs, 1, n);
    }

    // DP
    int getMoneyAmount(int n) {
        vector<vector<int>> f(n + 2, vector<int>(n + 2));
        for (int i = n; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                f[i][j] = INT_MAX;
                for (int k = i; k <= j; k++) {
                    f[i][j] = min(f[i][j], max(f[i][k - 1], f[k + 1][j]) + k);
                }
            }
        }
        return f[1][n];
    }

};
// @lc code=end

