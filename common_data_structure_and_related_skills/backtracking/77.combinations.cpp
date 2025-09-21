/*
 * @lc app=leetcode id=77 lang=cpp
 *
 * [77] Combinations
 *
 * https://leetcode.com/problems/combinations/description/
 *
 * algorithms
 * Medium (73.11%)
 * Likes:    8722
 * Dislikes: 243
 * Total Accepted:    1.2M
 * Total Submissions: 1.6M
 * Testcase Example:  '4\n2'
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * chosen from the range [1, n].
 * 
 * You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1,2] and [2,1] are considered
 * to be the same combination.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1, k = 1
 * Output: [[1]]
 * Explanation: There is 1 choose 1 = 1 total combination.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 20
 * 1 <= k <= n
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;

        vector<int> combi;
        auto dfs = [&](auto &dfs, int pos) -> void {
            if (combi.size() == k) {
                ans.push_back(combi);
                return;
            }

            for (int i = pos; i <= n + 1 - (k - combi.size()); i++) {
                combi.push_back(i);
                dfs(dfs, i + 1);
                combi.pop_back();
            }
        };
        dfs(dfs, 1);
        return ans;
    }
};
// @lc code=end

