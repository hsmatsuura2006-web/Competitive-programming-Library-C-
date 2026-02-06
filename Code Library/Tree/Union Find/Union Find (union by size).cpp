class UnionFind {
private:
    vector<ll> par, siz;
public:
    UnionFind(ll n) : par(n, -1), siz(n, 1){}
    //根を求める
    ll root (ll x) {
        if (par[x] == -1) return x;
        return par[x] = root(par[x]);
    }
    //xとyが同じグループに属するかどうか(根が一致するかどうか)
    bool isSame(ll x, ll y) {
        return root(x) == root(y);
    }
    //xを含むグループとyを含むグループを併合する
    bool unite(ll x, ll y) {
        ll p = root(x), q = root(y);
        if (p == q) return false;
        if (siz[p] < siz[q]) swap(p, q);
        par[q] = p;
        siz[p] += siz[q];
        return true;
    }
    //xを含むグループのサイズ
    ll size(ll x) {
        return siz[root(x)];
    }
    //グループの数
    ll groupCnt() {
        set<ll> s;
        rep(i, par.size()) {
            s.insert(root(i));
        }
        return s.size();
    }
};
//使い方
//UnionFind uf(n)で初期化する
