/*
 * @lc app=leetcode id=1218 lang=cpp
 *
 * [1218] Longest Arithmetic Subsequence of Given Difference
 *
 * https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/description/
 *
 * algorithms
 * Medium (54.42%)
 * Likes:    3354
 * Dislikes: 92
 * Total Accepted:    166.7K
 * Total Submissions: 306.6K
 * Testcase Example:  '[1,2,3,4]\n1'
 *
 * Given an integer array arr and an integer difference, return the length of
 * the longest subsequence in arr which is an arithmetic sequence such that the
 * difference between adjacent elements in the subsequence equals difference.
 * 
 * A subsequence is a sequence that can be derived from arr by deleting some or
 * no elements without changing the order of the remaining elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,3,4], difference = 1
 * Output: 4
 * Explanation: The longest arithmetic subsequence is [1,2,3,4].
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,3,5,7], difference = 1
 * Output: 1
 * Explanation: The longest arithmetic subsequence is any single element.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
 * Output: 4
 * Explanation: The longest arithmetic subsequence is [7,5,3,1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * -10^4 <= arr[i], difference <= 10^4
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // DP
    int longestSubsequence1(vector<int>& arr, int difference) {
        int n = arr.size();
        unordered_map<int, int> map;
        map[arr[0]] = 0;
        vector<array<int, 2>> f(n);
        f[0][1] = 1;
        for (int i = 1; i < n; i++) {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            f[i][1] = 1;
            int prev = arr[i] - difference;
            if (map.contains(prev)) {
                f[i][1] = max(f[i][1], f[map[prev]][1] + 1);
            }
            map[arr[i]] = i;
        }
        return max(f[n - 1][0], f[n - 1][1]);
    }

    // DP + 空间优化
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = 1, n = arr.size();
        unordered_map<int, int> map;
        for (int x : arr) {
            int prev = x - difference;
            map[x] = map[prev] + 1;
            ans = max(ans, map[x]);
        }
        return ans;
    }
};
// @lc code=end

