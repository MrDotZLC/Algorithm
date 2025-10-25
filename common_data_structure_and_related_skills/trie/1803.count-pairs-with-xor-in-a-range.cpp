/*
 * @lc app=leetcode id=1803 lang=cpp
 *
 * [1803] Count Pairs With XOR in a Range
 *
 * https://leetcode.com/problems/count-pairs-with-xor-in-a-range/description/
 *
 * algorithms
 * Hard (45.87%)
 * Likes:    546
 * Dislikes: 24
 * Total Accepted:    11.6K
 * Total Submissions: 25.1K
 * Testcase Example:  '[1,4,2,7]\n2\n6'
 *
 * Given a (0-indexed) integer array nums and two integers low and high, return
 * the number of nice pairs.
 * 
 * A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <=
 * (nums[i] XOR nums[j]) <= high.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,4,2,7], low = 2, high = 6
 * Output: 6
 * Explanation: All nice pairs (i, j) are as follows:
 * ⁠   - (0, 1): nums[0] XOR nums[1] = 5 
 * ⁠   - (0, 2): nums[0] XOR nums[2] = 3
 * ⁠   - (0, 3): nums[0] XOR nums[3] = 6
 * ⁠   - (1, 2): nums[1] XOR nums[2] = 6
 * ⁠   - (1, 3): nums[1] XOR nums[3] = 3
 * ⁠   - (2, 3): nums[2] XOR nums[3] = 5
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [9,8,4,2,1], low = 5, high = 14
 * Output: 8
 * Explanation: All nice pairs (i, j) are as follows:
 * ​​​​​    - (0, 2): nums[0] XOR nums[2] = 13
 * - (0, 3): nums[0] XOR nums[3] = 11
 * - (0, 4): nums[0] XOR nums[4] = 8
 * - (1, 2): nums[1] XOR nums[2] = 12
 * - (1, 3): nums[1] XOR nums[3] = 10
 * - (1, 4): nums[1] XOR nums[4] = 9
 * - (2, 3): nums[2] XOR nums[3] = 6
 * - (2, 4): nums[2] XOR nums[4] = 5
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * 1 <= nums[i] <= 2 * 10^4
 * 1 <= low <= high <= 2 * 10^4
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
    int cnt = 0;
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
            ++cur->cnt;
        }
    }

    int search(int val, int limit) {
        Node* cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0 && cur; i--) {
            int bit = (val >> i) & 1;
            if (limit >> i & 1) {
                if (cur->children[bit]) {
                    ans += cur->children[bit]->cnt;
                }
                cur = cur->children[bit ^ 1];
            } else {
                cur = cur->children[bit];
            }
        }
        return ans;
    }

private:
    static const int HIGH_BIT = 15;
    Node* root = new Node();
};

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        Trie* t = new Trie();
        int ans = 0;
        for (int x : nums) {
            ans += t->search(x, high + 1) - t->search(x, low);
            t->insert(x);
        }
        return ans;
    }
};
// @lc code=end

