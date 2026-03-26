//区間更新区間和
template <typename T>
struct LazySegTree {
    int n;
    vector<T> dat, lazy;
    const T lazy_empty = numeric_limits<T>::max(); // ???????????????????????

    LazySegTree(int n_) {
        int x = 1;
        while (n_ > x) x *= 2;
        n = x;
        dat.assign(2 * n - 1, 0);
        lazy.assign(2 * n - 1, lazy_empty);
    }

    void eval(int k, int l, int r) {
        if (lazy[k] == lazy_empty) return;
        
        // ????????????? * ??????
        dat[k] = lazy[k] * (r - l);

        if (k < n - 1) { // ????????????????
            lazy[k * 2 + 1] = lazy[k];
            lazy[k * 2 + 2] = lazy[k];
        }
        lazy[k] = lazy_empty;
    }

    void update(int a, int b, T x, int k, int l, int r) {
        eval(k, l, r);
        if (a <= l && r <= b) {
            lazy[k] = x;
            eval(k, l, r);
        } else if (a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
        }
    }

    void update(int a, int b, T x) { update(a, b, x, 0, 0, n); }

    T query_sub(int a, int b, int k, int l, int r) {
        eval(k, l, r);
        if (r <= a || b <= l) return 0; // ??????? 0 ?????
        if (a <= l && r <= b) return dat[k];
        
        T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
        return vl + vr;
    }

    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
};
