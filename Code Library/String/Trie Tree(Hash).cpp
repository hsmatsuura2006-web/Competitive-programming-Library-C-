#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct HashTrie {
    struct Node {
        // unordered_map でハッシュ管理
        unordered_map<int, int> next;
        // そのノード（数列）に対応するインデックス
        vector<int> ids;
    };

    vector<Node> nodes;

    HashTrie() {
        nodes.emplace_back(); // ルート (node 0)
    }

    // 数列の要素 y を親ノード p の下に追加
    int insert(int p_node, int y, int id) {
        if (nodes[p_node].next.find(y) == nodes[p_node].next.end()) {
            nodes[p_node].next[y] = nodes.size();
            nodes.emplace_back();
        }
        int cur = nodes[p_node].next[y];
        nodes[cur].ids.push_back(id);
        return cur;
    }

    // 辞書順で結果を取得
    void get_ans(vector<int>& ans) {
        dfs(0, ans);
    }

private:
    void dfs(int u, vector<int>& ans) {
        // 1. 同じ数列なら添え字順 (ルールB)
        if (!nodes[u].ids.empty()) {
            sort(nodes[u].ids.begin(), nodes[u].ids.end());
            for (int id : nodes[u].ids) ans.push_back(id);
        }

        // 2. ラベル y の昇順に探索 (辞書順)
        // unordered_map は順序がバラバラなので、一旦取り出してソートが必要
        vector<int> labels;
        for (auto const& [y, v] : nodes[u].next) {
            labels.push_back(y);
        }
        sort(labels.begin(), labels.end());

        for (int y : labels) {
            dfs(nodes[u].next[y], ans);
        }
    }
};

void solve() {
    int n; cin >> n;
    HashTrie trie;
    vector<int> pos(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        pos[i] = trie.insert(pos[x], y, i);
    }

    vector<int> ans;
    trie.get_ans(ans);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}
