/*
 * @lc app=leetcode id=3177 lang=cpp
 *
 * [3177] Find the Maximum Length of a Good Subsequence II
 *
 * https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/description/
 *
 * algorithms
 * Hard (24.06%)
 * Likes:    136
 * Dislikes: 10
 * Total Accepted:    8.9K
 * Total Submissions: 36.6K
 * Testcase Example:  '[1,2,1,1,3]\n2'
 *
 * You are given an integer array nums and a non-negative integer k. A sequence
 * of integers seq is called good if there are at most k indices i in the range
 * [0, seq.length - 2] such that seq[i] != seq[i + 1].
 * 
 * Return the maximum possible length of a good subsequence of nums.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,1,1,3], k = 2
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * The maximum length subsequence is [1,2,1,1,3].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4,5,1], k = 0
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * The maximum length subsequence is [1,2,3,4,5,1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^3
 * 1 <= nums[i] <= 10^9
 * 0 <= k <= min(50, nums.length)
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
    int maximumLength(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> fs;
        vector<array<int, 3>> records(k + 1);
        for (int x : nums) {
            auto &f = fs[x];
            f.resize(k + 1);
            for (int j = k; j >= 0; j--) {
                f[j]++;
                if (j) {
                    auto &r = records[j - 1];
                    int mx = r[0], mx2 = r[1], num = r[2];
                    f[j] = max(f[j], (x != num ? mx : mx2) + 1);           
                }
                int v = f[j];
                auto &p = records[j];
                if (v > p[0]) {
                    if (x != p[2]) {
                        p[2] = x;
                        p[1] = p[0];
                    }
                    p[0] = v;
                } else if (x != p[2] && v > p[1]) {
                    p[1] = v;
                }
            }
        }
        return records[k][0];
    }
};
// @lc code=end

