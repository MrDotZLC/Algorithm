/*
 * @lc app=leetcode id=1095 lang=cpp
 *
 * [1095] Find in Mountain Array
 *
 * https://leetcode.com/problems/find-in-mountain-array/description/
 *
 * algorithms
 * Hard (40.56%)
 * Likes:    3482
 * Dislikes: 145
 * Total Accepted:    176.3K
 * Total Submissions: 433.8K
 * Testcase Example:  '[1,2,3,4,5,3,1]\n3'
 *
 * (This problem is an interactive problem.)
 *
 * You may recall that an array arr is a mountain array if and only if:
 *
 *
 * arr.length >= 3
 * There exists some i with 0 < i < arr.length - 1 such that:
 *
 * arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 * arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 *
 *
 *
 *
 * Given a mountain array mountainArr, return the minimum index such that
 * mountainArr.get(index) == target. If such an index does not exist, return
 * -1.
 *
 * You cannot access the mountain array directly. You may only access the array
 * using a MountainArray interface:
 *
 *
 * MountainArray.get(k) returns the element of the array at index k
 * (0-indexed).
 * MountainArray.length() returns the length of the array.
 *
 *
 * Submissions making more than 100 calls to MountainArray.get will be judged
 * Wrong Answer. Also, any solutions that attempt to circumvent the judge will
 * result in disqualification.
 *
 *
 * Example 1:
 *
 *
 * Input: mountainArr = [1,2,3,4,5,3,1], target = 3
 * Output: 2
 * Explanation: 3 exists in the array, at index=2 and index=5. Return the
 * minimum index, which is 2.
 *
 * Example 2:
 *
 *
 * Input: mountainArr = [0,1,2,4,2,1], target = 3
 * Output: -1
 * Explanation: 3 does not exist in the array, so we return -1.
 *
 *
 *
 * Constraints:
 *
 *
 * 3 <= mountainArr.length() <= 10^4
 * 0 <= target <= 10^9
 * 0 <= mountainArr.get(index) <= 10^9
 *
 *
 */
// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
   public:
    int get(int index);
    int length();
};

// @lc code=start
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray& mountainArr) {
        int n = mountainArr.length();
        int L = 1, R = n - 2;
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                L = mid;
            } else {
                R = mid;
            }
        }

        auto find = [&](int L, int R, bool order) -> int {
            while (L <= R) {
                int mid = L + (R - L) / 2;
                if ((mountainArr.get(mid) < target && order) ||
                    (mountainArr.get(mid) > target && !order)) {
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }
            return (L != n && mountainArr.get(L) == target) ? L : -1;
        };

        int left_ans = find(0, R, true);
        if (left_ans != -1) {
            return left_ans;
        }
        return find(R, n - 1, false);
    }
};
// @lc code=end
