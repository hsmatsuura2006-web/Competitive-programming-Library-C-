#pragma once
#include <vector>
#include <algorithm>

// =====================================================================
//  二次元配列 回転テンプレート
//
//  ・正方行列 (N×N)  → in-place 版と copy 版
//  ・非正方行列 (N×M) → copy 版
//  ・回転方向: CW (時計回り 90°) / CCW (反時計回り 90°) / 180°
// =====================================================================

// ------------------------------------------------------------------
// 共通エイリアス
// ------------------------------------------------------------------
template <typename T>
using Matrix = std::vector<std::vector<T>>;

// ------------------------------------------------------------------
//  ユーティリティ: 行列を標準出力に表示 (デバッグ用)
// ------------------------------------------------------------------
template <typename T>
void print_matrix(const Matrix<T>& mat) {
    for (const auto& row : mat) {
        for (const auto& v : row)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

// =====================================================================
//  COPY 版 (非破壊)  ―― 正方・非正方どちらでも動く
//  入力: N×M 行列
//  出力: M×N 行列 (90° 回転の場合)
// =====================================================================

// --- 90° 時計回り (CW) ---
// dst[j][N-1-i] = src[i][j]  →  dst[i][j] = src[N-1-j][i]
template <typename T>
Matrix<T> rotate90_cw(const Matrix<T>& src) {
    int N = (int)src.size();
    int M = (int)src[0].size();
    Matrix<T> dst(M, std::vector<T>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dst[j][N - 1 - i] = src[i][j];
    return dst;
}

// --- 90° 反時計回り (CCW) ---
// dst[M-1-j][i] = src[i][j]  →  dst[i][j] = src[j][M-1-i]
template <typename T>
Matrix<T> rotate90_ccw(const Matrix<T>& src) {
    int N = (int)src.size();
    int M = (int)src[0].size();
    Matrix<T> dst(M, std::vector<T>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dst[M - 1 - j][i] = src[i][j];
    return dst;
}

// --- 180° ---
// dst[N-1-i][M-1-j] = src[i][j]
template <typename T>
Matrix<T> rotate180(const Matrix<T>& src) {
    int N = (int)src.size();
    int M = (int)src[0].size();
    Matrix<T> dst(N, std::vector<T>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dst[N - 1 - i][M - 1 - j] = src[i][j];
    return dst;
}

// =====================================================================
//  IN-PLACE 版  ―― 正方行列 (N×N) 専用
// =====================================================================

// --- 90° 時計回り (CW) ---
//   Step1: 転置  a[i][j] <-> a[j][i]
//   Step2: 各行を左右反転
template <typename T>
void rotate90_cw_inplace(Matrix<T>& mat) {
    int N = (int)mat.size();
    // 転置
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            std::swap(mat[i][j], mat[j][i]);
    // 各行を反転
    for (int i = 0; i < N; ++i)
        std::reverse(mat[i].begin(), mat[i].end());
}

// --- 90° 反時計回り (CCW) ---
//   Step1: 各行を左右反転
//   Step2: 転置
template <typename T>
void rotate90_ccw_inplace(Matrix<T>& mat) {
    int N = (int)mat.size();
    // 各行を反転
    for (int i = 0; i < N; ++i)
        std::reverse(mat[i].begin(), mat[i].end());
    // 転置
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            std::swap(mat[i][j], mat[j][i]);
}

// --- 180° ---
//   各行を反転したあと行の順序を反転
template <typename T>
void rotate180_inplace(Matrix<T>& mat) {
    for (auto& row : mat)
        std::reverse(row.begin(), row.end());
    std::reverse(mat.begin(), mat.end());
}
