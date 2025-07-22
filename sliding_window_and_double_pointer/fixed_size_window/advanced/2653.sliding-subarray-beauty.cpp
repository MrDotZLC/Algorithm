/*
 * @lc app=leetcode id=2653 lang=cpp
 *
 * [2653] Sliding Subarray Beauty
 *
 * https://leetcode.com/problems/sliding-subarray-beauty/description/
 *
 * algorithms
 * Medium (34.29%)
 * Likes:    691
 * Dislikes: 138
 * Total Accepted:    27.7K
 * Total Submissions: 80.5K
 * Testcase Example:  '[1,-1,-3,-2,3]\n3\n2'
 *
 * Given an integer array nums containing n integers, find the beauty of each
 * subarray of size k.
 * 
 * The beauty of a subarray is the x^th smallest integer in the subarray if it
 * is negative, or 0 if there are fewer than x negative integers.
 * 
 * Return an integer array containing n - k + 1 integers, which denote the
 * beauty of the subarrays in order from the first index in the
 * array.
 * 
 * 
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
 * Output: [-1,-2,-2]
 * Explanation: There are 3 subarrays with size k = 3. 
 * The first subarray is [1, -1, -3] and the 2^nd smallest negative integer is
 * -1. 
 * The second subarray is [-1, -3, -2] and the 2^nd smallest negative integer
 * is -2. 
 * The third subarray is [-3, -2, 3] and the 2^nd smallest negative integer is
 * -2.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-1,-2,-3,-4,-5], k = 2, x = 2
 * Output: [-1,-2,-3,-4]
 * Explanation: There are 4 subarrays with size k = 2.
 * For [-1, -2], the 2^nd smallest negative integer is -1.
 * For [-2, -3], the 2^nd smallest negative integer is -2.
 * For [-3, -4], the 2^nd smallest negative integer is -3.
 * For [-4, -5], the 2^nd smallest negative integer is -4. 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [-3,1,2,-3,0,-3], k = 2, x = 1
 * Output: [-3,0,-3,-3,-3]
 * Explanation: There are 5 subarrays with size k = 2.
 * For [-3, 1], the 1^st smallest negative integer is -3.
 * For [1, 2], there is no negative integer so the beauty is 0.
 * For [2, -3], the 1^st smallest negative integer is -3.
 * For [-3, 0], the 1^st smallest negative integer is -3.
 * For [0, -3], the 1^st smallest negative integer is -3.
 * 
 * 
 * Constraints:
 * 
 * 
 * n == nums.length 
 * 1 <= n <= 10^5
 * 1 <= k <= n
 * 1 <= x <= k 
 * -50 <= nums[i] <= 50 
 * 
 * 
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    // Timeout
    vector<int> getSubarrayBeauty1(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> res(n - k + 1);
        vector<int> store;
        int first_ele = nums[0];

        auto insert_num = [&] (int num) {
            auto it = lower_bound(store.begin(), store.end(), num);
            store.insert(it, num);
        };

        auto delete_first_num = [&] () {
            auto it = find(store.begin(), store.end(), first_ele);
            if (it != store.end()) {
                store.erase(it);
            }
        };

        for (int i = 0; i < n; i++) {
            insert_num(nums[i]);
            if (i < k - 1) {
                continue;
            }
            first_ele = nums[i - k + 1];
            if (store[x - 1] < 0) {
                res[i - k + 1] = store[x - 1];
            }
            delete_first_num();
        }
        return res;
    }

    // Maintian a nagetive integer of counting sort using a array, 
    // because of little range nums[i]
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        const int BIAS = 50;
        int cnt[BIAS]{};
        for (int i = 0; i < k - 1; i++) {
            if (nums[i] < 0) {
                cnt[nums[i] + BIAS]++;
            }
        }
        
        int n = nums.size();
        vector<int> res(n - k + 1);
        for (int i = k - 1; i < n; i++) {
            if (nums[i] < 0) {
                cnt[nums[i] + BIAS]++;
            }
            int left = x;
            for (int j = 0; j < BIAS; j++) {
                left -= cnt[j];
                if (left <= 0) {
                    res[i - k + 1] = j - BIAS;
                    break;
                }
            }
            if (nums[i - k + 1] < 0) {
                cnt[nums[i - k + 1] + BIAS]--;
            }
        }
        return res;
    }
};
// @lc code=end

