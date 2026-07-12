template <typename Container = std::string>
struct Manacher {
    using ValueType = typename Container::value_type;
    std::vector<int> radius;

    // コンストラクタ: $O(N)$
    // dummyには元の列に出現しない値（文字列なら '$'、整数配列なら -1 など）を指定する
    Manacher(const Container& s, ValueType dummy = '$') {
        int n = s.size();
        Container t;
        t.resize(2 * n + 1, dummy);
        for (int i = 0; i < n; ++i) {
            t[2 * i + 1] = s[i];
        }

        int m = t.size();
        radius.assign(m, 0);
        int i = 0, j = 0;
        while (i < m) {
            while (i - j >= 0 && i + j < m && t[i - j] == t[i + j]) {
                ++j;
            }
            radius[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < m && k + radius[i - k] < j) {
                radius[i + k] = radius[i - k];
                ++k;
            }
            i += k;
            j -= k;
        }
    }
    //radius[i] - 1は回文の長さだから
    // 元の配列の半開区間 [l, r) が回文かどうかを判定する: $O(1)$
    // 0-indexed で指定
    bool is_palindrome(int l, int r) const {
        if (l >= r) return true;
        // ダミー文字を挿入した配列上での、区間 [l, r) の中心インデックスは美しいことに l + r となる
        int center = l + r;
        int len = r - l;
        // radius[center] - 1 が、その中心における元の配列での最大回文長
        return radius[center] - 1 >= len;
    }

    // 元の配列における、全体での最長回文の部分配列の長さを取得する: $O(N)$
    int max_palindrome_length() const {
        int max_len = 0;
        for (int r : radius) {
            max_len = std::max(max_len, r - 1);
        }
        return max_len;
    }
};
