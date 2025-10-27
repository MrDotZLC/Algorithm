/*
 * @lc app=leetcode id=1052 lang=cpp
 *
 * [1052] Grumpy Bookstore Owner
 *
 * https://leetcode.com/problems/grumpy-bookstore-owner/description/
 *
 * algorithms
 * Medium (64.03%)
 * Likes:    2581
 * Dislikes: 253
 * Total Accepted:    216.2K
 * Total Submissions: 337.7K
 * Testcase Example:  '[1,0,1,2,1,1,7,5]\n[0,1,0,1,0,1,0,1]\n3'
 *
 * There is a bookstore owner that has a store open for n minutes. You are
 * given an integer array customers of length n where customers[i] is the
 * number of the customers that enter the store at the start of the i^th minute
 * and all those customers leave after the end of that minute.
 * 
 * During certain minutes, the bookstore owner is grumpy. You are given a
 * binary array grumpy where grumpy[i] is 1 if the bookstore owner is grumpy
 * during the i^th minute, and is 0 otherwise.
 * 
 * When the bookstore owner is grumpy, the customers entering during that
 * minute are not satisfied. Otherwise, they are satisfied.
 * 
 * The bookstore owner knows a secret technique to remain not grumpy for
 * minutes consecutive minutes, but this technique can only be used once.
 * 
 * Return the maximum number of customers that can be satisfied throughout the
 * day.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes =
 * 3
 * 
 * Output: 16
 * 
 * Explanation:
 * 
 * The bookstore owner keeps themselves not grumpy for the last 3 minutes.
 * 
 * The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 +
 * 5 = 16.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: customers = [1], grumpy = [0], minutes = 1
 * 
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == customers.length == grumpy.length
 * 1 <= minutes <= n <= 2 * 10^4
 * 0 <= customers[i] <= 1000
 * grumpy[i] is either 0 or 1.
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        // Find the consecutive minutes with the highest satisfaction 
        // score sat_sum. The res is the total satisfaction score plus sat_num.
        int gru_sum = 0, max_gru = 0, total_sat = 0;
        int n = customers.size();
        for (int i = 0; i < n; i++) {
            total_sat += customers[i] * !grumpy[i];
            gru_sum += customers[i] * grumpy[i];
            if (i < minutes - 1) {
                continue;
            }
            max_gru = max(max_gru, gru_sum);
            gru_sum -= customers[i - minutes + 1] * grumpy[i - minutes + 1];
        }
        return total_sat + max_gru;
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<int> customers{9,10,4,5};
    vector<int> grumpy{1,0,1,1};
    int minutes = 1;
    auto res = sol.maxSatisfied(customers, grumpy, minutes);
    cout << "res is " << res << endl;
}