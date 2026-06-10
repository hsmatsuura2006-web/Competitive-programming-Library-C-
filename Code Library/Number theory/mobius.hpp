#pragma once
/**
 * mobius.hpp — メビウス関数ライブラリ
 *
 * 提供する機能:
 *  - mobius(n)          : μ(n) を単体計算
 *  - MobiusSieve        : 篩で μ(1)…μ(N) を一括計算
 *  - mobius_sum(n)      : Σ_{k=1}^{n} μ(k)（Mertens 関数）
 *  - mobius_inversion   : Möbius 反転公式のユーティリティ
 *  - squarefree(n)      : n が square-free かどうかの判定
 */

#include <vector>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <functional>
#include <cassert>

namespace mobius_lib {

// ─────────────────────────────────────────────
//  1. 単体計算  O(√n)
// ─────────────────────────────────────────────

/**
 * @brief μ(n) を計算する。
 *
 * μ(n) =  1  : n = 1
 *         0  : n が平方因子を持つ
 *       (-1)^k : n が k 個の相異なる素因子の積
 *
 * @param n 正の整数
 * @return int  1, 0, または -1
 */
inline int mobius(long long n) {
    if (n <= 0) throw std::domain_error("mobius: n must be a positive integer");
    if (n == 1) return 1;

    int factor_count = 0;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            ++factor_count;
            n /= p;
            if (n % p == 0) return 0;   // p^2 | 元の n
        }
    }
    if (n > 1) ++factor_count;           // 残った素因子
    return (factor_count % 2 == 0) ? 1 : -1;
}

/**
 * @brief n が square-free（平方因子を持たない）かを返す。
 */
inline bool squarefree(long long n) {
    return mobius(n) != 0;
}

// ─────────────────────────────────────────────
//  2. 篩による一括計算  O(N log log N)
// ─────────────────────────────────────────────

/**
 * @brief 線形篩で μ(1)…μ(N) を計算するクラス。
 *
 * 構築後は operator[] でアクセス可能。
 * また Mertens 関数 M(n) = Σ_{k=1}^{n} μ(k) も提供する。
 */
class MobiusSieve {
public:
    /**
     * @param N  上限値（1 以上）
     */
    explicit MobiusSieve(int N) : N_(N), mu_(N + 1, 0), mertens_(N + 1, 0) {
        if (N < 1) throw std::invalid_argument("MobiusSieve: N must be >= 1");
        compute();
    }

    /** μ(n) を返す（1 ≤ n ≤ N）*/
    int operator[](int n) const {
        check(n);
        return mu_[n];
    }

    /** Mertens 関数 M(n) = Σ_{k=1}^{n} μ(k) を返す */
    long long mertens(int n) const {
        check(n);
        return mertens_[n];
    }

    /** 上限値を返す */
    int upper_bound() const { return N_; }

    /** μ の配列全体を返す（index 0 は未使用）*/
    const std::vector<int>& data() const { return mu_; }

private:
    int N_;
    std::vector<int>  mu_;
    std::vector<long long> mertens_;

    void check(int n) const {
        if (n < 1 || n > N_)
            throw std::out_of_range("MobiusSieve: index out of range");
    }

    void compute() {
        // 線形篩（最小素因子 spf を使う方法）
        std::vector<int> spf(N_ + 1, 0);   // smallest prime factor
        mu_[1] = 1;

        std::vector<int> primes;
        primes.reserve(static_cast<int>(N_ / std::log(N_ + 2) * 1.2));

        for (int i = 2; i <= N_; ++i) {
            if (spf[i] == 0) {             // i は素数
                spf[i] = i;
                mu_[i] = -1;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf[i] || static_cast<long long>(i) * p > N_) break;
                spf[i * p] = p;
                if (i % p == 0) {
                    mu_[i * p] = 0;        // p^2 | i*p
                } else {
                    mu_[i * p] = -mu_[i];
                }
            }
        }

