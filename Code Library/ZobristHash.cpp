// --- Zobrist Hash テンプレート開始 ---
struct ZobristHash {
    mt19937_64 engine;
    unordered_map<ll, ull> val_to_hash;

    ZobristHash() : engine(chrono::steady_clock::now().time_since_epoch().count()) {}

    // 数値に対して一意なランダム背番号を返す
    ull get_id(ll x) {
        if (val_to_hash.find(x) == val_to_hash.end()) {
            val_to_hash[x] = engine();
        }
        return val_to_hash[x];
    }

    // 配列の各地点における「集合ハッシュ」の累積配列を返す
    vector<ull> build_prefix_hashes(const vl& a) {
        int n = a.size();
        vector<ull> res(n);
        set<ll> seen;
        ull cur = 0;
        for (int i = 0; i < n; i++) {
            // 初めて登場した時だけXORをとる
            if (seen.find(a[i]) == seen.end()) {
                cur ^= get_id(a[i]);
                seen.insert(a[i]);
            }
            res[i] = cur;
        }
        return res;
    }
};
// --- Zobrist Hash テンプレート終了 ---
