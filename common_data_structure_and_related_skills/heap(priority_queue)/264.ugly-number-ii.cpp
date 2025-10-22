/*
 * @lc app=leetcode id=264 lang=cpp
 *
 * [264] Ugly Number II
 *
 * https://leetcode.com/problems/ugly-number-ii/description/
 *
 * algorithms
 * Medium (49.29%)
 * Likes:    6779
 * Dislikes: 434
 * Total Accepted:    511.6K
 * Total Submissions: 1M
 * Testcase Example:  '10'
 *
 * An ugly number is a positive integer whose prime factors are limited to 2,
 * 3, and 5.
 * 
 * Given an integer n, return the n^th ugly number.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 10
 * Output: 12
 * Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first
 * 10 ugly numbers.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1
 * Output: 1
 * Explanation: 1 has no prime factors, therefore all of its prime factors are
 * limited to 2, 3, and 5.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 1690
 * 
 * 
 */
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int nthUglyNumber(int n) {
        unordered_set<long long> set;
        priority_queue<long long, vector<long long>, greater<>> pq;
        pq.push(1);
        set.insert(1);
        long long base = 1;
        while (n--) {
            base = pq.top();
            pq.pop();
            if (!set.contains(2 * base)) {
                set.insert(2 * base);
                pq.push(2 * base);
            }
            if (!set.contains(3 * base)) {
                set.insert(3 * base);
                pq.push(3 * base);
            }
            if (!set.contains(5 * base)) {
                set.insert(5 * base);
                pq.push(5 * base);
            }
        }
        return (int)base;
    }
};
// @lc code=end

