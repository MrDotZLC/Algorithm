/*
 * @lc app=leetcode id=2791 lang=cpp
 *
 * [2791] Count Paths That Can Form a Palindrome in a Tree
 *
 * https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/description/
 *
 * algorithms
 * Hard (45.69%)
 * Likes:    426
 * Dislikes: 12
 * Total Accepted:    8.8K
 * Total Submissions: 19.1K
 * Testcase Example:  '[-1,0,0,1,1,2]\n"acaabc"'
 *
 * You are given a tree (i.e. a connected, undirected graph that has no cycles)
 * rooted at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is
 * represented by a 0-indexed array parent of size n, where parent[i] is the
 * parent of node i. Since node 0 is the root, parent[0] == -1.
 * 
 * You are also given a string s of length n, where s[i] is the character
 * assigned to the edge between i and parent[i]. s[0] can be ignored.
 * 
 * Return the number of pairs of nodes (u, v) such that u < v and the
 * characters assigned to edges on the path from u to v can be rearranged to
 * form a palindrome.
 * 
 * A string is a palindrome when it reads the same backwards as forwards.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: parent = [-1,0,0,1,1,2], s = "acaabc"
 * Output: 8
 * Explanation: The valid pairs are:
 * - All the pairs (0,1), (0,2), (1,3), (1,4) and (2,5) result in one character
 * which is always a palindrome.
 * - The pair (2,3) result in the string "aca" which is a palindrome.
 * - The pair (1,5) result in the string "cac" which is a palindrome.
 * - The pair (3,5) result in the string "acac" which can be rearranged into
 * the palindrome "acca".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: parent = [-1,0,0,0,0], s = "aaaaa"
 * Output: 10
 * Explanation: Any pair of nodes (u,v) where u < v is valid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == parent.length == s.length
 * 1 <= n <= 10^5
 * 0 <= parent[i] <= n - 1 for all i >= 1
 * parent[0] == -1
 * parent represents a valid tree.
 * s consists of only lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution {
public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p = parent[i];
            g[p].push_back(i);
        }

        long long ans = 0;
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        auto dfs = [&](auto &dfs, int x, int xor_sum) -> void {
            for (int y : g[x]) {
                int new_xor_sum = xor_sum ^ (1 << (s[y] - 'a'));
                ans += cnt.contains(new_xor_sum) ? cnt[new_xor_sum] : 0;
                for (int i = 0; i < 26; i++) {
                    ans += cnt.contains(new_xor_sum ^ (1 << i)) ? cnt[new_xor_sum ^ (1 << i)] : 0; 
                }
                cnt[new_xor_sum]++;
                dfs(dfs, y, new_xor_sum);
            }
        };
        dfs(dfs, 0, 0);
        return ans;
    }
};
// @lc code=end

