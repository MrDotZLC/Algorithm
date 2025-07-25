/*
 * @lc app=leetcode id=1695 lang=cpp
 *
 * [1695] Maximum Erasure Value
 *
 * https://leetcode.com/problems/maximum-erasure-value/description/
 *
 * algorithms
 * Medium (62.41%)
 * Likes:    3326
 * Dislikes: 64
 * Total Accepted:    270.2K
 * Total Submissions: 423.1K
 * Testcase Example:  '[4,2,4,5,6]'
 *
 * You are given an array of positive integers nums and want to erase a
 * subarray containing unique elements. The score you get by erasing the
 * subarray is equal to the sum of its elements.
 * 
 * Return the maximum score you can get by erasing exactly one subarray.
 * 
 * An array b is called to be a subarray of a if it forms a contiguous
 * subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some
 * (l,r).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,2,4,5,6]
 * Output: 17
 * Explanation: The optimal subarray here is [2,4,5,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,2,1,2,5,2,1,2,5]
 * Output: 8
 * Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <deque>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int res = 0, sum = 0, l = 0;
        unordered_set<int> freq(nums.size());
        for (int r = 0; r < nums.size(); r++) {
            sum += nums[r];
            while (freq.find(nums[r]) != freq.end()) {
                sum -= nums[l];
                freq.erase(nums[l]);
                l++;
            }
            freq.insert(nums[r]);
            res = max(res, sum);
        }
        return res;
    }

    /**
     * Advanced problem: 
     * How solve the problem that the elements of array are integers.
     * 
     * Calculate the prefix sum of the subscripts of element i and 
     * subtract the minimum array where the subscript i is at the 
     * right end.
     */
    int maximumUniqueSubarray2(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        // The subscript of the last occurrence of an element.
        unordered_map<int, int> last_index;
        // The left endpoint of the non-repeating minimum subarray
        vector<int> l(n, -1);
        for (int i = 0; i < n; i++) {
            int v = nums[i];
            int last = last_index.find(v) != last_index.end() ? 
                            last_index[v] : -1;
            l[i] = max(i > 0 ? l[i - 1] : -1, last);
            last_index[v] = i;
        }

        vector<int> prefix(nums.size() + 1);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // The minimum prefix sum of the elements
        deque<int> q;
        q.push_back(0);

        // Find the minimum prefix sum.
        for (int i = 0; i < n; i++) {
            int cur_sum = prefix[i + 1];
            // pop up the prefix sum that is greater than the current element.
            while (!q.empty() && cur_sum <= prefix[q.back()]) {
                q.pop_back();
            }
            // pop up the minimum prefix sum the is not within the limited range.
            while (!q.empty() && q.front() - 1 < l[i]) {
                q.pop_front();
            }
            // save current prefix index
            q.push_back(i + 1);
            // update res
            if (!q.empty()) {
                res = max(res, prefix[i + 1] - prefix[q.front()]);
            }
        }

        return res;
    }
};
// @lc code=end

