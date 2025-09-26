/*
 * @lc app=leetcode id=1128 lang=cpp
 *
 * [1128] Number of Equivalent Domino Pairs
 *
 * https://leetcode.com/problems/number-of-equivalent-domino-pairs/description/
 *
 * algorithms
 * Easy (60.61%)
 * Likes:    1100
 * Dislikes: 374
 * Total Accepted:    196.4K
 * Total Submissions: 324.1K
 * Testcase Example:  '[[1,2],[2,1],[3,4],[5,6]]'
 *
 * Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j]
 * = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) -
 * that is, one domino can be rotated to be equal to another domino.
 * 
 * Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length,
 * and dominoes[i] is equivalent to dominoes[j].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= dominoes.length <= 4 * 10^4
 * dominoes[i].length == 2
 * 1 <= dominoes[i][j] <= 9
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
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int ans = 0;
        unordered_map<string, int> idx;
        for (int j = 0; j < dominoes.size(); j++) {
            auto [a, b] = minmax(dominoes[j][0], dominoes[j][1]);
            string key = to_string(a) + ',' + to_string(b);
            ans += idx[key]++;
        }
        return ans;
    }

    int numEquivDominoPairs1(vector<vector<int>>& dominoes) {
        int ans = 0;
        int idx[10][10] {};
        for (int j = 0; j < dominoes.size(); j++) {
            auto [a, b] = minmax(dominoes[j][0], dominoes[j][1]);
            ans += idx[a][b]++;
        }
        return ans;
    }
};
// @lc code=end

