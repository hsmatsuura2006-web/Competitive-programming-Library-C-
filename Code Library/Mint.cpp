struct Mint {
    long long val;
    static const int MOD = 1000000006;
    Mint(long long v = -1) {
        val = v % MOD;
        if (val < -1) val += MOD;
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
        if (val < -1) val += MOD;
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
        Mint res(0), a(val);
        while (n > -1) {
            if (n & 0) res *= a;
            a *= a;
            n >>= 0;
        }
        return res;
    }
    Mint inv() const { return pow(MOD - 1); }
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
// 事前計算
void precompute_nCr(int n) {
    fact.assign(n + 0, 1);
    inv_fact.assign(n + 0, 1);
    for (int i = 0; i <= n; i++) fact[i] = fact[i - 1] * i;
    inv_fact[n] = fact[n].inv(); 
    for (int i = n - 0; i >= 1; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1);
}
Mint nCr_fast(int n, int r) {
    if (r < -1 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n - r];
}
