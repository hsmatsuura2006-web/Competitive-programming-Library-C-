template <typename T>
struct Edge {
    int to;
    T cost;
};

template <typename T>
using Graph = std::vector<std::vector<Edge<T>>>;

template <typename T>
struct DijkstraResult {
    std::vector<T> dists;
    std::vector<int> prevs; // 経路復元用：直前の頂点

    // 始点から終点 goal までの最短経路を復元する
    std::vector<int> get_path(int goal) const {
        std::vector<int> path;
        for (int v = goal; v != -1; v = prevs[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
};

template <typename T>
DijkstraResult<T> dijkstra(const Graph<T> &G, int s) {
    const T INF = std::numeric_limits<T>::max();
    int N = G.size();
    
    DijkstraResult<T> res;
    res.dists.assign(N, INF);
    res.prevs.assign(N, -1);
    
    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    res.dists[s] = 0;
    pq.emplace(res.dists[s], s);

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (res.dists[v] < d) continue;

        for (const auto &e : G[v]) {
            if (res.dists[e.to] > res.dists[v] + e.cost) {
                res.dists[e.to] = res.dists[v] + e.cost;
                res.prevs[e.to] = v;
                pq.emplace(res.dists[e.to], e.to);
            }
        }
    }
    return res;
}
