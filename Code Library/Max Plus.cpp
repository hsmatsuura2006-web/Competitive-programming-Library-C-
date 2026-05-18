#include <vector>
#include <iostream>
#include <cassert>

// --- 1. 演算の定義（半環 / Semiring の構造） ---
// 通常の「+」と「×」（Mod 1000000007）
struct NormalMod {
    using T = long long;
    static constexpr T MOD = 1e9 + 7;
    
    static T add(T a, T b) { return (a + b) % MOD; }
    static T mul(T a, T b) { return (a * b) % MOD; }
    static T zero() { return 0; } // 加算の単位元
    static T one() { return 1;  } // 乗算の単位元
};

// MAX-PLUS演算（最短路やDPの高速化用：「+」がmax、「×」が+）
struct MaxPlus {
    using T = long long;
    static constexpr T INF = 1e18; // 十分に小さな値（-INFの代わり）
    
    static T add(T a, T b) { return std::max(a, b); }
    static T mul(T a, T b) { return (a == -INF || b == -INF) ? -INF : a + b; }
    static T zero() { return -INF; } // maxの単位元（-INF）
    static T one() { return 0; }     // 加算（mul）の単位元（0）
};

// --- 2. 汎用行列クラス ---
template <typename Semiring>
struct Matrix {
    using T = typename Semiring::T;
    int h, w;
    std::vector<std::vector<T>> mat;

    Matrix(int h, int w) : h(h), w(w), mat(h, std::vector<T>(w, Semiring::zero())) {}
    Matrix(std::vector<std::vector<T>> v) : h(v.size()), w(v[0].size()), mat(v) {}

    // 単位行列を作成する静的関数
    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) res.mat[i][i] = Semiring::one();
        return res;
    }

    // 行列の積
    Matrix operator*(const Matrix& other) const {
        assert(w == other.h);
        Matrix res(h, other.w);
        for (int i = 0; i < h; ++i) {
            for (int k = 0; k < w; ++k) {
                for (int j = 0; j < other.w; ++j) {
                    res.mat[i][j] = Semiring::add(res.mat[i][j], Semiring::mul(mat[i][k], other.mat[k][j]));
                }
            }
        }
        return res;
    }

    // 行列累乗 A^n
    Matrix pow(long long n) const {
        assert(h == w);
        Matrix res = identity(h);
        Matrix base = *this;
        while (n > 0) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
};
