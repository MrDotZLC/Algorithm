/*
 * @lc app=leetcode id=3211 lang=cpp
 *
 * [3211] Generate Binary Strings Without Adjacent Zeros
 *
 * https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/description/
 *
 * algorithms
 * Medium (87.40%)
 * Likes:    249
 * Dislikes: 44
 * Total Accepted:    68.2K
 * Total Submissions: 77.7K
 * Testcase Example:  '3'
 *
 * You are given a positive integer n.
 * 
 * A binary string x is valid if all substrings of x of length 2 contain at
 * least one "1".
 * 
 * Return all valid strings with length n, in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3
 * 
 * Output: ["010","011","101","110","111"]
 * 
 * Explanation:
 * 
 * The valid strings of length 3 are: "010", "011", "101", "110", and "111".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * 
 * Output: ["0","1"]
 * 
 * Explanation:
 * 
 * The valid strings of length 1 are: "0" and "1".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 18
 * 
 * 
 */
#include <vector>
#include <string>
#include <bitset>
// #include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // backtracking
    vector<string> validStrings1(int n) {
        vector<string> ans;
        string path(n, 0);

        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }

            path[i] = '1';
            dfs(dfs, i + 1);

            if (i == 0 || path[i - 1] == '1') {
                path[i] = '0';
                dfs(dfs, i + 1);
            }
        };
        dfs(dfs, 0);
        return ans;
    }

    // bit
    vector<string> validStrings(int n) {
        vector<string> ans;
        int mask = (1 << n) - 1;
        for (int i = 0; i <= mask; i++) {
            if (((i >> 1) & i) == 0) {
                ans.push_back(bitset<18>(i ^ mask).to_string().substr(18 - n));
            }
        }
        return ans;
    }
};
// @lc code=end

