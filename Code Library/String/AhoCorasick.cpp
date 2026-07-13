// aho_corasick.hpp
// DP / 数え上げに使いやすいことを重視した汎用 Aho-Corasick ライブラリ
//
// 特徴:
//   - build() 時に「状態 x 文字」の完全遷移表(goto関数)をBFSで構築 → 遷移は O(1)
//   - 各状態に fail リンク経由の情報を累積済みなので「危険な状態か」を O(1) で判定可能
//   - パターン数が 64 個以下なら bitmask で「どのパターンにマッチしたか」も追跡できる
//   - 状態数 V が確定するので、そのまま DP の次元や行列累乗の行列サイズとして使える
//
// 想定する使い方:
//   AhoCorasick<26> ac;
//   for (auto &s : patterns) ac.add(s);
//   ac.build();
//   int V = ac.size();
//   // dp[state] を持って ac.move(state, c) で遷移するだけ

#include <bits/stdc++.h>
using namespace std;

template <int CHAR_SIZE = 26, char BASE = 'a'>
struct AhoCorasick {
    struct Node {
        array<int, CHAR_SIZE> next; // 完全遷移表 (goto). build後は必ず有効な状態番号が入る
        int fail = 0;               // fail リンク (build 後にのみ有効な値、外部からは基本使わない)
        int cnt = 0;                // このノードで "終端になっているパターンの個数"
                                     // fail 経由の祖先の分も累積済み
        uint64_t mask = 0;          // どのパターン(id)にマッチしたか。id < 64 のときのみ有効
        Node() { next.fill(-1); }
    };

    vector<Node> nodes;
    bool built = false;

    AhoCorasick() { nodes.emplace_back(); }

    // パターン文字列を追加。 id はそのパターンの識別子 (0-indexed, mask を使うなら 64 未満推奨)
    // 戻り値: このパターンが終端となるノード番号 (必要なら記録しておくと後で使える)
    int add(const string &s, int id = -1) {
        int cur = 0;
        for (char c : s) {
            int ci = idx(c);
            if (nodes[cur].next[ci] == -1) {
                nodes[cur].next[ci] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].next[ci];
        }
        nodes[cur].cnt += 1;
        if (id >= 0 && id < 64) nodes[cur].mask |= (1ULL << id);
        return cur;
    }

    // fail リンクの構築 + 完全遷移表の構築 + cnt/mask の累積
    void build() {
        queue<int> q;
        for (int c = 0; c < CHAR_SIZE; c++) {
            if (nodes[0].next[c] == -1) {
                nodes[0].next[c] = 0; // root からの未定義遷移は root へ
            } else {
                nodes[nodes[0].next[c]].fail = 0;
                q.push(nodes[0].next[c]);
            }
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            // fail 先の情報を引き継ぐ (これで「祖先パターンを含むか」が O(1) 判定可能になる)
            nodes[v].cnt += nodes[nodes[v].fail].cnt;
            nodes[v].mask |= nodes[nodes[v].fail].mask;
            for (int c = 0; c < CHAR_SIZE; c++) {
                int u = nodes[v].next[c];
                if (u == -1) {
                    // 子が無いなら fail 先の遷移をコピー (goto の完全化)
                    nodes[v].next[c] = nodes[nodes[v].fail].next[c];
                } else {
                    nodes[u].fail = nodes[nodes[v].fail].next[c];
                    q.push(u);
                }
            }
        }
        built = true;
    }

    // 状態 state から文字 c ('a' や 'A' など、実際の文字) で遷移した先の状態番号。 O(1)
    inline int move(int state, char c) const {
        return nodes[state].next[idx(c)];
    }

    // 状態 state から 添字 ci (0 ~ CHAR_SIZE-1) で遷移した先の状態番号。 O(1)
    // DPループを for (int c = 0; c < CHAR_SIZE; c++) で回したい場合はこちらを使う。
    // (move() に誤って添字をそのまま char として渡すと BASE 分ずれてバグるので注意)
    inline int move_by_index(int state, int ci) const {
        return nodes[state].next[ci];
    }

    // その状態が「何らかのパターンを含んでしまっている(=危険な状態)」かどうか
    inline bool is_matched(int state) const {
        return nodes[state].cnt > 0;
    }

    // その状態でマッチしているパターンの数 (fail 経由込み)
    inline int match_count(int state) const {
        return nodes[state].cnt;
    }

    // その状態でマッチしているパターン id の bitmask (id < 64 の場合のみ有効)
    inline uint64_t match_mask(int state) const {
        return nodes[state].mask;
    }

    inline int size() const { return (int)nodes.size(); } // 状態数 V

private:
    static inline int idx(char c) { return c - BASE; }
};

/* ============================================================
   使用例 1: 長さ N の文字列で、与えられたパターンを1つも
             部分文字列として含まないものの個数 (mod付き)
   ============================================================
   AhoCorasick<26> ac;
   for (auto &s : patterns) ac.add(s);
   ac.build();
   int V = ac.size();
   vector<long long> dp(V, 0), ndp;
   dp[0] = 1;
   for (int i = 0; i < N; i++) {
       ndp.assign(V, 0);
       for (int v = 0; v < V; v++) {
           if (!dp[v]) continue;
           for (int c = 0; c < 26; c++) {
               int u = ac.move_by_index(v, c); // 添字ループなので move_by_index を使う
               if (ac.is_matched(u)) continue; // 危険な状態には遷移しない
               ndp[u] = (ndp[u] + dp[v]) % MOD;
           }
       }
       dp.swap(ndp);
   }
   long long ans = 0;
   for (auto x : dp) ans = (ans + x) % MOD;

   ============================================================
   使用例 2: N が非常に大きい (例えば 10^9) 場合
             → 行列累乗で高速化 (O(V^3 log N))
   ============================================================
   V x V 行列 T を作る:
     T[v][u] += 1  ( u = ac.move(v, c) かつ !ac.is_matched(u) となる c ごとに )
   危険状態については自己ループ ( T[dead][dead] = 1 ) にしておくと吸収状態として扱える。
   初期ベクトルは state 0 のみ 1 として、 T^N を掛ければ良い。

   ============================================================
   使用例 3: 「ちょうど1つのパターンを含む」「特定のパターンの
             組み合わせを含む」など、bitmask を使った拡張
   ============================================================
   dp の次元を (state, これまでに出現したパターンの mask) に拡張し、
   遷移時に ac.match_mask(u) を OR していけば良い。
   パターン数が少ない (<=15程度) 桁DP系の問題でよく使う形。
*/
