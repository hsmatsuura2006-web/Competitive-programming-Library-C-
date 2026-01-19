struct SegmentTree {
public:
  ll n;
  vector<ll> data, datb;
  SegmentTree(int _n) {
    n = 1;
    while (n < _n) n <<= 1;
    data.assign(2 * n, 0);
    datb.assign(2 * n, 0);
  }
  void add(ll a, ll b, ll x) {
    add(a, b, x, 0, 0, n);
  }
  ll sum(ll a, ll b) {
    return sum(a, b, 0, 0, n);
  }
private:
  void add(ll a, ll b, ll x, ll k, ll l, ll r) {
    if (a <= l && r <= b) {
      data[k] += x;
    }else if (l < b && a < r) {
      datb[k] += (min(b, r) - max(a, l)) * x;
      add(a, b, x, k * 2 + 1, l, (l + r)/2);
      add(a, b, x, k * 2 + 2, (l + r)/2, r);
    }
  }

  ll sum(ll a, ll b, ll k, ll l, ll r) {
    if (b <= l || r <= a) {
      return 0;
    }else if (a <= l && r <= b) {
      return data[k] * (r - l) + datb[k];
    }else {
      ll res = (min(b, r) - max(a, l)) * data[k];
      res += sum(a, b, k * 2 + 1, l, (l + r)/2);
      res += sum(a, b, k * 2 + 2, (l + r)/2, r);
      return res;
    }
  }
};
