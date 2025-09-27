/*
 * @lc app=leetcode id=1534 lang=cpp
 *
 * [1534] Count Good Triplets
 *
 * https://leetcode.com/problems/count-good-triplets/description/
 *
 * algorithms
 * Easy (85.50%)
 * Likes:    1182
 * Dislikes: 1247
 * Total Accepted:    275.3K
 * Total Submissions: 321.9K
 * Testcase Example:  '[3,0,1,1,9,7]\n7\n2\n3'
 *
 * Given an array of integers arr, and three integers a, b and c. You need to
 * find the number of good triplets.
 * 
 * A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are
 * true:
 * 
 * 
 * 0 <= i < j < k < arr.length
 * |arr[i] - arr[j]| <= a
 * |arr[j] - arr[k]| <= b
 * |arr[i] - arr[k]| <= c
 * 
 * 
 * Where |x| denotes the absolute value of x.
 * 
 * Return the number of good triplets.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
 * Output: 4
 * Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1),
 * (0,1,1)].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
 * Output: 0
 * Explanation: No triplet satisfies all conditions.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= arr.length <= 100
 * 0 <= arr[i] <= 1000
 * 0 <= a, b, c <= 1000
 * 
 */
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // 中间遍历 + 栈 + 前缀和
    int countGoodTriplets1(vector<int>& arr, int a, int b, int c) {
        int n = arr.size(), mx = ranges::max(arr);
        vector<int> s(mx + 2);
        int ans = 0;
        for (int j = 0; j < n; j++) {
            int y = arr[j];
            for (int k = j + 1; k < n; k++) {
                int z = arr[k];
                if (abs(y - z) > b) {
                    continue;
                }
                int l = max({y - a, z - c, 0});
                int r = min({y + a, z + c, mx});
                ans += max(s[r + 1] - s[l], 0);
            }
            for (int v = y + 1; v < mx + 2; v++) {
                s[v]++;
            }
        }
        return ans;
    }

    // 三指针
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        // 根据值的大小，对下标进行排序，放入新数组，得到数值升序的数组
        vector<int> idx(arr.size());
        ranges::iota(idx, 0);
        ranges::sort(idx, {}, [&](int i) {
            return arr[i];
        });

        int ans = 0;
        // 遍历y，将左边满足条件的放入left，右边同理
        for (int j : idx) {
            int y = arr[j];
            vector<int> left, right;
            for (int i : idx) {
                if (i < j && abs(arr[i] - y) <= a) {
                    left.push_back(arr[i]);
                }
            }
            for (int k : idx) {
                if (k > j && abs(arr[k] - y) <= b) {
                    right.push_back(arr[k]);
                }
            }

            // i的取值范围[x - c, x + c]，统计范围内的元素个数
            int k1 = 0, k2 = 0;
            for (int x : left) {
                while (k2 < right.size() && right[k2] <= x + c) {
                    k2++;
                }
                while (k1 < right.size() && right[k1] < x - c) {
                    k1++;
                }
                ans += k2 - k1;
            }
        }
        return ans;
    }
};
// @lc code=end

