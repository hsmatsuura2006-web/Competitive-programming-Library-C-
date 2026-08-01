// 無向グラフの閉路列挙 (C++版)
//
//  1. fundamentalCycles(graph)
//     全域森 + back edge から「基本閉路（サイクル空間の基底）」を求める。
//     計算量: O(V + E) 程度。閉路本数は E - V + (連結成分数) 個。
//
//  2. allSimpleCycles(graph)
//     グラフに存在する全ての単純閉路を列挙する。
//     最悪指数時間。密なグラフでは閉路数が爆発するので注意。
//
// グラフは vector<set<int>>（頂点0..n-1の隣接リスト）で表す。

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

using Graph = vector<set<int>>;

Graph buildGraph(int n, const vector<pair<int,int>>& edges) {
    Graph g(n);
    for (auto& [u, v] : edges) {
        if (u == v) continue; // 自己ループは無視
        g[u].insert(v);
        g[v].insert(u);
    }
    return g;
}

// ---------- 1. 基本閉路（サイクル空間の基底） ----------
vector<vector<int>> fundamentalCycles(const Graph& g) {
    int n = g.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> depth(n, -1);
    vector<vector<int>> cycles;

    for (int start = 0; start < n; ++start) {
        if (visited[start]) continue;

        // BFS/DFSで全域木を構築
        visited[start] = true;
        parent[start] = -1;
        depth[start] = 0;
        vector<int> order = {start};
        vector<int> stack = {start};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v : g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    stack.push_back(v);
                    order.push_back(v);
                }
            }
        }

        set<pair<int,int>> treeEdges;
        for (int v : order) {
            if (parent[v] != -1) {
                treeEdges.insert({min(v, parent[v]), max(v, parent[v])});
            }
        }

        set<pair<int,int>> seenBack;
        for (int u : order) {
            for (int v : g[u]) {
                auto e = make_pair(min(u, v), max(u, v));
                if (treeEdges.count(e) || seenBack.count(e)) continue;
                seenBack.insert(e);

                // u, v から共通の祖先(LCA)まで木を辿って閉路を作る
                int a = u, b = v;
                vector<int> pathA = {a}, pathB = {b};
                while (depth[a] > depth[b]) { a = parent[a]; pathA.push_back(a); }
                while (depth[b] > depth[a]) { b = parent[b]; pathB.push_back(b); }
                while (a != b) {
                    a = parent[a]; pathA.push_back(a);
                    b = parent[b]; pathB.push_back(b);
                }

                vector<int> cycle(pathA.begin(), pathA.end() - 1);
                cycle.insert(cycle.end(), pathB.rbegin(), pathB.rend());
                if ((int)cycle.size() >= 3) cycles.push_back(cycle);
            }
        }
    }
    return cycles;
}

// ---------- 2. 全単純閉路の列挙 ----------
void dfsSimpleCycles(const Graph& g, int start, int current,
                      vector<int>& path, vector<bool>& visited,
                      vector<vector<int>>& cycles) {
    for (int neighbor : g[current]) {
        if (neighbor == start) {
            if ((int)path.size() >= 3 && path[1] < path.back()) {
                cycles.push_back(path);
            }
        } else if (neighbor > start && !visited[neighbor]) {
            visited[neighbor] = true;
            path.push_back(neighbor);
            dfsSimpleCycles(g, start, neighbor, path, visited, cycles);
            path.pop_back();
            visited[neighbor] = false;
        }
    }
}

vector<vector<int>> allSimpleCycles(const Graph& g) {
    int n = g.size();
    vector<vector<int>> cycles;
    vector<bool> visited(n, false);

    for (int start = 0; start < n; ++start) {
        vector<int> path = {start};
        visited[start] = true;
        dfsSimpleCycles(g, start, start, path, visited, cycles);
        visited[start] = false;
    }
    return cycles;
}

// ---------- 動作確認 ----------
void printCycles(const vector<vector<int>>& cycles) {
    for (auto& c : cycles) {
        cout << "[";
        for (size_t i = 0; i < c.size(); ++i) {
            cout << c[i] << (i + 1 < c.size() ? ", " : "");
        }
        cout << "]\n";
    }
}

int main() {
    // 例: 頂点 0-4
    //     0-1, 1-2, 2-0 で三角形
    //     2-3, 3-4, 4-2 でもう1つの三角形（頂点2を共有）
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,0}, {2,3}, {3,4}, {4,2}};
    Graph g = buildGraph(5, edges);

    cout << "=== 基本閉路（サイクル空間の基底） ===\n";
    printCycles(fundamentalCycles(g));

    cout << "\n=== 全単純閉路 ===\n";
    printCycles(allSimpleCycles(g));

    return 0;
}
