// ternary_search.hpp
//
// 単峰性(unimodal)関数に対する三分探索ライブラリ
//   - 実数区間版: 下に凸/上に凸な連続関数の最小値・最大値を与える x を探索
//   - 整数区間版: 下に凸/上に凸な離散関数の最小値・最大値を与える整数 x を探索
//
// 使い方は example.cpp を参照してください。
//
// ライセンス: パブリックドメイン相当(自由に改変・利用してください)

#ifndef TERNARY_SEARCH_HPP
#define TERNARY_SEARCH_HPP

#include <type_traits>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <limits>

namespace tsearch {

// ============================================================
// 実数区間に対する三分探索 (連続な単峰関数)
// ============================================================

// 下に凸な関数 f の [lo, hi] における最小値を与える x を返す。
//   f  : T -> 比較可能な値 を返す呼び出し可能オブジェクト(関数, ラムダ等)
//   eps: 探索を打ち切る区間幅の許容誤差
//   iter: 反復回数の上限(eps に達する前に打ち切る安全弁)
template <typename F, typename T>
T minimize(F f, T lo, T hi, T eps = static_cast<T>(1e-9), int iter = 200) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    for (int i = 0; i < iter && (hi - lo) > eps; ++i) {
        T m1 = lo + (hi - lo) / 3;
        T m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    return (lo + hi) / 2;
}

// 上に凸な関数 f の [lo, hi] における最大値を与える x を返す。
template <typename F, typename T>
T maximize(F f, T lo, T hi, T eps = static_cast<T>(1e-9), int iter = 200) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    auto neg_f = [&f](T x) { return -f(x); };
    return minimize<decltype(neg_f), T>(neg_f, lo, hi, eps, iter);
}

// 反復回数を固定して打ち切りたい場合の版(eps を使わない)。
// 誤差 <= (hi-lo) * (2/3)^iter 程度に収束する。
template <typename F, typename T>
T minimize_fixed_iter(F f, T lo, T hi, int iter = 100) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    for (int i = 0; i < iter; ++i) {
        T m1 = lo + (hi - lo) / 3;
        T m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    return (lo + hi) / 2;
}

template <typename F, typename T>
T maximize_fixed_iter(F f, T lo, T hi, int iter = 100) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be a floating point type");
    auto neg_f = [&f](T x) { return -f(x); };
    return minimize_fixed_iter<decltype(neg_f), T>(neg_f, lo, hi, iter);
}

// ============================================================
// 整数区間に対する三分探索 (離散な単峰関数)
// ============================================================
//
// f(lo), f(lo+1), ..., f(hi) が「狭義単調減少 → 狭義単調増加」
// (下に凸)、あるいは同値が連続するだけの緩い凸性を持つ場合に対応。
// 最後に残った小区間(高々数点)は線形探索で確定させるため厳密に正しい。

template <typename F>
long long minimize_int(F f, long long lo, long long hi) {
    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    long long best = lo;
    for (long long x = lo + 1; x <= hi; ++x) {
        if (f(x) < f(best)) best = x;
    }
    return best;
}

template <typename F>
long long maximize_int(F f, long long lo, long long hi) {
    auto neg_f = [&f](long long x) { return -f(x); };
    return minimize_int<decltype(neg_f)>(neg_f, lo, hi);
}

} // namespace tsearch

#endif // TERNARY_SEARCH_HPP
