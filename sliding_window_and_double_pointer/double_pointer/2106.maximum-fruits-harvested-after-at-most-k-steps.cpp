/*
 * @lc app=leetcode id=2106 lang=cpp
 *
 * [2106] Maximum Fruits Harvested After at Most K Steps
 *
 * https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/description/
 *
 * algorithms
 * Hard (36.73%)
 * Likes:    576
 * Dislikes: 20
 * Total Accepted:    13.2K
 * Total Submissions: 36K
 * Testcase Example:  '[[2,8],[6,3],[8,6]]\n5\n4'
 *
 * Fruits are available at some positions on an infinite x-axis. You are given
 * a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts
 * amounti fruits at the position positioni. fruits is already sorted by
 * positioni in ascending order, and each positioni is unique.
 * 
 * You are also given an integer startPos and an integer k. Initially, you are
 * at the position startPos. From any position, you can either walk to the left
 * or right. It takes one step to move one unit on the x-axis, and you can walk
 * at most k steps in total. For every position you reach, you harvest all the
 * fruits at that position, and the fruits will disappear from that position.
 * 
 * Return the maximum total number of fruits you can harvest.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
 * Output: 9
 * Explanation: 
 * The optimal way is to:
 * - Move right to position 6 and harvest 3 fruits
 * - Move right to position 8 and harvest 6 fruits
 * You moved 3 steps and harvested 3 + 6 = 9 fruits in total.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
 * Output: 14
 * Explanation: 
 * You can move at most k = 4 steps, so you cannot reach position 0 nor 10.
 * The optimal way is to:
 * - Harvest the 7 fruits at the starting position 5
 * - Move left to position 4 and harvest 1 fruit
 * - Move right to position 6 and harvest 2 fruits
 * - Move right to position 7 and harvest 4 fruits
 * You moved 1 + 3 = 4 steps and harvested 7 + 1 + 2 + 4 = 14 fruits in
 * total.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
 * Output: 0
 * Explanation:
 * You can move at most k = 2 steps and cannot reach any position with
 * fruits.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= fruits.length <= 10^5
 * fruits[i].length == 2
 * 0 <= startPos, positioni <= 2 * 10^5
 * positioni-1 < positioni for any i > 0 (0-indexed)
 * 1 <= amounti <= 10^4
 * 0 <= k <= 2 * 10^5
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
    int maxTotalFruits2(vector<vector<int>>& fruits, int startPos, int k) {
        int ans = 0;
        vector<int> freq(fruits.back()[0] + 1);
        for (int i = 0; i < fruits.size(); i++) {
            freq[fruits[i][0]] = fruits[i][1];
        }
        for (int i = 0; i <= k; i++) {
            int left = startPos - (k - i);
            int right = startPos - (k - i * 2);
            int l = min({left, right, startPos});
            int r = max({left, right, startPos});
            int sum = 0;
            while (l <= r && l >= 0 && r < freq.size()) {
                sum += freq[l++];                
            }
            ans = max(ans, sum);
        }
        for (int i = 0; i <= k; i++) {
            int right = startPos + i;
            int left = startPos + (i * 2 - k);
            int l = min({left, right, startPos});
            int r = max({left, right, startPos});
            int sum = 0;
            while (l <= r && l >= 0 && r < freq.size()) {
                sum += freq[l++];                
            }
            ans = max(ans, sum);
        }
        return ans;
    }

    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int ans = 0;
        int l = lower_bound(fruits.begin(), fruits.end(), startPos - k,
            [] (const auto &a, int b) {
                return a[0] < b;
            }) - fruits.begin();
        int r = l, sum = 0, n = fruits.size();
        for (; r < n && fruits[r][0] <= startPos; r++) {
            sum += fruits[r][1];
        }
        ans = max(ans, sum);
        for (; r < n && fruits[r][0] <= startPos + k; r++) {
            sum += fruits[r][1];
            while ((fruits[r][0] - startPos) + (fruits[r][0] - fruits[l][0]) > k &&
                (startPos - fruits[l][0]) + (fruits[r][0] - fruits[l][0]) > k
            ) {
                sum -= fruits[l++][1];
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
// @lc code=end

