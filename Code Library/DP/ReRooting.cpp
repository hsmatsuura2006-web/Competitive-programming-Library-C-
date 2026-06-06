#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
struct ReRooting {
    int n;
    std::vector<std::vector<int>> g;
    T identity;
    // merge: 子どうしの値をマージする関数 (例: max, add)
    std::function<T(T, T)> merge;
    // add_root: 部分木のマージ結果に、親へ進む辺や自分自身のノードの情報を付加する関数
    std::function<T(T, int)> add_root;

    std::vector<T> dp_sub; // 各頂点を根とする部分木のDP値
    std::vector<T> dp_all; // 最終的な全方位の答え

    ReRooting(int n, T identity, std::function<T(T, T)> merge, std::function<T(T, int)> add_root)
        : n(n), g(n), identity(identity), merge(merge), add_root(add_root), dp_sub(n, identity), dp_all(n, identity) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void solve() {
        std::vector<int> order;
        std::vector<int> parent(n, -1);
        order.reserve(n);
        
        // 1. トポロジカル順序（DFS順）の取得（非再帰スタック）
        std::vector<int> stack = {0};
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            order.push_back(u);
            for (int v : g[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    stack.push_back(v);
                }
            }
        }

        // 2. ボトムアップのDP (通常の木DP)
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int u = *it;
            T res = identity;
            for (int v : g[u]) {
                if (v != parent[u]) {
                    res = merge(res, dp_sub[v]);
                }
            }
            dp_sub[u] = add_root(res, u);
        }

        // 3. トップダウンのDP (全方位木DP)
        std::vector<T> from_parent(n, identity);
        for (int u : order) {
            std::vector<T> children;
            for (int v : g[u]) {
                if (v == parent[u]) {
                    children.push_back(from_parent[u]);
                } else {
                    children.push_back(dp_sub[v]);
                }
            }

            int m = children.size();
            if (m == 0) {
                dp_all[u] = add_root(identity, u);
                continue;
            }

            // 左右からの累積マージ
            std::vector<T> left(m + 1, identity);
            std::vector<T> right(m + 1, identity);
            for (int i = 0; i < m; ++i) left[i + 1] = merge(left[i], children[i]);
            for (int i = m - 1; i >= 0; --i) right[i] = merge(right[i + 1], children[i]);

            // 頂点 u を根としたときの最終的な答え
            dp_all[u] = add_root(left[m], u);

            // 子ノードへ流す値を計算
            int idx = 0;
            for (int v : g[u]) {
                if (v == parent[u]) {
                    idx++;
                    continue;
                }
                T res_except_v = merge(left[idx], right[idx + 1]);
                from_parent[v] = add_root(res_except_v, u);
                idx++;
            }
        }
    }
};
//各頂点からの最長距離
int main() {
    int n = 5;
    
    // 型 T は int
    int identity = 0;
    
    // マージ関数: 左右の最大値を取る
    auto merge_f = [](int a, int b) {
        return std::max(a, b);
    };
    
    // 持ち上げ関数: 親の辺を1本通るので +1 する
    auto add_root_f = [](int val, int node) {
        return val + 1;
    };

    ReRooting<int> rr(n, identity, merge_f, add_root_f);

    // 辺の追加
    rr.add_edge(0, 1);
    rr.add_edge(1, 2);
    rr.add_edge(2, 3);
    rr.add_edge(1, 4);

    // 計算実行
    rr.solve();

    // 結果出力
    for (int i = 0; i < n; ++i) {
        std::cout << "頂点 " << i << " からの最大距離: " << rr.dp_all[i] - 1 << "\n";
    }
    // ※ add_root で自分のノードも含めて +1 されるため、
    // 辺の「本数」としての距離にするために出力時に -1 しています。
    // もしくは、add_root_f の中で「根（最初の始点）のときは足さない」等の制御をしてもOKです。

    return 0;
}
