/*
 * @lc app=leetcode id=1423 lang=cpp
 *
 * [1423] Maximum Points You Can Obtain from Cards
 *
 * https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/
 *
 * algorithms
 * Medium (55.84%)
 * Likes:    6690
 * Dislikes: 284
 * Total Accepted:    409.9K
 * Total Submissions: 732.8K
 * Testcase Example:  '[1,2,3,4,5,6,1]\n3'
 *
 * There are several cards arranged in a row, and each card has an associated
 * number of points. The points are given in the integer array cardPoints.
 * 
 * In one step, you can take one card from the beginning or from the end of the
 * row. You have to take exactly k cards.
 * 
 * Your score is the sum of the points of the cards you have taken.
 * 
 * Given the integer array cardPoints and the integer k, return the maximum
 * score you can obtain.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: cardPoints = [1,2,3,4,5,6,1], k = 3
 * Output: 12
 * Explanation: After the first step, your score will always be 1. However,
 * choosing the rightmost card first will maximize your total score. The
 * optimal strategy is to take the three cards on the right, giving a final
 * score of 1 + 6 + 5 = 12.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: cardPoints = [2,2,2], k = 2
 * Output: 4
 * Explanation: Regardless of which two cards you take, your score will always
 * be 4.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: cardPoints = [9,7,7,9,7,7,9], k = 7
 * Output: 55
 * Explanation: You have to take all the cards. Your score is the sum of points
 * of all cards.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= cardPoints.length <= 10^5
 * 1 <= cardPoints[i] <= 10^4
 * 1 <= k <= cardPoints.length
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
    // Positive thinking
    int maxScore1(vector<int>& cardPoints, int k) {
        int res = 0, sum = 0;
        int n = cardPoints.size();

        // init window
        for (int i = 0; i < k; i++) {
            sum += cardPoints[i];
        }
        res = max(res, sum);

        if (n == k) {
            return res;
        }

        for (int j = 0; j < k; j++) {
            sum -= cardPoints[k - 1 - j];
            sum += cardPoints[n - 1 - j];
            res = max(res, sum);
        }

        return res;
    }

    // Reverse thinking: find the minimum contiguous 
    // array with length n - k
    int maxScore2(vector<int>& cardPoints, int k) {
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);

        int res = INT_MAX, sum = 0;
        int n = cardPoints.size();

        if (n == k) {
            return total;
        }

        for (int j = 0; j < n; j++) {
            sum += cardPoints[j];
            if (j < (n - k) - 1) {
                continue;
            }
            res = min(res, sum);
            sum -= cardPoints[j + 1 - (n - k)];
        }

        return total - res;
    }

    // Optimized method 2 
    int maxScore(vector<int>& cardPoints, int k) {
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        int n = cardPoints.size();
        int j = n - k; 
        int sum = accumulate(cardPoints.begin(), cardPoints.begin() + j, 0);
        int temp = sum;
        for (int i = j; i < n; i++) {
            sum += cardPoints[i] - cardPoints[i - j];
            temp = min(temp, sum);
        }
        return total - temp;
    }

    /**
     * Advanced problem: set k is unlimited and
     * array cardPoints contains nagetive number.
     * */  
    // Positive thinking: 
    // Traverse the prefix and suffix sum. Time cost O（n^2)
    int maxScoreAdvanced1(vector<int>& cardPoints) {
        int n = cardPoints.size();
        vector<int> prefix(n + 2, 0), suffix(n + 2, 0);
        int res = 0; // take 0 sheet, res = 0

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + cardPoints[i];

            suffix[i + 1] = suffix[i] + cardPoints[n - i - 1];
            int temp = 0;
        }
        int temp = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n - i; j++) {
                res = max(res, prefix[i] + suffix[j]);
                temp = 0;
            }
        }

        return res; 
    }

    // Reverse thinking: use Kadane Algorithm. 
    // This problem is equal to find the sum of minimum congeous array.
    int maxScoreAdvanced2(vector<int>& cardPoints) {
        int res = 0;
        int cur = 0;
        for (int i = 0; i < cardPoints.size(); i++) {
            cur = min(cur, cur + cardPoints[i]);
            res = min(res, cur);
        }
        return accumulate(cardPoints.begin(), cardPoints.end(), 0) - res; 
    }
};
// @lc code=end

int main() {
    Solution sol;

    vector<int> nums{-1,-2,-3,4,-5,6,-1};
    int k = 2;
    auto res = sol.maxScoreAdvanced1(nums);
    cout << "res is " << res << endl;
}