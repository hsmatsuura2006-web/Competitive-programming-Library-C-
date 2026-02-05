//その集合でx以下の個数が何個あるかを調べる(setじゃ無理です)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// 任意の型 T に対して定義（ここでは long long を想定）
typedef tree<
    long long,                // キーの型
    null_type,                // 値の型（setとして使うなら null_type）
    std::less<long long>,     // 比較関数（昇順）
    rb_tree_tag,              // 木の種類（赤黒木を指定）
    tree_order_statistics_node_update // これが「サイズ情報」を保持する
> ordered_set;

ordered_set s;
s.insert(1);
s.insert(4);
s.insert(8);

// order_of_key: 値からインデックスを求める
cout << s.order_of_key(4) << endl; // 「4」は 0, 1... なので 1 を返す
cout << s.order_of_key(10) << endl; // 存在しない大きな値を入れると、size() と同じ 3 を返す

// find_by_order: インデックスから値を求める
cout << *s.find_by_order(0) << endl; // 0番目の要素である 1 を返す

//値が重複する場合 -> pairですべてを別々の値をして管理する
// pairの1番目を「実際の値」、2番目を「追加順のID」にする
typedef tree<
    pair<long long, int>, 
    null_type,
    less<pair<long long, int>>, 
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_multiset;

ordered_multiset s;
int timer = 0; // ID生成用

// 追加
s.insert({10, timer++});
s.insert({20, timer++});
s.insert({20, timer++}); // 2つ目の20
s.insert({30, timer++});

// k番目の値を取得
auto it = s.find_by_order(2); // 0-indexedで2番目（3つ目）
if (it != s.end()) {
    cout << it->first << endl; // 20 が出力される
}
