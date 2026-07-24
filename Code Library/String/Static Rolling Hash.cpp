#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

struct RollingHash {
    static const uint64_t mod = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> hash;  // 累積ハッシュ: hash[i] は S[0...i-1] のハッシュ
    vector<uint64_t> power; // 基数のべき乗テーブル

    // 2^61-1 を法とする高速な乗算
    inline uint64_t multiply(uint64_t a, uint64_t b) const {
        unsigned __int128 c = (unsigned __int128)a * b;
        uint64_t res = (c >> 61) + (c & mod);
        if (res >= mod) res -= mod;
        return res;
    }

    // コンストラクタ: 前計算を O(N) で行う
    RollingHash(const string& s, uint64_t base) : base(base) {
        int n = s.size();
        hash.assign(n + 1, 0);
        power.assign(n + 1, 1);

        for (int i = 0; i < n; i++) {
            // べき乗の計算
            power[i + 1] = multiply(power[i], base);
            
            // 累積ハッシュの計算: hash[i+1] = hash[i] * base + s[i]
            uint64_t next_h = multiply(hash[i], base) + (uint64_t)s[i];
            if (next_h >= mod) next_h -= mod;
            hash[i + 1] = next_h;
        }
    }

    // 区間 [l, r) のハッシュ値を O(1) で取得
    uint64_t get(int l, int r) const {
        uint64_t res = hash[r] + mod - multiply(hash[l], power[r - l]);
        if (res >= mod) res -= mod;
        return res;
    }
};

// 安全な基数をランダム生成する関数
uint64_t generate_base() {
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<uint64_t> rand(2, RollingHash::mod - 2);
    return rand(eng);
}

int main() {
    string S = "abracadabra";
    uint64_t base = generate_base();
    
    RollingHash srh(S, base);
    
    // "bra" のハッシュ (区間 [1, 4))
    uint64_t hash_bra1 = srh.get(1, 4);
    // 後方の "bra" のハッシュ (区間 [8, 11))
    uint64_t hash_bra2 = srh.get(8, 11);
    
    cout << "Hash of first 'bra': " << hash_bra1 << endl;
    cout << "Hash of second 'bra': " << hash_bra2 << endl;
    
    if (hash_bra1 == hash_bra2) {
        cout << "Match!" << endl;
    } else {
        cout << "Mismatch!" << endl;
    }
    
    return 0;
}
