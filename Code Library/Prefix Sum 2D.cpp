template<typename T>
struct PrefixSum2D {
    int H, W;
    vector<vector<T>> sum;

    PrefixSum2D() {}
    // 2次元ベクターから初期化
    PrefixSum2D(const vector<vector<T>>& grid, T p = 0) {
        init(grid, p);
    }

    void init(const vector<vector<T>>& grid, T p = 0) {
        H = grid.size();
        W = H ? grid[0].size() : 0;
        sum.assign(H + 1, vector<T>(W + 1, 0));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + grid[i][j];
                if (p > 0) {
                    sum[i + 1][j + 1] = (sum[i + 1][j + 1] % p + p) % p;
                }
            }
        }
    }

    // 半開区間 [h1, h2) x [w1, w2) の和を取得 (0-indexed)
    T query(int h1, int h2, int w1, int w2, T p = 0) const {
        if (h1 >= h2 || w1 >= w2) return 0;
        T res = sum[h2][w2] - sum[h1][w2] - sum[h2][w1] + sum[h1][w1];
        if (p > 0) {
            return (res % p + p) % p;
        }
        return res;
    }
};
