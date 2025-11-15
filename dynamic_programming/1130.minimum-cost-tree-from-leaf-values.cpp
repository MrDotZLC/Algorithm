/*
 * @lc app=leetcode id=1130 lang=cpp
 *
 * [1130] Minimum Cost Tree From Leaf Values
 *
 * https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/description/
 *
 * algorithms
 * Medium (67.68%)
 * Likes:    4402
 * Dislikes: 280
 * Total Accepted:    117K
 * Total Submissions: 172.8K
 * Testcase Example:  '[6,2,4]'
 *
 * Given an array arr of positive integers, consider all binary trees such
 * that:
 * 
 * 
 * Each node has either 0 or 2 children;
 * The values of arr correspond to the values of each leaf in an in-order
 * traversal of the tree.
 * The value of each non-leaf node is equal to the product of the largest leaf
 * value in its left and right subtree, respectively.
 * 
 * 
 * Among all possible binary trees considered, return the smallest possible sum
 * of the values of each non-leaf node. It is guaranteed this sum fits into a
 * 32-bit integer.
 * 
 * A node is a leaf if and only if it has zero children.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [6,2,4]
 * Output: 32
 * Explanation: There are two possible trees shown.
 * The first has a non-leaf node sum 36, and the second has non-leaf node sum
 * 32.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [4,11]
 * Output: 44
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= arr.length <= 40
 * 1 <= arr[i] <= 15
 * It is guaranteed that the answer fits into a 32-bit signed integer (i.e., it
 * is less than 2^31).
 * 
 * 
 */
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
// @lc code=start
/**
 * 方法一：记忆化搜索/DP
 * 用一个二维数组维护范围最大值
 * f(i,j)表示[i,j]区间内非叶子节点的最小值，max(i,j)下标范围[i,j]内的最大值
 * f(i,j)=min{f(i,k)+f(k+1,j)+max(i,k)*max(k+1,j)}, k∈(i,j-1) <== k>=i&&k+1<=j
 * 边界：i==j时，无非叶子节点，f(i,j)=0
 *      i>=j ，f(i,j)=0
 * 入口：f(1,n)
 * 
 * 方法二：单调栈
 * 自底向上构建树，遍历叶子节点，三个相邻的叶子节点，一定是最小与次小先求代价
 * 用单调栈可实现上述功能，栈顶最小，
 * 节点入栈前，先计算栈顶2个元素和当前节点值，优先计算最小与次小节点的代价，依次弹出，直到当前元素为栈顶
 * 此时，根的左子节点就是最大值节点，依次计算栈顶两个最小节点的代价并逐个弹出，真没元素小于2，则树构建完成
 */
class Solution {
public:
    // 单调栈
    int mctFromLeafValues1(vector<int>& arr) {
        int res = 0;
        deque<int> st;
        for (int x : arr) {
            while (!st.empty() && st.back() <= x) {
                int y = st.back();
                st.pop_back();
                if (st.empty() || st.back() > x) {
                    res += x * y;
                } else {
                    res += st.back() * y;
                }
            }
            st.push_back(x);
        }

        while (st.size() > 1) {
            int x = st.back();
            st.pop_back();
            res += st.back() * x;
        }
        return res;
    }

    // 记忆化递归
    int mctFromLeafValues2(vector<int>& arr) {
        int n = arr.size();
        vector memo(n, vector<int>(n, INT_MAX / 4)), mxs(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) {
            mxs[i][i] = arr[i];
            for (int j = i + 1; j < n; j++) {
                mxs[i][j] = max(mxs[i][j - 1], arr[j]);
            }
        }
        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i >= j) {
                return 0;
            }
            int &res = memo[i][j];
            if (res != INT_MAX / 4) {
                return res;
            }
            for (int k = i; k < j; k++) {
                res = min(res, dfs(dfs, i, k) + dfs(dfs, k + 1, j) +
                                   mxs[i][k] * mxs[k + 1][j]);
            }
            return res;
        };
        return dfs(dfs, 0, n - 1);
    }

    // DP
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector f(n, vector<int>(n)), mxs(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) {
            mxs[i][i] = arr[i];
            for (int j = i + 1; j < n; j++) {
                mxs[i][j] = max(mxs[i][j - 1], arr[j]);
                f[i][j] = INT_MAX / 4;
                for (int k = i; k < j; k++) {
                    f[i][j] =
                        min(f[i][j], f[i][k] + f[k + 1][j] +
                                         mxs[i][k] * mxs[k + 1][j]);
                }
            }
        }
        return f[0][n - 1];
    }
};
// @lc code=end

