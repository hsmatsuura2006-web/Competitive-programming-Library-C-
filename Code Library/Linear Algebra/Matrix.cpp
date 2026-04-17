struct Matrix {
    lll mat[2][2]; // 2x2 行列
    ll mod;

    Matrix(ll m) : mod(m) {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }

    // 行列の積 A * B
    Matrix operator*(const Matrix& B) const {
        Matrix res(mod);
        for (int i = 0; i < 2; i++) {
            for (int k = 0; k < 2; k++) {
                for (int j = 0; j < 2; j++) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * B.mat[k][j]) % mod;
                }
            }
        }
        return res;
    }

    // 行列の累乗 A^n
    Matrix pow(ll n) {
        Matrix res(mod);
        res.mat[0][0] = res.mat[1][1] = 1; // 単位行列
        Matrix A = *this;
        while (n > 0) {
            if (n & 1) res = res * A;
            A = A * A;
            n >>= 1;
        }
        return res;
    }
};

void solve() {
    ll a, x, m; cin >> a >> x >> m;

    // 遷移行列 M = [[a, 1], [0, 1]] を作る
    Matrix M(m);
    M.mat[0][0] = a % m;
    M.mat[0][1] = 1;
    M.mat[1][0] = 0;
    M.mat[1][1] = 1;

    // M^x を計算
    Matrix res = M.pow(x);

    // 求める和 S_x は、ベクトル [S_0, 1]^T に M^x を掛けたものの第1成分
    // S_0 = 0 なので、 res.mat[0][0] * 0 + res.mat[0][1] * 1
    cout << (ll)res.mat[0][1] << endl;
}
