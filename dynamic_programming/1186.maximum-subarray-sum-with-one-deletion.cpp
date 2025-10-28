/*
 * @lc app=leetcode id=1186 lang=cpp
 *
 * [1186] Maximum Subarray Sum with One Deletion
 *
 * https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/description/
 *
 * algorithms
 * Medium (45.28%)
 * Likes:    1963
 * Dislikes: 77
 * Total Accepted:    68.2K
 * Total Submissions: 149.1K
 * Testcase Example:  '[1,-2,0,3]'
 *
 * Given an array of integers, return the maximum sum for a non-empty subarray
 * (contiguous elements) with at most one element deletion. In other words, you
 * want to choose a subarray and optionally delete one element from it so that
 * there is still at least one element left and the sum of the remaining
 * elements is maximum possible.
 * 
 * Note that the subarray needs to be non-empty after deleting one element.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,-2,0,3]
 * Output: 4
 * Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the
 * subarray [1, 0, 3] becomes the maximum value.
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,-2,-2,3]
 * Output: 3
 * Explanation: We just choose [3] and it's the maximum sum.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [-1,-1,-1,-1]
 * Output: -1
 * Explanation: The final subarray needs to be non-empty. You can't choose [-1]
 * and delete -1 from it, then get an empty subarray to make the sum equals to
 * 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * -10^4 <= arr[i] <= 10^4
 * 
 * 
 */
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumSum1(vector<int>& arr) {
        int n = arr.size();
        vector<array<int, 2>> memo(n + 1, {INT_MIN, INT_MIN});

        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i < 0) {
                return INT_MIN / 2;
            }
            int &ans = memo[i][j];
            if (ans != INT_MIN) {
                return ans;
            }
            if (j == 0) {
                return ans = max(dfs(i - 1, 0), 0) + arr[i];
            }
            return ans = max(dfs(i - 1, 0), dfs(i - 1, 1) + arr[i]);
        };

        int ans = INT_MIN;
        for (int i = 0; i < n; i++) {
            ans = max(ans, max(dfs(i, 0), dfs(i, 1)));
        }
        return ans;
    }

    int maximumSum(vector<int>& arr) {
        int ans = INT_MIN / 2, f0 = ans, f1 = ans;
        for (int x : arr) {
            f1 = max(f0, f1 + x);
            f0 = max(f0, 0) + x;
            ans = max(ans, max(f0, f1));
        }
        return ans;
    }
};
// @lc code=end

