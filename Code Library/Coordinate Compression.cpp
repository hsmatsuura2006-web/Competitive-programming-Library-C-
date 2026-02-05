#include <vector>
#include <algorithm>

template <typename T>
struct Compressor {
    std::vector<T> dict;

    // 1. 値を登録する（先読み用）
    void add(T x) {
        dict.push_back(x);
    }

    // 2. 辞書を確定させる
    void build() {
        std::sort(dict.begin(), dict.end());
        dict.erase(std::unique(dict.begin(), dict.end()), dict.dict.end());
    }

    // 3. 値 x が何番目か (0-indexed) を返す
    int get_idx(T x) {
        return std::lower_bound(dict.begin(), dict.end(), x) - dict.begin();
    }

    // 4. 番目から元の値を返す
    T get_val(int idx) {
        return dict[idx];
    }

    // 種類数（BITやセグ木のサイズに使う）
    int size() {
        return dict.size();
    }
};
// Compressor<ll> aとして使う。
