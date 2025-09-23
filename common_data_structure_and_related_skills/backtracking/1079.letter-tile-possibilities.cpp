/*
 * @lc app=leetcode id=1079 lang=cpp
 *
 * [1079] Letter Tile Possibilities
 *
 * https://leetcode.com/problems/letter-tile-possibilities/description/
 *
 * algorithms
 * Medium (83.57%)
 * Likes:    3117
 * Dislikes: 88
 * Total Accepted:    246.6K
 * Total Submissions: 295.2K
 * Testcase Example:  '"AAB"'
 *
 * You have n  tiles, where each tile has one letter tiles[i] printed on it.
 * 
 * Return the number of possible non-empty sequences of letters you can make
 * using the letters printed on those tiles.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: tiles = "AAB"
 * Output: 8
 * Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
 * "ABA", "BAA".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: tiles = "AAABBC"
 * Output: 188
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: tiles = "V"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= tiles.length <= 7
 * tiles consists of uppercase English letters.
 * 
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <functional>
using namespace std;
// @lc code=start
class Solution {
public:
    int numTilePossibilities(string tiles) {
        ranges::sort(tiles.begin(), tiles.end());
        int n = tiles.length();
        int ans = 0;
        vector<int> on_path(n);

        function<void()> dfs = [&]() -> void {
            for (int j = 0; j < n; j++) {
                if (on_path[j] || j > 0 && tiles[j] == tiles[j - 1] && !on_path[j - 1]) {
                    continue;
                }
                ans++;
                on_path[j] = 1;
                dfs();
                on_path[j] = 0;
            }
        };
        dfs();
        return ans;
    }
};
// @lc code=end

