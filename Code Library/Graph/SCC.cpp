struct SCC {
    int n;
    std::vector<std::vector<int>> adj;     // 元のグラフ
    std::vector<std::vector<int>> rev_adj; // 逆向きグラフ
    std::vector<int> order;                // 帰りがけ順の記録
    std::vector<bool> used;
    std::vector<int> component;            // 各頂点が属する強連結成分のID
    int group_count;                       // 強連結成分の総数

    SCC(int _n) : n(_n), adj(_n), rev_adj(_n), used(_n), component(_n, -1), group_count(0) {}

    // 有向辺を追加
    void add_edge(int from, int to) {
        adj[from].push_back(to);
        rev_adj[to].push_back(from);
    }

    void dfs(int v) {
        used[v] = true;
        for (int next : adj[v]) {
            if (!used[next]) dfs(next);
        }
        order.push_back(v);
    }

    void rdfs(int v, int k) {
        component[v] = k;
        for (int next : rev_adj[v]) {
            if (component[next] == -1) rdfs(next, k);
        }
    }

    // SCCを実行
    void build() {
        std::fill(used.begin(), used.end(), false);
        order.clear();
        for (int i = 0; i < n; i++) {
            if (!used[i]) dfs(i);
        }
        std::reverse(order.begin(), order.end());
        int k = 0;
        for (int v : order) {
            if (component[v] == -1) rdfs(v, k++);
        }
        group_count = k;
    }

    // 各成分に属する頂点リストを返す
    std::vector<std::vector<int>> get_groups() {
        std::vector<std::vector<int>> groups(group_count);
        for (int i = 0; i < n; i++) {
            groups[component[i]].push_back(i);
        }
        return groups;
    }

    /**
     * @brief 凝縮グラフ (DAG) を構築する
     * @return 各SCCを一つの頂点とした隣接リスト
     */
    std::vector<std::vector<int>> build_dag() {
        std::vector<std::vector<int>> dag_adj(group_count);
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (component[u] != component[v]) {
                    dag_adj[component[u]].push_back(component[v]);
                }
            }
        }
        // 重複辺の削除
        for (int i = 0; i < group_count; i++) {
            std::sort(dag_adj[i].begin(), dag_adj[i].end());
            dag_adj[i].erase(std::unique(dag_adj[i].begin(), dag_adj[i].end()), dag_adj[i].end());
        }
        return dag_adj;
    }
};
