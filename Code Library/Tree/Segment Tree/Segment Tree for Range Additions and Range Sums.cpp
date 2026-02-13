#include <vector>
#include <algorithm>

template <typename T>
struct SegmentTree {
public:
    int n;
    std::vector<T> data, datb;

    SegmentTree(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        data.assign(2 * n - 1, T(0));
        datb.assign(2 * n - 1, T(0));
    }

    void add(int a, int b, T x) {
        if (a >= b) return;
        add(a, b, x, 0, 0, n);
    }

    T sum(int a, int b) {
        if (a >= b) return T(0);
        return sum(a, b, 0, 0, n);
    }

private:
    void add(int a, int b, T x, int k, int l, int r) {
        if (a <= l && r <= b) {
            data[k] += x;
        } else if (l < b && a < r) {
            datb[k] += T(std::min(b, r) - std::max(a, l)) * x;
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);
        }
    }

    T sum(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) {
            return T(0);
        } else if (a <= l && r <= b) {
            return data[k] * (r - l) + datb[k];
        } else {
            T res = T(std::min(b, r) - std::max(a, l)) * data[k];
            res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
            res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
            return res;
        }
    }
};
