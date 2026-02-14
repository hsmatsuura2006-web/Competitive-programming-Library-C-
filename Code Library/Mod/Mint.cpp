#include <iostream>
#include <vector>

using namespace std;

struct Mint {
    long long val;
    static const int MOD = 998244353;
    Mint(long long v = 0) {
        val = v % MOD;
        if (val < 0) val += MOD;
    }

    bool operator==(const Mint& other) const { return val == other.val; }
    bool operator!=(const Mint& other) const { return val != other.val; }
    
    Mint operator-() const { return Mint(-val); }

    Mint& operator+=(const Mint& other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }

    Mint& operator-=(const Mint& other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    Mint& operator*=(const Mint& other) {
        val = val * other.val % MOD;
        return *this;
    }

    Mint operator+(const Mint& other) const { return Mint(*this) += other; }
    Mint operator-(const Mint& other) const { return Mint(*this) -= other; }
    Mint operator*(const Mint& other) const { return Mint(*this) *= other; }

    Mint pow(long long n) const {
        Mint res(1), a(val);
        while (n > 0) {
            if (n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    Mint inv() const { return pow(MOD - 2); }

    Mint& operator/=(const Mint& other) { return *this *= other.inv(); }
    Mint operator/(const Mint& other) const { return Mint(*this) /= other; }
};

ostream& operator<<(ostream& os, const Mint& m) { return os << m.val; }
istream& operator>>(istream& is, Mint& m) {
    long long v;
    is >> v;
    m = Mint(v);
    return is;
}
vector<Mint> fact, inv_fact;
// nCrの前計算
void precompute_nCr(int n) {
    fact.assign(n + 1, 1);
    inv_fact.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    inv_fact[n] = fact[n].inv();
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1);
}

// nCrの計算
Mint nCr_fast(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n - r];
}
