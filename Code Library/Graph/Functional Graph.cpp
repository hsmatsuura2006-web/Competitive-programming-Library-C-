/**
 * Functional Graph の閉路抽出
 * @param next_node: 各頂点の遷移先
 * @return cycles: 各閉路を構成する頂点リストの集合
 * @return is_cycle_member: 各頂点が閉路に属するかどうかのフラグ
 */
struct FunctionalGraph {
    int n;
    std::vector<int> next_node;
    std::vector<std::vector<int>> cycles;
    std::vector<bool> is_cycle_member;

    FunctionalGraph(const std::vector<int>& next) : n(next.size()), next_node(next), is_cycle_member(n, true) {
        std::vector<int> in_degree(n, 0);
        for (int i = 0; i < n; ++i) in_degree[next_node[i]]++;

        // 1. トポロジカルソートで閉路以外の枝を削除
        std::queue<int> que;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) que.push(i);
        }

        while (!que.empty()) {
            int v = que.front();
            que.pop();
            is_cycle_member[v] = false; // 枝なので閉路ではない
            int nv = next_node[v];
            if (--in_degree[nv] == 0) que.push(nv);
        }

        // 2. 閉路の抽出
        std::vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!is_cycle_member[i] || visited[i]) continue;
            
            std::vector<int> cycle;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle.push_back(curr);
                curr = next_node[curr];
            }
            cycles.push_back(cycle);
        }
    }
};
