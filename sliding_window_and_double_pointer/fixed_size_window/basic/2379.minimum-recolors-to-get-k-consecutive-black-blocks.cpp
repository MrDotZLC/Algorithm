/*
 * @lc app=leetcode id=2379 lang=cpp
 *
 * [2379] Minimum Recolors to Get K Consecutive Black Blocks
 *
 * https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/description/
 *
 * algorithms
 * Easy (68.45%)
 * Likes:    1276
 * Dislikes: 38
 * Total Accepted:    211.7K
 * Total Submissions: 309.4K
 * Testcase Example:  '"WBBWWBBWBW"\n7'
 *
 * You are given a 0-indexed string blocks of length n, where blocks[i] is
 * either 'W' or 'B', representing the color of the i^th block. The characters
 * 'W' and 'B' denote the colors white and black, respectively.
 * 
 * You are also given an integer k, which is the desired number of consecutive
 * black blocks.
 * 
 * In one operation, you can recolor a white block such that it becomes a black
 * block.
 * 
 * Return the minimum number of operations needed such that there is at least
 * one occurrence of k consecutive black blocks.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: blocks = "WBBWWBBWBW", k = 7
 * Output: 3
 * Explanation:
 * One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd,
 * and 4th blocks
 * so that blocks = "BBBBBBBWBW". 
 * It can be shown that there is no way to achieve 7 consecutive black blocks
 * in less than 3 operations.
 * Therefore, we return 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: blocks = "WBWBBBW", k = 2
 * Output: 0
 * Explanation:
 * No changes need to be made, since 2 consecutive black blocks already exist.
 * Therefore, we return 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == blocks.length
 * 1 <= n <= 100
 * blocks[i] is either 'W' or 'B'.
 * 1 <= k <= n
 * 
 * 
 */
#include <vector>
#include <iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int res = k, counter = 0;
        for (int i = 0; i < blocks.length(); i++) {
            /**
             * @brief A more efficent way
             * As we all known, bitwise is more efficent than if-else.
             * the ASCII value of 'W' is 87, which means the lowest bit is 1.
             * Similarly, the lowest bit of 'B' is 0. In this way, 
             * bitwise operations can be used to replaced if-else.
             * Such as: counter
             */
            if (blocks[i] == 'W') { // counter += blocks[i] & 1;
                counter++;
            }
            if (i < k - 1) {
                continue;
            }
            res = min(res, counter);
            if (blocks.at(i - k + 1) == 'W') {
                counter--;
            }
        }
        return res;
    }
};
// @lc code=end

