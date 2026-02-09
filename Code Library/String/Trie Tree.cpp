/**
 * Trie木（接頭辞木）テンプレート
 * * 使い方:
 * 1. MAX_NODES を「全単語の合計文字数 + 1」以上に設定する。
 * 2. trie.insert(string) で単語を追加しつつ、共通接頭辞の累積などを計算する。
 */
struct Trie {
    static const int MAX_NODES = 300005; 
    static const int ALPHABET_SIZE = 26;
    
    int next[MAX_NODES][ALPHABET_SIZE];
    int pass_cnt[MAX_NODES];
    int nodes_cnt;

    Trie() {
        nodes_cnt = 1; 
        for(int i=0; i<MAX_NODES; i++) {
            pass_cnt[i] = 0;
            for(int j=0; j<ALPHABET_SIZE; j++) next[i][j] = 0;
        }
    }

    // 単語を挿入し、挿入過程で「既に存在した共通接頭辞の長さの和」を返す
    long long insert(const string& s) {
        int curr = 0;
        long long score = 0;
        for (char c : s) {
            int x = c - 'a';
            if (next[curr][x] == 0) {
                next[curr][x] = nodes_cnt++;
            }
            curr = next[curr][x];
            score += pass_cnt[curr];
            pass_cnt[curr]++;
        }
        return score;
    }
};

// 実際の使い方の例
void solve() {
    int N;
    if (!(cin >> N)) return;

    // staticをつけるとメモリが静的に確保され、スタックオーバーフローを防げる
    static Trie t; 
    
    long long total_ans = 0;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        total_ans += t.insert(s);
    }
    cout << total_ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
