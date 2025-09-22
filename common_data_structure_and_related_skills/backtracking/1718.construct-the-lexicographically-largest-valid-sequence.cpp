/*
 * @lc app=leetcode id=1718 lang=cpp
 *
 * [1718] Construct the Lexicographically Largest Valid Sequence
 *
 * https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/description/
 *
 * algorithms
 * Medium (73.00%)
 * Likes:    1147
 * Dislikes: 178
 * Total Accepted:    111.2K
 * Total Submissions: 152.4K
 * Testcase Example:  '3'
 *
 * Given an integer n, find a sequence with elements in the range [1, n] that
 * satisfies all of the following:
 * 
 * 
 * The integer 1 occurs once in the sequence.
 * Each integer between 2 and n occurs twice in the sequence.
 * For every integer i between 2 and n, the distance between the two
 * occurrences of i is exactly i.
 * 
 * 
 * The distance between two numbers on the sequence, a[i] and a[j], is the
 * absolute difference of their indices, |j - i|.
 * 
 * Return the lexicographically largest sequence. It is guaranteed that under
 * the given constraints, there is always a solution. 
 * 
 * A sequence a is lexicographically larger than a sequence b (of the same
 * length) if in the first position where a and b differ, sequence a has a
 * number greater than the corresponding number in b. For example, [0,1,9,0] is
 * lexicographically larger than [0,1,5,6] because the first position they
 * differ is at the third number, and 9 is greater than 5.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3
 * Output: [3,1,2,3,2]
 * Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the
 * lexicographically largest valid sequence.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 5
 * Output: [5,3,1,4,3,5,2,4,2]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 20
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // TLE
    vector<int> constructDistancedSequence1(int n) {
        n = 2 * n - 1;
        
        vector<int> ans(n, 0), path(n, 0), on_path(n, 0);
        auto dfs = [&](auto &dfs, int i) -> void {
            if (i == n) {
                ans = max(ans, path);
                return;
            }

            for (int j = 0; j < n; j++) {
                if (!on_path[j]) {
                    int value = j == 0 ? 1 : (j - 1) / 2 + 2; // mapping idx to value, val = (idx - 1) / 2 + 2
                    auto it = ranges::find(path, value);
                    if (it != path.end() && i - (it - path.begin()) != value) {
                        continue;
                    }
                    path[i] = value;
                    on_path[j] = 1;
                    dfs(dfs, i + 1);
                    path[i] = 0;
                    on_path[j] = 0; // 恢复现场
                }
            }
        };
        dfs(dfs, 0);
        return ans;
    }

    vector<int> constructDistancedSequence(int n) {
        int m = 2 * n - 1;
        
        vector<int> ans(m, 0), on_path(n + 1, 0);
        auto dfs = [&](auto &dfs, int i) -> bool {
            while (i < m && ans[i]) {
                i++;
            }
            if (i == m) {
                return true;
            }

            for (int j = n; j > 0; j--) {
                if (!on_path[j]) {
                    int second_pos = j == 1 ? i : i + j;

                    if (second_pos < m && ans[i] == 0 && ans[second_pos] == 0) {
                        ans[i] = j;
                        ans[second_pos] = j;
                        on_path[j] = 1;
                        if (dfs(dfs, i + 1)) {
                            return true;
                        }
                        on_path[j] = 0;
                        ans[second_pos] = 0;
                        ans[i] = 0;
                    }
                }
            }
            return false;
        };
        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end
