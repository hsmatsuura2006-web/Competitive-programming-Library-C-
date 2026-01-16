int op(int a, int b) { return a ^ b; }
int e() { return 0; }

struct SegmentTree {
    int n;
    vector<int> tree;
    SegmentTree(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        tree.assign(2 * n, e());
    }
    void add(int i, int x) {
        i += n;
        tree[i] = op(tree[i], x);
        while (i > 1) {
            i >>= 1; 
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
        }
    }
    // 区間取得：[l, r)
    int query(int l, int r) {
        int res_l = e(), res_r = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_l = op(res_l, tree[l++]);
            if (r & 1) res_r = op(tree[--r], res_r);
        }
        return op(res_l, res_r);
    }
};
