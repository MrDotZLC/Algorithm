/*
 * @lc app=leetcode id=1707 lang=cpp
 *
 * [1707] Maximum XOR With an Element From Array
 *
 * https://leetcode.com/problems/maximum-xor-with-an-element-from-array/description/
 *
 * algorithms
 * Hard (55.72%)
 * Likes:    1365
 * Dislikes: 40
 * Total Accepted:    41.3K
 * Total Submissions: 72.7K
 * Testcase Example:  '[0,1,2,3,4]\n[[3,1],[1,3],[5,6]]'
 *
 * You are given an array nums consisting of non-negative integers. You are
 * also given a queries array, where queries[i] = [xi, mi].
 * 
 * The answer to the i^th query is the maximum bitwise XOR value of xi and any
 * element of nums that does not exceed mi. In other words, the answer is
 * max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in
 * nums are larger than mi, then the answer is -1.
 * 
 * Return an integer array answer where answer.length == queries.length and
 * answer[i] is the answer to the i^th query.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
 * Output: [3,3,7]
 * Explanation:
 * 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1
 * XOR 3 = 2. The larger of the two is 3.
 * 2) 1 XOR 2 = 3.
 * 3) 5 XOR 2 = 7.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
 * Output: [15,-1,5]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length, queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= nums[j], xi, mi <= 10^9
 * 
 * 
 */
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
struct Node {
    array<Node*, 2> children{};
};
class Trie {
public:
    void insert(int val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = new Node();
            }
            cur = cur->children[bit];
        }
    }

    int max_xor(int val) {
        if (!root->children[0] && !root->children[1]) {
            return -1;
        }
        Node* cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit ^ 1]) {
                ans |= 1 << i;
                bit ^= 1;
            }
            cur = cur->children[bit];
        }
        return ans;
    }

private:
    static const int HIGH_BIT = 30;
    Node* root = new Node();
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        ranges::sort(nums);
        vector<tuple<int, int, int>> qs;
        for (int i = 0; i < queries.size(); i++) {
            qs.emplace_back(queries[i][1], queries[i][0], i);
        }
        ranges::sort(qs);

        vector<int> ans(queries.size());
        Trie* root = new Trie();
        int i = 0, n = nums.size();
        for (auto &[mi, xi, idx] : qs) {
            while (i < n && nums[i] <= mi) {
                root->insert(nums[i++]);
            }
            if (i == 0) {
                ans[idx] = -1;
            } else {
                ans[idx] = root->max_xor(xi);
            }
        }
        return ans;
    }
};
// @lc code=end

