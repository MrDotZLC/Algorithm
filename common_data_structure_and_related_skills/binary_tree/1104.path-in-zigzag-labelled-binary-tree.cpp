/*
 * @lc app=leetcode id=1104 lang=cpp
 *
 * [1104] Path In Zigzag Labelled Binary Tree
 *
 * https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/description/
 *
 * algorithms
 * Medium (75.53%)
 * Likes:    1528
 * Dislikes: 327
 * Total Accepted:    51.1K
 * Total Submissions: 67.7K
 * Testcase Example:  '14'
 *
 * In an infinite binary tree where every node has two children, the nodes are
 * labelled in row order.
 * 
 * In the odd numbered rows (ie., the first, third, fifth,...), the labelling
 * is left to right, while in the even numbered rows (second, fourth,
 * sixth,...), the labelling is right to left.
 * 
 * 
 * 
 * Given the label of a node in this tree, return the labels in the path from
 * the root of the tree to the node with that label.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: label = 14
 * Output: [1,3,4,14]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: label = 26
 * Output: [1,2,6,10,26]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= label <= 10^6
 * 
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector <int> ans;
        while(label) {
            ans.push_back(label);
            label >>= 1;
        }
        reverse(ans.begin(), ans.end());
        int l, r, deep = ans.size();
        for(int i = 0; i < deep; i++) {
            if((deep & 1) != (i & 1)) continue;     // 判断第 i 层是否需要修改
            l = (1 << i);
            r = l + l - 1;
            ans[i] = r - ans[i] + l;
        }
        return ans;

    }
};
// @lc code=end

