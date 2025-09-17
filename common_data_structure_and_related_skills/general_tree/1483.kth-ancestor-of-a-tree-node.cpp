/*
 * @lc app=leetcode id=1483 lang=cpp
 *
 * [1483] Kth Ancestor of a Tree Node
 *
 * https://leetcode.com/problems/kth-ancestor-of-a-tree-node/description/
 *
 * algorithms
 * Hard (36.14%)
 * Likes:    2047
 * Dislikes: 123
 * Total Accepted:    47.1K
 * Total Submissions: 129.4K
 * Testcase Example:  '["TreeAncestor","getKthAncestor","getKthAncestor","getKthAncestor"]\n' +
  '[[7,[-1,0,0,1,1,2,2]],[3,1],[5,2],[6,3]]'
 *
 * You are given a tree with n nodes numbered from 0 to n - 1 in the form of a
 * parent array parent where parent[i] is the parent of i^th node. The root of
 * the tree is node 0. Find the k^th ancestor of a given node.
 * 
 * The k^th ancestor of a tree node is the k^th node in the path from that node
 * to the root node.
 * 
 * Implement the TreeAncestor class:
 * 
 * 
 * TreeAncestor(int n, int[] parent) Initializes the object with the number of
 * nodes in the tree and the parent array.
 * int getKthAncestor(int node, int k) return the k^th ancestor of the given
 * node node. If there is no such ancestor, return -1.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["TreeAncestor", "getKthAncestor", "getKthAncestor", "getKthAncestor"]
 * [[7, [-1, 0, 0, 1, 1, 2, 2]], [3, 1], [5, 2], [6, 3]]
 * Output
 * [null, 1, 0, -1]
 * 
 * Explanation
 * TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);
 * treeAncestor.getKthAncestor(3, 1); // returns 1 which is the parent of 3
 * treeAncestor.getKthAncestor(5, 2); // returns 0 which is the grandparent of
 * 5
 * treeAncestor.getKthAncestor(6, 3); // returns -1 because there is no such
 * ancestor
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= n <= 5 * 10^4
 * parent.length == n
 * parent[0] == -1
 * 0 <= parent[i] < n for all 0 < i < n
 * 0 <= node < n
 * There will be at most 5 * 10^4 queries.
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        int m = bit_width((unsigned) n); // int m = floor(log2(n)) + 1;
        pa.resize(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            pa[i][0] = parent[i];
        }
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                int p = pa[x][i]; 
                if (p != -1) {
                    pa[x][i + 1] = pa[p][i];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        int m = bit_width((unsigned) k);
        for (int i = 0; i < m; i++) {
            if (k >> i & 1) {
                node = pa[node][i];
                if (node < 0) {
                    break;
                }
            }
        }
        return node;
    }
private:
    vector<vector<int>> pa;
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
// @lc code=end

