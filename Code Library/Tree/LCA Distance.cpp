#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
using P = pair<long long, int>; // {depth, node_id}
P op(P a, P b) { return min(a, b); }
P e() { return {(ll)1e18, -1}; }
struct SegmentTree {
    int n;
    vector<P> tree;
    SegmentTree(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        tree.assign(2 * n, e());
    }
    void build(const vector<P>& data) {
        int sz = data.size();
        for (int i = 0; i < sz; i++) tree[n + i] = data[i];
        for (int i = n - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    P query(int l, int r) {
        P res_l = e(), res_r = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_l = op(res_l, tree[l++]);
            if (r & 1) res_r = op(tree[--r], res_r);
        }
        return op(res_l, res_r);
    }
};
struct Edge {
    int to;
    ll cost;
};
struct EulerTourLCA {
    vector<int> first_pos;
    vector<ll> dist_from_root;
    vector<int> depths; // 各ノードの深さ
    SegmentTree st;

    EulerTourLCA(int n, const vector<vector<Edge>>& adj, int root = 0) 
        : first_pos(n, -1), dist_from_root(n, 0), depths(n, 0), st(2 * n) {
        
        vector<P> tour_data;
        tour_data.reserve(2 * n);
        
        int timer = 0;
        dfs(root, -1, 0, 0, adj, tour_data);
        
        st.build(tour_data);
    }

    void dfs(int u, int p, int d, ll current_dist, const vector<vector<Edge>>& adj, vector<P>& tour_data) {
        first_pos[u] = tour_data.size();
        depths[u] = d;
        dist_from_root[u] = current_dist;
        tour_data.push_back({d, u});

        for (auto& edge : adj[u]) {
            if (edge.to != p) {
                dfs(edge.to, u, d + 1, current_dist + edge.cost, adj, tour_data);
                tour_data.push_back({d, u}); 
            }
        }
    }

    int get_lca(int u, int v) {
        int l = first_pos[u], r = first_pos[v];
        if (l > r) swap(l, r);
        return st.query(l, r + 1).second;
    }

    ll get_dist(int u, int v) {
        int lca = get_lca(u, v);
        return dist_from_root[u] + dist_from_root[v] - 2 * dist_from_root[lca];
    }
};
int main() {
    int N; cin >> N;
    vector<vector<Edge>> adj(N);
    for(int i = 0; i < N-1; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; u--; v--; // 0-indexedにする場合
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    EulerTourLCA lca_machine(N, adj);

    int Q; cin >> Q;
    while(Q--) {
        int u, v; cin >> u >> v; u--; v--;
        cout << lca_machine.get_dist(u, v) << "\n";
    }
}
