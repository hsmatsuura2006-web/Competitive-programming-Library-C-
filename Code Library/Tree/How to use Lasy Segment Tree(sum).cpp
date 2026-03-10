struct S {
    long long sum;
    int size;
};

S op(S a, S b) { return {a.sum + b.sum, a.size + b.size}; }
S e() { return {0, 0}; }

using F = long long;
S mapping(F f, S x) { return {x.sum + f * x.size, x.size}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
    int n = 10;
    std::vector<S> initial(n, {0, 1}); // Initial sum 0, each element size 1
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(initial);

    seg.apply(0, 5, 10); // Add 10 to indices [0, 5)
    auto res = seg.prod(0, 3); // Returns sum of [0, 3), which is 30
}
