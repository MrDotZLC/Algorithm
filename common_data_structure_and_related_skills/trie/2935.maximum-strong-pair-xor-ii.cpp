/*
 * @lc app=leetcode id=2935 lang=cpp
 *
 * [2935] Maximum Strong Pair XOR II
 *
 * https://leetcode.com/problems/maximum-strong-pair-xor-ii/description/
 *
 * algorithms
 * Hard (31.00%)
 * Likes:    204
 * Dislikes: 2
 * Total Accepted:    8.1K
 * Total Submissions: 25.7K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * You are given a 0-indexed integer array nums. A pair of integers x and y is
 * called a strong pair if it satisfies the condition:
 * 
 * 
 * |x - y| <= min(x, y)
 * 
 * 
 * You need to select two integers from nums such that they form a strong pair
 * and their bitwise XOR is the maximum among all strong pairs in the array.
 * 
 * Return the maximum XOR value out of all possible strong pairs in the array
 * nums.
 * 
 * Note that you can pick the same integer twice to form a pair.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5]
 * Output: 7
 * Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2),
 * (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
 * The maximum XOR possible from these pairs is 3 XOR 4 = 7.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [10,100]
 * Output: 0
 * Explanation: There are 2 strong pairs in the array nums: (10, 10) and (100,
 * 100).
 * The maximum XOR possible from these pairs is 10 XOR 10 = 0 since the pair
 * (100, 100) also gives 100 XOR 100 = 0.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [500,520,2500,3000]
 * Output: 1020
 * Explanation: There are 6 strong pairs in the array nums: (500, 500), (500,
 * 520), (520, 520), (2500, 2500), (2500, 3000) and (3000, 3000).
 * The maximum XOR possible from these pairs is 500 XOR 520 = 1020 since the
 * only other non-zero XOR value is 2500 XOR 3000 = 636.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^4
 * 1 <= nums[i] <= 2^20 - 1
 * 
 * 
 */
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
using namespace std;
// @lc code=start
class Node {
public:
    array<Node*, 2> children{};
    int cnt = 0;
};
class Trie {
    static const int HIGH_BIT = 19;
public:
    Node* root = new Node();

    void insert(int val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = new Node();
            }
            cur = cur->children[bit];
            cur->cnt++;
        }
    }

    void remove(int val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            cur = cur->children[(val >> i) & 1];
            cur->cnt--;
        }
    }

    int max_xor(int val) {
        Node* cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit ^ 1] && cur->children[bit ^ 1]->cnt) {
                ans |= 1 << i;
                bit ^= 1;
            }
            cur = cur->children[bit];
        }
        return ans;
    }
};

class Solution {
public:
    // 位运算+字典树思路
    int maximumStrongPairXor1(vector<int>& nums) {
        ranges::sort(nums);
        int high_bit = __lg(ranges::max(nums));
        int ans = 0, mask = 0;
        unordered_map<int, int> seen;
        for (int i = high_bit; i >= 0; i--) {
            seen.clear();
            mask |= 1 << i;
            int new_ans = ans | (1 << i);
            for (int y : nums) {
                int mask_y = y & mask;
                auto it = seen.find(new_ans ^ mask_y);
                if (it != seen.end() && it->second * 2 >= y) {
                    ans = new_ans;
                    break;
                }
                seen[mask_y] = y;
            }
        }
        return ans;
    }

    // 0-1字典树
    int maximumStrongPairXor(vector<int>& nums) {
        ranges::sort(nums);
        Trie t;
        int ans = 0, left = 0;
        for (int y : nums) {
            t.insert(y);
            while (nums[left] * 2 < y) {
                t.remove(nums[left++]);
            }
            ans = max(ans, t.max_xor(y));
        }
        return ans;
    }
};
// @lc code=end

