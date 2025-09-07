/*
 * @lc app=leetcode id=2049 lang=cpp
 *
 * [2049] Count Nodes With the Highest Score
 *
 * https://leetcode.com/problems/ans-nodes-with-the-highest-cnt/description/
 *
 * algorithms
 * Medium (51.37%)
 * Likes:    1146
 * Dislikes: 94
 * Total Accepted:    37.2K
 * Total Submissions: 72.2K
 * Testcase Example:  '[-1,2,0,2,0]'
 *
 * There is a binary tree rooted at 0 consisting of n nodes. The nodes are
 * labeled from 0 to n - 1. You are given a 0-indexed integer array parents
 * representing the tree, where parents[i] is the parent of node i. Since node
 * 0 is the root, parents[0] == -1.
 * 
 * Each node has a cnt. To find the cnt of a node, consider if the node and
 * the edges connected to it were removed. The tree would become one or more
 * non-empty subtrees. The size of a subtree is the number of the nodes in it.
 * The cnt of the node is the product of the sizes of all those subtrees.
 * 
 * Return the number of nodes that have the highest cnt.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: parents = [-1,2,0,2,0]
 * Output: 3
 * Explanation:
 * - The cnt of node 0 is: 3 * 1 = 3
 * - The cnt of node 1 is: 4 = 4
 * - The cnt of node 2 is: 1 * 1 * 2 = 2
 * - The cnt of node 3 is: 4 = 4
 * - The cnt of node 4 is: 4 = 4
 * The highest cnt is 4, and three nodes (node 1, node 3, and node 4) have
 * the highest cnt.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: parents = [-1,2,0]
 * Output: 2
 * Explanation:
 * - The cnt of node 0 is: 2 = 2
 * - The cnt of node 1 is: 2 = 2
 * - The cnt of node 2 is: 1 * 1 = 1
 * The highest cnt is 2, and two nodes (node 0 and node 1) have the highest
 * cnt.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == parents.length
 * 2 <= n <= 10^5
 * parents[0] == -1
 * 0 <= parents[i] <= n - 1 for i != 0
 * parents represents a valid binary tree.
 * 
 * 
 */
#include "template.h"
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    // 链式前向星建树
    int countHighestScoreNodes1(vector<int>& parents) {
        int n = parents.size();
        fill(he, he + n, -1); // 衰变decay为指针&he[0]，指向第一个元素
        int idx = 0;

        // 建树
        for (int i = 1; i < n; i++) {
            add(parents[i], i); // (头节点，尾节点)
        }

        dfs(0);

        long long mx = 0LL;
        int ans = 0;

        for (int node = 0; node < n; node++) {
            long long sum = 1LL;
            for (int i = he[node]; i != -1; i = ne[i]) { // children
                sum *= f[e[i]];
            }

            if (node != 0) {
                sum *= (long long)(n - f[node]);
            }

            if (sum > mx) {
                mx = sum;
                ans = 1;
            } else if (sum == mx) {
                ans++;
            }
        }
        return ans;
    }

    void add(int a, int b) {
        e[idx] = b;
        ne[idx] = he[a];
        he[a] = idx++;
    }

    int dfs(int node) {
        int sz = 1;
        for (int i = he[node]; i != -1; i = ne[i]) {
            sz += dfs(e[i]);
        }
        f[node] = sz;
        return sz;
    }

    // 邻接表建树
    int countHighestScoreNodes(vector<int>& parents) {
        long long maxScore = 0;
        int ans = 0;
        int n = parents.size();
        vector<vector<int>> children(n);
        for (int i = 0; i < n; i++) {
            int p = parents[i];
            if (p != -1) {
                children[p].emplace_back(i);
            }
        }

        auto dfs = [&](this auto &&dfs, int node) -> int {
            long long cnt = 1LL;
            int sum = 1;
            for (int num : children[node]) {
                int t = dfs(num);
                cnt *= t;
                sum += t;
            }
            if (node != 0) {
                cnt *= n - sum;
            }
            if (maxScore == cnt) {
                ans++;
            } else if (maxScore < cnt) {
                maxScore = cnt;
                ans = 1;
            }
            return sum;
        };
        dfs(0);
        return ans;
    }

private:
    static const int N = 100010, M = N * 2;
    int he[N], e[M], ne[M], idx;
    int f[N]; // 子树大小
};
// @lc code=end

