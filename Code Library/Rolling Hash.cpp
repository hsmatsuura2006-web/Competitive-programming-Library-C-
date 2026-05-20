#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// セグメント木に乗せるデータ構造
struct Node {
    uint64_t hash;
    int len;
};

struct DynamicRollingHash {
    static const uint64_t mod = (1ULL << 61) - 1;
    uint64_t base;
    int n; // 葉の数（2のべき乗）
    vector<Node> tree;
    vector<uint64_t> power;

    // 2^61-1 を法とする高速な乗算
    inline uint64_t multiply(uint64_t a, uint64_t b) const {
        unsigned __int128 c = (unsigned __int128)a * b;
        uint64_t res = (c >> 61) + (c & mod);
        if (res >= mod) res -= mod;
        return res;
    }

    // 2つの区間のハッシュを結合する（モノイドの演算）
    Node merge(const Node& left, const Node& right) const {
        if (left.len == 0) return right; // 左が単位元のとき
        if (right.len == 0) return left; // 右が単位元のとき
        
        uint64_t h = multiply(left.hash, power[right.len]) + right.hash;
        if (h >= mod) h -= mod;
        return {h, left.len + right.len};
    }

    // コンストラクタ: 文字列 S と基数を受け取ってセグメント木を構築 (O(N))
    DynamicRollingHash(const string& s, uint64_t base) : base(base) {
        int sz = s.size();
        n = 1;
        while (n < sz) n *= 2; // サイズを2のべき乗にする
        
        tree.assign(2 * n, {0, 0});
        power.assign(n + 1, 1);
        
        // 基数のべき乗を事前計算
        for (int i = 0; i < n; i++) {
            power[i + 1] = multiply(power[i], base);
        }
        
        // 葉の初期化
        for (int i = 0; i < sz; i++) {
            tree[n + i] = { (uint64_t)s[i], 1 };
        }
        
        // 下から上へ構築
        for (int i = n - 1; i > 0; i--) {
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // S[pos] の文字を c に変更（値の更新）: O(log N)
    void update(int pos, char c) {
        pos += n;
        tree[pos] = { (uint64_t)c, 1 };
        while (pos > 1) {
            pos /= 2;
            tree[pos] = merge(tree[2 * pos], tree[2 * pos + 1]);
        }
    }

    // 区間 [l, r) の Node(ハッシュ値, 長さ) を取得: O(log N)
    Node query(int l, int r) const {
        Node res_l = {0, 0}, res_r = {0, 0};
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) res_l = merge(res_l, tree[l++]);
            if (r & 1) res_r = merge(tree[--r], res_r);
        }
        return merge(res_l, res_r);
    }
    
    // 区間 [l, r) のハッシュ値のみを取得
    uint64_t get(int l, int r) const {
        return query(l, r).hash;
    }
};

uint64_t generate_base() {
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<uint64_t> rand(2, DynamicRollingHash::mod - 2);
    return rand(eng);
}

int main() {
    string S = "abracadabra";
    uint64_t base = generate_base();
    
    DynamicRollingHash drh(S, base);
    
    // "abra" のハッシュを取得
    uint64_t hash_before = drh.get(0, 4);
    cout << "Before update: " << hash_before << endl;
    
    // S[2] を 'r' -> 'x' に変更（1点更新）
    // S は "abxacadabra" になる
    drh.update(2, 'x');
    
    // 更新後の "abxa" のハッシュを取得
    uint64_t hash_after = drh.get(0, 4);
    cout << "After update: " << hash_after << endl;
    
    return 0;
}
