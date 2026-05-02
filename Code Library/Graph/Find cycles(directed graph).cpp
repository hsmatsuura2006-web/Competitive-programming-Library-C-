/**
 * 有向グラフのサイクルに含まれる頂点を1つ分列挙する
 * 戻り値: サイクルの頂点リスト（サイクルがない場合は空のvector）
 */
vector<ll> find_cycle_directed(const vector<vector<ll>>& G) {
    ll N = G.size();
    vector<int> state(N, 0); // 0:未, 1:中, 2:済
    vector<ll> history;      // 現在の探索パスを記録
    vector<ll> cycle;

    auto dfs = [&](auto& dfs, ll u) -> bool {
        state[u] = 1;
        history.push_back(u);

        for (ll v : G[u]) {
            if (state[v] == 1) {
                // サイクル検出！ historyからサイクル部分を抽出
                auto it = find(history.begin(), history.end(), v);
                while (it != history.end()) {
                    cycle.push_back(*it);
                    ++it;
                }
                return true;
            }
            if (state[v] == 0) {
                if (dfs(dfs, v)) return true;
            }
        }

        state[u] = 2;
        history.pop_back();
        return false;
    };

    for (ll i = 0; i < N; ++i) {
        if (state[i] == 0) {
            if (dfs(dfs, i)) return cycle;
        }
    }

    return {}; // サイクルなし
}