        // Mertens 関数の前置和
        mertens_[0] = 0;
        for (int i = 1; i <= N_; ++i)
            mertens_[i] = mertens_[i - 1] + mu_[i];
    }
};

// ─────────────────────────────────────────────
//  3. Möbius 反転公式ユーティリティ
// ─────────────────────────────────────────────

/**
 * @brief Möbius 反転（加法版）
 *
 * g(n) = Σ_{d|n} f(d)  が与えられたとき
 * f(n) = Σ_{d|n} μ(n/d) g(d)  を計算する。
 *
 * @tparam T  値の型（int, long long, double など）
 * @param g   入力配列（index 1 始まり、サイズ N+1）
 * @param sieve  MobiusSieve（サイズ ≥ N）
 * @return f の配列（index 1 始まり）
 */
template <typename T>
std::vector<T> mobius_inversion(const std::vector<T>& g, const MobiusSieve& sieve) {
    int N = static_cast<int>(g.size()) - 1;
    if (N < 1) throw std::invalid_argument("mobius_inversion: g must have size >= 2");
    if (sieve.upper_bound() < N)
        throw std::invalid_argument("mobius_inversion: sieve too small");

    // f(n) = Σ_{d|n} μ(n/d) * g(d)
    // d を固定すると n = d*k なので μ(k)*g(d) を f[d*k] に加算
    std::vector<T> f(N + 1, T{});
    for (int d = 1; d <= N; ++d) {
        for (int k = 1; static_cast<long long>(d) * k <= N; ++k) {
            if (sieve[k] == 0) continue;
            f[d * k] += static_cast<T>(sieve[k]) * g[d];
        }
    }
    return f;
}

/**
 * @brief Dirichlet 畳み込みの逆（除法版）
 *
 * h = f * g（Dirichlet 積）のとき、g が既知なら f を求める。
 * h(n) = Σ_{d|n} f(d) g(n/d)
 *
 * @tparam T  値の型
 * @param h   ターゲット配列（index 1 始まり）
 * @param g   既知の関数配列（g[1] ≠ 0 が必要）
 * @return f の配列（index 1 始まり）
 */
template <typename T>
std::vector<T> dirichlet_inverse(const std::vector<T>& h,
                                 const std::vector<T>& g) {
    int N = static_cast<int>(h.size()) - 1;
    if (g[1] == T{}) throw std::invalid_argument("dirichlet_inverse: g[1] must be non-zero");

    std::vector<T> f(N + 1, T{});
    for (int n = 1; n <= N; ++n) {
        f[n] = h[n];
        for (int d = 2; d <= n; ++d) {
            if (n % d == 0) f[n] -= f[n / d] * g[d];
        }
        f[n] /= g[1];
    }
    return f;
}

// ─────────────────────────────────────────────
//  4. 便利な集計関数
// ─────────────────────────────────────────────

/**
 * @brief μ(n) の部分和（Mertens 関数）を素朴に計算する。
 *        小さな n 向け。大きな n には MobiusSieve を使うこと。
 */
inline long long mertens_naive(long long n) {
    long long s = 0;
    for (long long k = 1; k <= n; ++k) s += mobius(k);
    return s;
}

/**
 * @brief n 以下の square-free な整数の個数を MobiusSieve で数える。
 */
inline int count_squarefree(const MobiusSieve& sieve, int n) {
    int cnt = 0;
    for (int k = 1; k <= n; ++k)
        if (sieve[k] != 0) ++cnt;
    return cnt;
}

/**
 * @brief φ(n)（Euler のトーシェント関数）を μ から計算する。
 *        φ(n) = Σ_{d|n} μ(d) * (n/d)
 */
inline long long euler_totient_from_mobius(long long n) {
    // 直接 μ を使って計算
    long long phi = 0;
    for (long long d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            phi += static_cast<long long>(mobius(d)) * (n / d);
            if (d != n / d)
                phi += static_cast<long long>(mobius(n / d)) * d;
        }
    }
    return phi;
}

} // namespace mobius_lib
