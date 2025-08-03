/*
 * @lc app=leetcode id=2540 lang=cpp
 *
 * [2540] Minimum Common Value
 *
 * https://leetcode.com/problems/minimum-common-value/description/
 *
 * algorithms
 * Easy (58.13%)
 * Likes:    1204
 * Dislikes: 40
 * Total Accepted:    286.4K
 * Total Submissions: 492.9K
 * Testcase Example:  '[1,2,3]\n[2,4]'
 *
 * Given two integer arrays nums1 and nums2, sorted in non-decreasing order,
 * return the minimum integer common to both arrays. If there is no common
 * integer amongst nums1 and nums2, return -1.
 * 
 * Note that an integer is said to be common to nums1 and nums2 if both arrays
 * have at least one occurrence of that integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,2,3], nums2 = [2,4]
 * Output: 2
 * Explanation: The smallest element common to both arrays is 2, so we return
 * 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
 * Output: 2
 * Explanation: There are two common elements in the array 2 and 3 out of which
 * 2 is the smallest, so 2 is returned.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 10^5
 * 1 <= nums1[i], nums2[j] <= 10^9
 * Both nums1 and nums2 are sorted in non-decreasing order.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int i=0,j=0;
        int ans=-1;
        while(i<nums1.size()&&j<nums2.size()){
            if(nums1[i]==nums2[j]){
                ans=nums1[i];
                break;
            }else if(nums1[i]>nums2[j]){
                j++;
            }else {
                i++;
            }
        }
        return ans;
    }
};
// @lc code=end

