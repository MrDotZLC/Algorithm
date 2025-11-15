/*
 * @lc app=leetcode id=3040 lang=cpp
 *
 * [3040] Maximum Number of Operations With the Same Score II
 *
 * https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/description/
 *
 * algorithms
 * Medium (33.19%)
 * Likes:    180
 * Dislikes: 16
 * Total Accepted:    24.2K
 * Total Submissions: 72K
 * Testcase Example:  '[3,2,1,2,3,4]'
 *
 * Given an array of integers called nums, you can perform any of the following
 * operation while nums contains at least 2 elements:
 * 
 * 
 * Choose the first two elements of nums and delete them.
 * Choose the last two elements of nums and delete them.
 * Choose the first and the last elements of nums and delete them.
 * 
 * 
 * The score of the operation is the sum of the deleted elements.
 * 
 * Your task is to find the maximum number of operations that can be performed,
 * such that all operations have the same score.
 * 
 * Return the maximum number of operations possible that satisfy the condition
 * mentioned above.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,2,1,2,3,4]
 * Output: 3
 * Explanation: We perform the following operations:
 * - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
 * - Delete the first and the last elements, with score 1 + 4 = 5, nums =
 * [2,3].
 * - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
 * We are unable to perform any more operations as nums is empty.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,2,6,1,4]
 * Output: 2
 * Explanation: We perform the following operations:
 * - Delete the first two elements, with score 3 + 2 = 5, nums = [6,1,4].
 * - Delete the last two elements, with score 1 + 4 = 5, nums = [6].
 * It can be proven that we can perform at most 2 operations.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 2000
 * 1 <= nums[i] <= 1000
 * 
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * f(i,j)表示区间[i,j]内满足条件的操作次数
 * f(i,j)=max{f(i+2,j), f(i+1,j-1),f(i,j-2)}, 移除的两个数的和等于固定值
 * 固定值由第一次移除的两个数决定
 * 结果等于max{f(2,n-1), f(1, n-2), f(0, n-3)}
 * 边界：i>=j,f=0
 * 入口：f(2,n-1), f(1, n-2), f(0, n-3)
 */
class Solution {
public:
    // 记忆化递归
    int maxOperations1(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        bool ok = false;
        auto dfs = [&](this auto &&dfs, int i, int j,
                       int target) -> int {
            if (ok || i >= j) {
                ok = true;
                return 0;
            }
            int &res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            if (nums[i] + nums[i + 1] == target) {
                res = max(res, dfs(i + 2, j, target) + 1);
            }
            if (nums[i] + nums[j] == target) {
                res = max(res, dfs(i + 1, j - 1, target) + 1);
            }
            if (nums[j - 1] + nums[j] == target) {
                res = max(res, dfs(i, j - 2, target) + 1);
            }
            return res;
        };
        return max({dfs(2, n - 1, nums[0] + nums[1]),
                    dfs(1, n - 2, nums[0] + nums[n - 1]),
                    dfs(0, n - 3, nums[n - 2] + nums[n - 1])}) + 1;
    }

    // DP
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        bool ok = false;
        auto helper = [&](this auto &&dfs, int start, int end,
                          int target) -> int {
            if (ok) {
                return n / 2;
            }
            vector<vector<int>> f(n + 1, vector<int>(n + 1));
            for (int i = end - 1 ; i >= start; i--) { // j=i+1 <= end --> i <= end - 1. 从end开始也可以。
                for (int j = i + 1; j <= end; j++) {
                    if (nums[i] + nums[i + 1] == target) {
                        f[i][j + 1] = max(f[i][j + 1], f[i + 2][j + 1] + 1);
                    }
                    if (nums[i] + nums[j] == target) {
                        f[i][j + 1] = max(f[i][j + 1], f[i + 1][j] + 1);
                    }
                    if (nums[j - 1] + nums[j] == target) {
                        f[i][j + 1] = max(f[i][j + 1], f[i][j - 1] + 1);
                    }
                    if (f[i][j] == n / 2) {
                        ok = true;
                        return n / 2;
                    }
                }
            }
            return f[start][end + 1] + 1;
        };
        int res1 = helper(2, n - 1, nums[0] + nums[1]);
        int res2 = helper(1, n - 2, nums[0] + nums[n - 1]);
        int res3 = helper(0, n - 3, nums[n - 2] + nums[n - 1]);
        return max({res1, res2, res3});
    }
};
// @lc code=end

