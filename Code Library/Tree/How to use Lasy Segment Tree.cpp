#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// 1. データの型 S と、その操作
using S = long long;
const S INF = 1e18;
S op(S a, S b) { return min(a, b); }
S e() { return INF; }

// 2. 操作の型 F と、その合成
using F = long long;
S mapping(F f, S s) { return s + f; }      // 値 s に f を加算
F composition(F f, F g) { return f + g; } // 加算 f と 加算 g を合わせる
F id() { return 0; }                       // 加算における何もしないは 0

int main() {
    vector<S> v = {1, 2, 3, 4, 5};

    // インスタンス化
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    // 区間 [0, 3) に 10 を足す -> {11, 12, 13, 4, 5}
    seg.apply(0, 3, 10);

    // 区間 [2, 5) の最小値を取得 -> min(13, 4, 5) = 4
    cout << seg.prod(2, 5) << endl; 

    // 1点取得
    cout << seg.get(0) << endl; // 11
}
