struct EulerTour {
    vector<int> tour;           
    vector<int> depths;       
    vector<int> first_pos;//クエリの範囲を記録  
    vector<int> last_pos;  
    vector<ll> dist_from_root;
    EulerTour(int n, const vector<vector<Edge>>& adj, int root = 0) {
				dist_from_root.assign(n, -1);
        tour.reserve(2 * n);
        depths.reserve(2 * n);
        first_pos.assign(n, -1);
        last_pos.assign(n, -1);
        dfs(root, -1, 0, adj, 0);
    }
    void dfs(int u, int p, int d, const vector<vector<Edge>>& adj, ll current_dist) {
        first_pos[u] = tour.size();
        tour.push_back(u);
        depths.push_back(d);
        dist_from_root[u] = current_dist;
        for (Edge v : adj[u]) {
            if (v.to != p) {
                dfs(v.to, u, d + 1, adj, current_dist + v.cost);
                tour.push_back(u);
                depths.push_back(d);
            }
        }
        last_pos[u] = tour.size() - 1; 
    }
};
