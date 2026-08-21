#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

// 输入：n 个节点（0-indexed），edges[i] = {from, to}
// 返回：拓扑序列；若图含环则抛出异常

// bfs 遍历所有入度为 0 的节点的所有子节点，被访问的子节点入度 -1
// 将 bfs 遍历过的节点置入输出数组
// 环判断：环中节点的入度恒不为 0，输出数组长度小于总节点数
vector<int> topo_sort_bfs(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> g(n); // 邻接表
    vector<int> indegree(n);  // 每个节点的入度
    deque<int> q;
    vector<int> res;
    res.reserve(n);

    // 构造邻接表 + 统计入度
    for (auto& [from, to] : edges) {
        g[from].push_back(to);
        ++indegree[to];
    }

    // 0 入度节点进队列
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            q.push_back(i);
        }
    }

    // 遍历队列
    // 被访问的子节点入度 -1，将入度为 0 的节点加入队列
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        res.push_back(cur);
        for (int s : g[cur]) {
            if (--indegree[s] == 0) q.emplace_back(s);
        }
    }

    // 判断是否有环（环中的节点入度永远不为 0，则数组长度小于总节点数）
    if (res.size() < n) {
        throw runtime_error("Graph has cycle");
    }

    return res;
}

// dfs 遍历，设节点有三种状态：0 未访问、1 栈中、2 已完成
// 递归将已完成的节点置入结果数组中，最后翻转输出
// 环判断：栈中节点存在“处于栈中状态的子节点”

void dfs(int i, const vector<vector<int>>& g, vector<int>& status, vector<int>& res) {
    status[i] = 1;
    for (int sub : g[i]) {
        if (status[sub] == 1) {
            throw runtime_error("Graph has cycle.");
        }
        if (status[sub] == 0) {
            dfs(sub, g, status, res);
        }
    }
    status[i] = 2;
    res.push_back(i);
}

vector<int> topo_sort_dfs(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> g(n); // 邻接表
    vector<int> res;
    res.reserve(n);
    vector<int> status(n, 0);

    // 构建邻接表
    for (auto& [from, to] : edges) {
        g[from].push_back(to);
    }

    for (int i = 0; i < n; ++i) {
        if (status[i] == 0) {
            dfs(i, g, status, res);
        }
    }
    
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    // 测试1: 无环图
    cout << "=== 测试1: 无环图 ===" << endl;
    // vector<pair<int, int>> edges1 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
    vector<pair<int, int>> edges1 = {
        {0, 1}, {1, 2},  // 0→1→2
        {3, 4}          // 3→4
    };
    vector<int> res1 = topo_sort_dfs(5, edges1);
    cout << "结果: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    cout << "=== 测试2: 有环图 ===" << endl;
    try {
        vector<pair<int, int>> edges2 = {{0, 1}, {1, 2}, {2, 0}};
        topo_sort_dfs(3, edges2);
    } catch (const exception& e) {
        cout << "报错: " << e.what() << endl;
    }
}