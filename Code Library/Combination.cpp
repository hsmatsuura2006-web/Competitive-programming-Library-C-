#include <iostream>
#include <vector>
#include <cassert>

template <long long MOD = 998244353>
struct Combination {
private:
    std::vector<long long> fact_, inv_, fact_inv_;

    void expand(int mx) {
        int cur = fact_.size();
        if (cur > mx) return;
        int next_sz = std::max(mx + 1, cur * 2);
        
        fact_.resize(next_sz);
        inv_.resize(next_sz);
        fact_inv_.resize(next_sz);

        for (int i = cur; i < next_sz; ++i) {
            fact_[i] = fact_[i - 1] * i % MOD;
            inv_[i] = MOD - inv_[MOD % i] * (MOD / i) % MOD;
            fact_inv_[i] = fact_inv_[i - 1] * inv_[i] % MOD;
        }
    }

public:
    explicit Combination(int max_n = 200000) {
        int sz = std::max(2, max_n + 1);
        fact_.resize(sz);
        inv_.resize(sz);
        fact_inv_.resize(sz);

        fact_[0] = fact_[1] = 1;
        inv_[1] = 1;
        fact_inv_[0] = fact_inv_[1] = 1;

        for (int i = 2; i < sz; ++i) {
            fact_[i] = fact_[i - 1] * i % MOD;
            inv_[i] = MOD - inv_[MOD % i] * (MOD / i) % MOD;
            fact_inv_[i] = fact_inv_[i - 1] * inv_[i] % MOD;
        }
    }

    // 階乗 n!
    long long fact(int n) {
        if (n < 0) return 0;
        if (n >= (int)fact_.size()) expand(n);
        return fact_[n];
    }

    // 逆階乗 1 / n!
    long long fact_inv(int n) {
        if (n < 0) return 0;
        if (n >= (int)fact_inv_.size()) expand(n);
        return fact_inv_[n];
    }

    // 逆元 1 / n
    long long inv(int n) {
        if (n <= 0) return 0;
        if (n >= (int)inv_.size()) expand(n);
        return inv_[n];
    }

    // 組合せ nCk
    long long nCr(int n, int k) {
        if (n < 0 || k < 0 || n < k) return 0;
        if (n >= (int)fact_.size()) expand(n);
        return fact_[n] * fact_inv_[k] % MOD * fact_inv_[n - k] % MOD;
    }

    // 順列 nPk
    long long nPr(int n, int k) {
        if (n < 0 || k < 0 || n < k) return 0;
        if (n >= (int)fact_.size()) expand(n);
        return fact_[n] * fact_inv_[n - k] % MOD;
    }

    // 重複組合せ nHk = (n+k-1)Ck
    long long nHr(int n, int k) {
        if (n < 0 || k < 0) return 0;
        if (n == 0 && k == 0) return 1;
        return nCr(n + k - 1, k);
    }
};
