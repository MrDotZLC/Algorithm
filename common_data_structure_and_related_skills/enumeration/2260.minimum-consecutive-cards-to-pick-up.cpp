/*
 * @lc app=leetcode id=2260 lang=cpp
 *
 * [2260] Minimum Consecutive Cards to Pick Up
 *
 * https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/description/
 *
 * algorithms
 * Medium (52.81%)
 * Likes:    1066
 * Dislikes: 44
 * Total Accepted:    111.7K
 * Total Submissions: 210.6K
 * Testcase Example:  '[3,4,2,3,4,7]'
 *
 * You are given an integer array cards where cards[i] represents the value of
 * the i^th card. A pair of cards are matching if the cards have the same
 * value.
 * 
 * Return the minimum number of consecutive cards you have to pick up to have a
 * pair of matching cards among the picked cards. If it is impossible to have
 * matching cards, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: cards = [3,4,2,3,4,7]
 * Output: 4
 * Explanation: We can pick up the cards [3,4,2,3] which contain a matching
 * pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also
 * optimal.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: cards = [1,0,5,3]
 * Output: -1
 * Explanation: There is no way to pick up a set of consecutive cards that
 * contain a pair of matching cards.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= cards.length <= 10^5
 * 0 <= cards[i] <= 10^6
 * 
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        int ans = INT_MAX;
        unordered_map<int, int> idx;
        for (int j = 0; j < cards.size(); j++) {
            if (idx.contains(cards[j])) {
                ans = min(ans, j - idx[cards[j]] + 1);
            }
            idx[cards[j]] = j;
        }
        return ans == INT_MAX ? -1 : ans;
    }

    int minimumCardPickup1(vector<int>& cards) {
        unordered_set<int> st;
        int ans = INT_MAX, l = 0;
        for (int r = 0; r < cards.size(); r++) {
            while (st.contains(cards[r])) {
                ans = min(ans, r - l + 1);
                st.erase(cards[l]);
                l++;
            }
            st.insert(cards[r]);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
// @lc code=end

