template<typename T>
class FenwickTree {
private: ll n;
  vector<T> bit;
public:
  explicit FenwickTree(const ll n_) : n(n_ + 1), bit(n, 0){}
  void add(ll i, T x) {
    for (ll idx = i; idx < n; idx += (idx & -idx)) {
      bit[idx] += x;
    }
  }
  T sum(ll i) {
    T s(0);
    for (ll idx = i; idx > 0; idx -= (idx & -idx)) {
      s += bit[idx];  
    }
    return s;
  }
};
