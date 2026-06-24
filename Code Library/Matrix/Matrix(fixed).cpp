#include <array>
#include <initializer_list>
//セグ木に乗せる用の行列です。
template <class T, size_t H, size_t W>
struct Matrix {
    std::array<std::array<T, W>, H> A;

    // 1. デフォルトコンストラクタ（0初期化 / Mintならval=0）
    Matrix() {
        for (size_t i = 0; i < H; i++) A[i].fill(T(0));
    }

    // 2. 初期化子リストによる生成
    Matrix(std::initializer_list<std::array<T, W>> init) {
        size_t i = 0;
        for (const auto& row : init) {
            if (i < H) A[i] = row;
            i++;
        }
    }

    // 3. 要素アクセス（高速化のため [] を使用）
    inline const std::array<T, W>& operator[](int k) const { return A[k]; }
    inline std::array<T, W>& operator[](int k) { return A[k]; }

    // 4. 単位行列の生成 (正方行列のみ)
    static Matrix I() {
        static_assert(H == W, "Identity matrix must be square.");
        Matrix mat;
        for (size_t i = 0; i < H; i++) mat[i][i] = T(1);
        return mat;
    }

    // 5. 加減算演算子
    Matrix& operator+=(const Matrix& B) {
        for (size_t i = 0; i < H; i++)
            for (size_t j = 0; j < W; j++)
                A[i][j] += B.A[i][j];
        return *this;
    }
    Matrix operator+(const Matrix& B) const { return Matrix(*this) += B; }

    Matrix& operator-=(const Matrix& B) {
        for (size_t i = 0; i < H; i++)
            for (size_t j = 0; j < W; j++)
                A[i][j] -= B.A[i][j];
        return *this;
    }
    Matrix operator-(const Matrix& B) const { return Matrix(*this) -= B; }

    // 6. 行列乗算: (H x W) * (W x W2) -> (H x W2) （キャッシュ効率最適化済）
    template <size_t W2>
    Matrix<T, H, W2> operator*(const Matrix<T, W, W2>& B) const {
        Matrix<T, H, W2> C;
        for (size_t i = 0; i < H; i++) {
            for (size_t k = 0; k < W; k++) {
                for (size_t j = 0; j < W2; j++) {
                    C[i][j] += A[i][k] * B.A[k][j];
                }
            }
        }
        return C;
    }

    // 7. 同サイズ同士の乗算のみ *= を許可
    Matrix& operator*=(const Matrix& B) {
        static_assert(H == W, "In-place multiplication is only allowed for square matrices.");
        *this = *this * B;
        return *this;
    }
};
