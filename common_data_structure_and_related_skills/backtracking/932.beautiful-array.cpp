/*
 * @lc app=leetcode id=932 lang=cpp
 *
 * [932] Beautiful Array
 *
 * https://leetcode.com/problems/beautiful-array/description/
 *
 * algorithms
 * Medium (67.17%)
 * Likes:    1127
 * Dislikes: 1561
 * Total Accepted:    52.6K
 * Total Submissions: 78.1K
 * Testcase Example:  '4'
 *
 * An array nums of length n is beautiful if:
 * 
 * 
 * nums is a permutation of the integers in the range [1, n].
 * For every 0 <= i < j < n, there is no index k with i < k < j where 2 *
 * nums[k] == nums[i] + nums[j].
 * 
 * 
 * Given the integer n, return any beautiful array nums of length n. There will
 * be at least one valid answer for the given n.
 * 
 * 
 * Example 1:
 * Input: n = 4
 * Output: [2,1,4,3]
 * Example 2:
 * Input: n = 5
 * Output: [3,1,2,5,4]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 1000
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> beautifulArray(int n) {
        vector<int> ans;
        if (n == 1) {
            ans.push_back(1);
            return ans;
        } 

        int odd_num = (n + 1) / 2;
        int even_num = n / 2;
        vector<int> left = beautifulArray(odd_num);
        vector<int> right = beautifulArray(even_num);
        for (int x : left) {
            ans.push_back(x * 2 - 1);
        }
        for (int x : right) {
            ans.push_back(x * 2);
        }
        return ans;
    }
};
// @lc code=end

