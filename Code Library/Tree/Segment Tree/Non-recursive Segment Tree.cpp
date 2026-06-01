#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// S: 要素の型
// op: 二項演算を返す関数
// e: 単位元を返す関数
template<typename S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
    int n;
    vector<S> tree;

    SegmentTree() : n(0) {}
    SegmentTree(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        tree.assign(2 * n, e());
    }

    // 既存の値に演算を適用する
    void apply(int i, S x) {
        i += n;
        tree[i] = op(tree[i], x);
        while (i > 1) {
            i >>= 1; 
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
        }
    }

    // 値を上書きする
    void update(int i, S x) {
        i += n;
        tree[i] = x;
        while (i > 1) {
            i >>= 1; 
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
        }
    }

    // [l, r) の区間クエリ
    S query(int l, int r) {
        S res_l = e(), res_r = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_l = op(res_l, tree[l++]);
            if (r & 1) res_r = op(tree[--r], res_r);
        }
        return op(res_l, res_r);
    }
};
