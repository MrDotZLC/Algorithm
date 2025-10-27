/*
 * @lc app=leetcode id=1477 lang=cpp
 *
 * [1477] Find Two Non-overlapping Sub-arrays Each With Target Sum
 *
 * https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/description/
 *
 * algorithms
 * Medium (36.53%)
 * Likes:    1760
 * Dislikes: 90
 * Total Accepted:    53.3K
 * Total Submissions: 145.8K
 * Testcase Example:  '[3,2,2,4,3]\n3'
 *
 * You are given an array of integers arr and an integer target.
 * 
 * You have to find two non-overlapping sub-arrays of arr each with a sum equal
 * target. There can be multiple answers so you have to find an answer where
 * the sum of the lengths of the two sub-arrays is minimum.
 * 
 * Return the minimum sum of the lengths of the two required sub-arrays, or
 * return -1 if you cannot find such two sub-arrays.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [3,2,2,4,3], target = 3
 * Output: 2
 * Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of
 * their lengths is 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [7,3,4,7], target = 7
 * Output: 2
 * Explanation: Although we have three non-overlapping sub-arrays of sum = 7
 * ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as
 * the sum of their lengths is 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = [4,3,2,6,2,3,4], target = 6
 * Output: -1
 * Explanation: We have only one sub-array of sum = 6.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 1000
 * 1 <= target <= 10^8
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minSumOfLengths1(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = INT_MAX, sum = 0;
        unordered_map<int,int> pre;
        vector<tuple<int, int, int>> subs;  // {left, right, len}

        pre[0] = -1;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            if (pre.count(sum - target)) {
                int l = pre[sum - target] + 1;
                int r = i;
                subs.push_back({l, r, r - l + 1});
            }
            pre[sum] = i;
        }

        // 按右端点排序，方便扫描
        sort(subs.begin(), subs.end(), [](auto &a, auto &b){
            return get<1>(a) < get<1>(b);
        });

        // 扫描一次，维护到当前位置最短的子数组
        int m = subs.size();
        if (m == 0) return -1; // 没有任何满足条件的子数组

        vector<int> best(m, INT_MAX);
        best[0] = get<2>(subs[0]);
        for (int i = 1; i < m; i++) {
            best[i] = min(best[i-1], get<2>(subs[i]));
        }

        // 枚举第二个子数组，二分查找左边不重叠的最优
        for (int i = 0; i < m; i++) {
            // 找 r < subs[i][0]
            int l = 0, r = i-1, idx = -1;
            while (l <= r) {
                int mid = (l+r)/2;
                if (get<1>(subs[mid]) < get<0>(subs[i])) {
                    idx = mid;
                    l = mid+1;
                } else {
                    r = mid-1;
                }
            }
            if (idx != -1) {
                ans = min(ans, best[idx] + get<2>(subs[i]));
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }

    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        int ans = INT_MAX, sum = 0, min_len = INT_MAX;
        vector<int> best(n, INT_MAX);
        unordered_map<int, int> pre;
        pre[0] = -1;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            if (pre.contains(sum - target)) {
                int l = pre[sum - target] + 1;
                int len = i - pre[sum - target];
                if (l > 0 && best[l - 1] != INT_MAX) {
                    ans = min(ans, best[l - 1] + len);
                }
                min_len = min(min_len, len);
            }
            best[i] = min_len;
            pre[sum] = i;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
// @lc code=end

