/*
 * @lc app=leetcode id=1310 lang=cpp
 *
 * [1310] XOR Queries of a Subarray
 *
 * https://leetcode.com/problems/xor-queries-of-a-subarray/description/
 *
 * algorithms
 * Medium (78.34%)
 * Likes:    2082
 * Dislikes: 60
 * Total Accepted:    210.3K
 * Total Submissions: 268.7K
 * Testcase Example:  '[1,3,4,8]\n[[0,1],[1,2],[0,3],[3,3]]'
 *
 * You are given an array arr of positive integers. You are also given the
 * array queries where queries[i] = [lefti, righti].
 * 
 * For each query i compute the XOR of elements from lefti to righti (that is,
 * arr[lefti] XOR arr[lefti + 1] XOR ... XOR arr[righti] ).
 * 
 * Return an array answer where answer[i] is the answer to the i^th query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
 * Output: [2,7,14,8] 
 * Explanation: 
 * The binary representation of the elements in the array are:
 * 1 = 0001 
 * 3 = 0011 
 * 4 = 0100 
 * 8 = 1000 
 * The XOR values for queries are:
 * [0,1] = 1 xor 3 = 2 
 * [1,2] = 3 xor 4 = 7 
 * [0,3] = 1 xor 3 xor 4 xor 8 = 14 
 * [3,3] = 8
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
 * Output: [8,0,4,4]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length, queries.length <= 3 * 10^4
 * 1 <= arr[i] <= 10^9
 * queries[i].length == 2
 * 0 <= lefti <= righti < arr.length
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> pre_xor(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            pre_xor[i] = arr[i - 1] ^ pre_xor[i - 1];
        }

        vector<int> ans;
        for (auto &query : queries) {
            int l = query[0], r = query[1];
            ans.push_back(pre_xor[r + 1] ^ pre_xor[l]);
        }

        return ans;
    }
};
// @lc code=end

