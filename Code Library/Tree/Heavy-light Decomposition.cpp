#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class FlatHLD {
public:
    int n;
    vector<int> head, parent, depth, in, out, sz, rev;
    vector<vector<int>> adj;

    FlatHLD(int n) : n(n), head(n), parent(n, -1), depth(n, 0), 
                     in(n), out(n), sz(n, 1), rev(n), adj(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        stack<pair<int, int>> st;
        st.push({root, -1});
        vector<int> order;
        while (!st.empty()) {
            auto [v, p] = st.top(); st.pop();
            order.push_back(v);
            parent[v] = p;
            for (int to : adj[v]) {
                if (to == p) continue;
                depth[to] = depth[v] + 1;
                st.push({to, v});
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            for (int& to : adj[v]) {
                if (to == parent[v]) continue;
                sz[v] += sz[to];
                if (sz[to] > sz[adj[v][0]] || adj[v][0] == parent[v]) swap(to, adj[v][0]);
            }
        }
        int timer = 0;
        st.push({root, root});
        while (!st.empty()) {
            auto [v, h] = st.top(); st.pop();
            head[v] = h;
            in[v] = timer++;
            rev[in[v]] = v;
            for (int i = (int)adj[v].size() - 1; i >= 0; --i) {
                int to = adj[v][i];
                if (to == parent[v]) continue;
                st.push({to, (i == 0 ? h : to)});
            }
        }
    }

    // パスを [l, r) の区間リストとして返す
    vector<pair<int, int>> get_path_intervals(int u, int v, bool edge = false) const {
        vector<pair<int, int>> res;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            res.push_back({in[head[u]], in[u] + 1});
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (!edge || u != v) res.push_back({in[u] + (edge ? 1 : 0), in[v] + 1});
        return res;
    }

    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            u = parent[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }
};
