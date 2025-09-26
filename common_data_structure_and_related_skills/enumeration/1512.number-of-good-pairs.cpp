/*
 * @lc app=leetcode id=1512 lang=cpp
 *
 * [1512] Number of Good Pairs
 *
 * https://leetcode.com/problems/number-of-good-pairs/description/
 *
 * algorithms
 * Easy (89.61%)
 * Likes:    5757
 * Dislikes: 280
 * Total Accepted:    977.7K
 * Total Submissions: 1.1M
 * Testcase Example:  '[1,2,3,1,1,3]'
 *
 * Given an array of integers nums, return the number of good pairs.
 * 
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,1,1,3]
 * Output: 4
 * Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,1,1]
 * Output: 6
 * Explanation: Each pair in the array are good.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
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
    int numIdenticalPairs1(vector<int>& nums) {
        int ans = 0;
        unordered_map<int, int> idx;
        for (int j = 0; j < nums.size(); j++) {
            ans += idx[nums[j]]++;
        }
        return ans;
    }

    int numIdenticalPairs(vector<int>& nums) {
        ranges::sort(nums);
        int ans = 0, l = 0, r = 1;
        while (r <= nums.size()) {
            if (r == nums.size() || nums[l] != nums[r]) {
                int diff = r - l - 1;
                ans += (diff * (diff + 1)) / 2;
                l = r;
            }
            r++;
        }
        return ans;
    }
};
// @lc code=end
int main() {
    Solution sol;
    vector<int> nums = {1,2,3,1,1,3};

    sol.numIdenticalPairs(nums);
}

