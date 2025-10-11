/*
 * @lc app=leetcode id=2216 lang=cpp
 *
 * [2216] Minimum Deletions to Make Array Beautiful
 *
 * https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/description/
 *
 * algorithms
 * Medium (49.03%)
 * Likes:    831
 * Dislikes: 96
 * Total Accepted:    38.4K
 * Total Submissions: 77.7K
 * Testcase Example:  '[1,1,2,3,5]'
 *
 * You are given a 0-indexed integer array nums. The array nums is beautiful
 * if:
 * 
 * 
 * nums.length is even.
 * nums[i] != nums[i + 1] for all i % 2 == 0.
 * 
 * 
 * Note that an empty array is considered beautiful.
 * 
 * You can delete any number of elements from nums. When you delete an element,
 * all the elements to the right of the deleted element will be shifted one
 * unit to the left to fill the gap created and all the elements to the left of
 * the deleted element will remain unchanged.
 * 
 * Return the minimum number of elements to delete from nums to make it
 * beautiful.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,2,3,5]
 * Output: 1
 * Explanation: You can delete either nums[0] or nums[1] to make nums =
 * [1,2,3,5] which is beautiful. It can be proven you need at least 1 deletion
 * to make nums beautiful.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,2,2,3,3]
 * Output: 2
 * Explanation: You can delete nums[0] and nums[5] to make nums = [1,2,2,3]
 * which is beautiful. It can be proven you need at least 2 deletions to make
 * nums beautiful.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^5
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int minDeletion1(vector<int>& nums) {
        int ans = 0;
        vector<int> st;
        for (int i : nums) {
            if (!st.empty()) {
                if (st.back() == i) {
                    ans++;
                } else {
                    st.pop_back();
                }
            } else {
                st.push_back(i);
            }
        }
        return ans + st.size();
    }

    int minDeletion(vector<int>& nums) {
        int ans = 0, last = nums[0], flag = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (flag) {
                if (nums[i] == last) {
                    ans++;
                } else {
                    flag = 0;
                }
            } else {
                flag = 1;
                last = nums[i];
            }
        }
       
        return ans + (nums.size() - ans) % 2;
    }
};
// @lc code=end

