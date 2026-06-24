template <class T>
struct Matrix {
    vector<vector<T>> A;

    // コンストラクタ
    Matrix() {}
    Matrix(size_t n, size_t m) : A(n, vector<T>(m, 0)) {}
    Matrix(size_t n) : A(n, vector<T>(n, 0)) {}; // ゼロ初期化の正方行列

    // 行数と列数
    size_t height() const { return A.size(); }
    size_t width() const { return A[0].size(); }

    // アクセス演算子
    inline const vector<T>& operator[](int k) const { return A.at(k); }
    inline vector<T>& operator[](int k) { return A.at(k); }

    // 単位行列の生成
    static Matrix I(size_t n) {
        Matrix mat(n);
        for (size_t i = 0; i < n; i++) mat[i][i] = 1;
        return mat;
    }

    // 行列の加算
    Matrix& operator+=(const Matrix& B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                (*this)[i][j] += B[i][j];
        return *this;
    }

    // 行列の減算
    Matrix& operator-=(const Matrix& B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                (*this)[i][j] -= B[i][j];
        return *this;
    }

    // 行列の乗算 (計算量: O(N^3))
    Matrix& operator*=(const Matrix& B) {
        size_t n = height(), m = B.width(), p = width();
        assert(p == B.height());
        vector<vector<T>> C(n, vector<T>(m, 0));
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                for (size_t k = 0; k < p; k++)
                    C[i][j] += (*this)[i][k] * B[k][j];
        A.swap(C);
        return *this;
    }

    // 行列の累乗 (繰り返し二乗法, 計算量: O(N^3 log K))
    Matrix pow(long long k) const {
        Matrix res = Matrix::I(height());
        Matrix x = *this;
        while (k > 0) {
            if (k & 1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }

    Matrix operator+(const Matrix& B) const { return (Matrix(*this) += B); }
    Matrix operator-(const Matrix& B) const { return (Matrix(*this) -= B); }
    Matrix operator*(const Matrix& B) const { return (Matrix(*this) *= B); }
};
