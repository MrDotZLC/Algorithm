/*
 * @lc app=leetcode id=2709 lang=cpp
 *
 * [2709] Greatest Common Divisor Traversal
 *
 * https://leetcode.com/problems/greatest-common-divisor-traversal/description/
 *
 * algorithms
 * Hard (41.74%)
 * Likes:    849
 * Dislikes: 142
 * Total Accepted:    75K
 * Total Submissions: 179.6K
 * Testcase Example:  '[2,3,6]'
 *
 * You are given a 0-indexed integer array nums, and you are allowed to
 * traverse between its indices. You can traverse between index i and index j,
 * i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest
 * common divisor.
 * 
 * Your task is to determine if for every pair of indices i and j in nums,
 * where i < j, there exists a sequence of traversals that can take us from i
 * to j.
 * 
 * Return true if it is possible to traverse between all such pairs of indices,
 * or false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,3,6]
 * Output: true
 * Explanation: In this example, there are 3 possible pairs of indices: (0, 1),
 * (0, 2), and (1, 2).
 * To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2
 * -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) =
 * gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because
 * gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
 * To go from index 0 to index 2, we can just go directly because gcd(nums[0],
 * nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we
 * can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,9,5]
 * Output: false
 * Explanation: No sequence of traversals can take us from index 0 to index 2
 * in this example. So, we return false.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [4,3,12,8]
 * Output: true
 * Explanation: There are 6 possible pairs of indices to traverse between: (0,
 * 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3). A valid sequence of
 * traversals exists for each pair, so we return true.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 
 * 
 */
#include <vector>
#include <set>
#include <unordered_map>
#include <numeric>
#include <functional>
using namespace std;
// @lc code=start
const int MX = 1e5;
bool is_prime[MX + 1]; // false为质数
unordered_map<int, vector<int>> mp;

// 埃及筛
int init = [](){
    for (int i = 2; i <= MX; i++) {
        if (!is_prime[i]) {
            for (int j = i; j <= MX; j += i) {
                is_prime[j] = true;
                mp[j].push_back(i);
            }
        }
    }
    return 0;
}();

class Solution {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        if (nums.size() == 1) {
            return true;
        }
        vector<int> p(MX + 1);
        ranges::iota(p, 0);

        function<int(int)> find = [&](int val) {
            return val == p[val] ? val : p[val] = find(p[val]); 
        };

        for (int x : nums) {
            if (x == 1) {
                return false;
            }
            for (int y : mp[x]) {
                x = find(x);
                y = find(y);
                p[x] = y;
            }
        }

        set<int> cnt;
        for (int x : nums) {
            cnt.insert(find(x));
        }
        return cnt.size() == 1;
    }
};
// @lc code=end

