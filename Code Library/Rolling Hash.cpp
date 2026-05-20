#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

struct RollingHash {
    static const uint64_t mod = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> hash, power;

    // 2^61-1 を法とする高速な乗算
    inline uint64_t multiply(uint64_t a, uint64_t b) const {
        unsigned __int128 c = (unsigned __int128)a * b;
        uint64_t res = (c >> 61) + (c & mod);
        if (res >= mod) res -= mod;
        return res;
    }

    // コンストラクタ（文字列と基数を受け取る）
    // 基数が指定されない場合はデフォルト値を使用（実戦ではランダム生成を推奨）
    RollingHash(const string &s, uint64_t base = 10007) : base(base) {
        int n = s.size();
        hash.assign(n + 1, 0);
        power.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = multiply(hash[i], base) + s[i];
            if (hash[i + 1] >= mod) hash[i + 1] -= mod;
            power[i + 1] = multiply(power[i], base);
        }
    }

    // 文字列の [l, r) のハッシュ値を O(1) で取得 (0-indexed)
    uint64_t get(int l, int r) const {
        uint64_t res = hash[r] + mod - multiply(hash[l], power[r - l]);
        if (res >= mod) res -= mod;
        return res;
    }

    // ハッシュ値 h1 (長さ h1_len) とハッシュ値 h2 を結合
    uint64_t connect(uint64_t h1, uint64_t h2, int h2_len) const {
        uint64_t res = multiply(h1, power[h2_len]) + h2;
        if (res >= mod) res -= mod;
        return res;
    }
};

// 基数（Base）をランダムに生成する関数（ハック対策）
uint64_t generate_base() {
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<uint64_t> rand(2, RollingHash::mod - 2);
    return rand(eng);
}
