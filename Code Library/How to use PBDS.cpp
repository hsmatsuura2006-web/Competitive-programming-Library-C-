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
