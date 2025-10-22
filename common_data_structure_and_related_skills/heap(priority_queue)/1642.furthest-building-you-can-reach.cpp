/*
 * @lc app=leetcode id=1642 lang=cpp
 *
 * [1642] Furthest Building You Can Reach
 *
 * https://leetcode.com/problems/furthest-building-you-can-reach/description/
 *
 * algorithms
 * Medium (50.42%)
 * Likes:    6155
 * Dislikes: 148
 * Total Accepted:    260.8K
 * Total Submissions: 516.1K
 * Testcase Example:  '[4,2,7,6,9,14,12]\n5\n1'
 *
 * You are given an integer array heights representing the heights of
 * buildings, some bricks, and some ladders.
 * 
 * You start your journey from building 0 and move to the next building by
 * possibly using bricks or ladders.
 * 
 * While moving from building i to building i+1 (0-indexed),
 * 
 * 
 * If the current building's height is greater than or equal to the next
 * building's height, you do not need a ladder or bricks.
 * If the current building's height is less than the next building's height,
 * you can either use one ladder or (h[i+1] - h[i]) bricks.
 * 
 * 
 * Return the furthest building index (0-indexed) you can reach if you use the
 * given ladders and bricks optimally.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
 * Output: 4
 * Explanation: Starting at building 0, you can follow these steps:
 * - Go to building 1 without using ladders nor bricks since 4 >= 2.
 * - Go to building 2 using 5 bricks. You must use either bricks or ladders
 * because 2 < 7.
 * - Go to building 3 without using ladders nor bricks since 7 >= 6.
 * - Go to building 4 using your only ladder. You must use either bricks or
 * ladders because 6 < 9.
 * It is impossible to go beyond building 4 because you do not have any more
 * bricks or ladders.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
 * Output: 7
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: heights = [14,3,19,3], bricks = 17, ladders = 0
 * Output: 3
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= heights.length <= 10^5
 * 1 <= heights[i] <= 10^6
 * 0 <= bricks <= 10^9
 * 0 <= ladders <= heights.length
 * 
 * 
 */
#include <queue>
using namespace std;
// @lc code=start
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size(); 
        priority_queue<int> pq;
        int i = 0;
        for (; i < n - 1; i++) {
            if (heights[i] < heights[i + 1]) {
                int diff = heights[i + 1] - heights[i]; //高度差
                //要使用工具了
                //先使用砖块
                if (bricks >= diff) {
                    bricks -= diff;
                    pq.push(diff);
                } else if (ladders > 0) {
                    //使用砖块到不了这个位置，必须要用梯子了
                    //要将梯子用在diff最大的位置，也有可能是当前位置到一个位置的diff最大，所以要将当前位置的diff进堆，就不用特殊判断了
                    pq.push(diff);
                    bricks -= diff; 
                    bricks += pq.top(); //反悔 用在高度差最大的位置，那么那个地方的砖块又可以拿回来了
                    pq.pop();
                    ladders--; //使用梯子
                } else {
                    break; //砖块和梯子都不够用了，停止前进
                }
            }
        }
        return i;
    }
};
// @lc code=end

