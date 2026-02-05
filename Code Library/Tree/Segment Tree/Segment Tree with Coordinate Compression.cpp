struct TopKSumSegTree {
    int n;
    struct Node {
        long long cnt = 0;
        long long sum = 0;
    };
    vector<Node> tree;
    vector<long long> dict; 

    //1. 初期化：先読みした全数値を渡して座圧を確定させる
    TopKSumSegTree(const vector<long long>& vals) {
        dict = vals;
        sort(dict.begin(), dict.end());
        dict.erase(unique(dict.begin(), dict.end()), dict.end());
        
        n = 1;
        while (n < dict.size()) n *= 2;
        tree.resize(2 * n);
    }

    // 2. 値の更新：valを1個追加なら (+1, val)、1個削除なら (-1, -val)
    void update(long long val, int add_cnt) {
        int idx = lower_bound(dict.begin(), dict.end(), val) - dict.begin();
        long long add_sum = val * add_cnt;
        idx += n;
        tree[idx].cnt += add_cnt;
        tree[idx].sum += add_sum;
        while (idx > 1) {
            idx /= 2;
            tree[idx].cnt = tree[2 * idx].cnt + tree[2 * idx + 1].cnt;
            tree[idx].sum = tree[2 * idx].sum + tree[2 * idx + 1].sum;
        }
    }

    // 3. クエリ：上位 k 個の和を取得
    long long query(long long k) {
        if (k <= 0) return 0;
        if (tree[1].cnt <= k) return tree[1].sum;
        return fetch(1, 0, n - 1, k);
    }

private:
    long long fetch(int v, int tl, int tr, long long k) {
        if (tl == tr) return dict[tl] * k;
        int tm = (tl + tr) / 2;
        long long r_cnt = tree[2 * v + 1].cnt;
        if (r_cnt >= k) {
            return fetch(2 * v + 1, tm + 1, tr, k);
        } else {
            return tree[2 * v + 1].sum + fetch(2 * v, tl, tm, k - r_cnt);
        }
    }
};
