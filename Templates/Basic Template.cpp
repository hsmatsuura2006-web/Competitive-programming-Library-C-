#include <bits/stdc++.h>

#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define reps(i, m, n) for (ll i = (ll)(m); i < (ll)(n); ++i)
#define repr(i, n) for (ll i = (ll)(n) - 1; i >= 0; --i)
#define fore(v, g) for (const auto& v : g)
#define yes cout << "Yes" << "\n"
#define no cout << "No" << "\n"
#define eb emplace_back
#define em emplace
#define pb pop_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())
#define fi first
#define se second
#define UNIQUE(v) sort((v).begin(), (v).end()), (v).erase(unique((v).begin(), (v).end()), (v).end())
#define SORT(v) sort(all(v))
#define RSORT(v) sort(rall(v))

using namespace std;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ld = long double;
using P = pair<ll, ll>;

struct Edge {
  ll to, cost;
};

using Graph = vector<vector<Edge> >;

void yn(bool f) { cout << (f ? "Yes" : "No") << "\n"; }

template<typename T>
using vc = vector<T>;
template<typename T>
using vv = vc<vc<T> >;
using vl = vc<ll>;
using vvl = vv<ll>;
using vvvl = vv<vl>;
using vvvvl = vv<vvl>;
using vs = vc<string>;
using vvs = vv<string>;
using vd = vc<ld>;
using vb = vc<bool>;
using vp = vc<P>;
using tp = tuple<ll, ll, ll>;

template<class T>
using pq = priority_queue<T, vector<T> >; // 降順
template<class T>
using pq_g = priority_queue<T, vector<T>, greater<T> >; // 昇順

template<class T>
inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template<class T>
inline bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}

template<typename T, typename... Ts>
bool is_any_of(T val, Ts... vals) {
  return ((val == vals) || ...);
}

//ビット
inline ll popcount(ll x) { return __builtin_popcountll(x); }
inline ll bit(ll n, ll i) { return (n >> i) & 1; } //右からi番目のビットを取得
inline ll bit_set(ll n, ll i) { return n | (1LL << i); } //右からi番目を1に
inline ll bit_clear(ll n, ll i) { return n & ~(1LL << i); } //右からi番目を0に
inline ll bit_flip(ll n, ll i) { return n ^ (1LL << i); } //右からi番目を反転
inline ll msb(ll x) { return x == 0 ? -1 : 63 - __builtin_clzll(x); } // 最上位ビットの位置
inline ll lsb(ll x) { return x == 0 ? -1 : __builtin_ctzll(x); } // 最下位ビットの位置
inline ll lowbit(ll x) { return x & (-x); } // 最下位の立っているビットそのもの
//nの空でない部分集合を全列挙
//for (ll sub = n; sub > 0; sub = (sub - 1) & n) {}
//nを含む全体集合の中の上位集合列挙
//for (ll sup = n; sup < (1LL << 20); sup = (sup + 1) | n) {}

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

//オペレーター
template<typename T, typename U>
istream &operator>>(istream &is, pair<T, U> &p) {
  is >> p.first >> p.second;
  return is;
}

template<typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << p.first << " " << p.second;
  return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (auto &x: v) is >> x;
  return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  for (size_t i = 0; i < v.size(); ++i) os << v[i] << (i + 1 == v.size() ? "" : " ");
  return os;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<vector<T> > &v) {
  for (size_t i = 0; i < v.size(); ++i) os << v[i] << (i + 1 == v.size() ? "" : "\n");
  return os;
}

ostream &operator<<(ostream &os, lll v) {
  if (v < 0) {
    os << '-';
    v = -v;
  }
  if (v > 9) os << (lll) (v / 10);
  return os << (char) ('0' + v % 10);
}

istream &operator>>(istream &is, lll &v) {
  string s;
  is >> s;
  v = 0;
  bool neg = (s[0] == '-');
  for (char c: s) if (c != '-') v = v * 10 + (c - '0');
  if (neg) v = -v;
  return is;
}

// 常に数直線の下方向に丸める除算
template<typename T>
T floor_div(T n, T d) {
  T res = n / d;
  T rem = n % d;
  if (rem != 0 && ((n < 0) ^ (d < 0))) res--;
  return res;
}

// 常に数直線の上方向に丸める除算
template<typename T>
T ceil_div(T n, T d) {
  T res = n / d;
  T rem = n % d;
  if (rem != 0 && !((n < 0) ^ (d < 0))) res++;
  return res;
}

//グリッド
const ll dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const ll dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
bool out_grid(const ll i, const ll j, const ll h, const ll w) { return (!(0 <= i && i < h && 0 <= j && j < w)); }
//定数
const ll INF = 1e18;
const ll MOD = 998244353;
const ll MOD1 = 1000000007;
//デバッグ
#ifdef LOCAL
namespace dbgutil {
  template<typename T, typename = void>
  struct is_iterable : std::false_type {
  };

  template<typename T>
  struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T &>())),
        decltype(std::end(std::declval<T &>()))> >
      : std::true_type {
  };

  template<typename T>
  constexpr bool is_iterable_v = is_iterable<T>::value;

  template<typename T, typename = void>
  struct is_streamable : std::false_type {
  };

  template<typename T>
  struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream &>() << std::declval<T>())> >
      : std::true_type {
  };

  template<typename T>
  constexpr bool is_streamable_v = is_streamable<T>::value;

  template<typename T>
  constexpr bool is_string_like_v =
      std::is_same_v<std::decay_t<T>, std::string> ||
      std::is_same_v<std::decay_t<T>, const char *> ||
      std::is_same_v<std::decay_t<T>, char *>;

  template<typename T>
  struct is_pair : std::false_type {
  };

  template<typename A, typename B>
  struct is_pair<std::pair<A, B> > : std::true_type {
  };

  template<typename T>
  struct is_tuple : std::false_type {
  };

  template<typename... Ts>
  struct is_tuple<std::tuple<Ts...> > : std::true_type {
  };

  template<typename T>
  struct is_optional : std::false_type {
  };

  template<typename T>
  struct is_optional<std::optional<T> > : std::true_type {
  };

  template<typename T>
  struct is_stack : std::false_type {
  };

  template<typename T, typename C>
  struct is_stack<std::stack<T, C> > : std::true_type {
  };

  template<typename T>
  struct is_queue : std::false_type {
  };

  template<typename T, typename C>
  struct is_queue<std::queue<T, C> > : std::true_type {
  };

  template<typename T>
  struct is_priority_queue : std::false_type {
  };

  template<typename T, typename C, typename Cmp>
  struct is_priority_queue<std::priority_queue<T, C, Cmp> > : std::true_type {
  };

  template<typename T>
  constexpr bool is_int128_v = std::is_same_v<std::decay_t<T>, __int128> ||
                               std::is_same_v<std::decay_t<T>, unsigned __int128>;

  //出力
  template<typename T>
  void print_value(std::ostream &os, const T &v) {
    using D = std::decay_t<T>;

    if constexpr (is_pair<D>::value) {
      os << "(";
      print_value(os, v.first);
      os << ", ";
      print_value(os, v.second);
      os << ")";
    } else if constexpr (is_tuple<D>::value) {
      os << "(";
      std::apply(
        [&](auto &&... args) {
          size_t i = 0, n = sizeof...(args);
          ((print_value(os, args), os << (++i < n ? ", " : "")), ...);
        },
        v);
      os << ")";
    } else if constexpr (is_optional<D>::value) {
      if (v) print_value(os, *v);
      else os << "nullopt";
    } else if constexpr (is_int128_v<D>) {
      __int128 x = v;
      if (x < 0) {
        os << '-';
        x = -x;
      }
      std::string s;
      if (x == 0) s = "0";
      while (x > 0) {
        s += char('0' + int(x % 10));
        x /= 10;
      }
      std::reverse(s.begin(), s.end());
      os << s;
    } else if constexpr (is_stack<D>::value || is_queue<D>::value || is_priority_queue<D>::value) {
      auto copy = v;
      std::vector<typename D::value_type> vec;
      if constexpr (is_stack<D>::value) {
        while (!copy.empty()) {
          vec.push_back(copy.top());
          copy.pop();
        }
        std::reverse(vec.begin(), vec.end());
        os << "stack";
      } else if constexpr (is_queue<D>::value) {
        while (!copy.empty()) {
          vec.push_back(copy.front());
          copy.pop();
        }
        os << "queue";
      } else {
        while (!copy.empty()) {
          vec.push_back(copy.top());
          copy.pop();
        }
        os << "priority_queue";
      }
      print_value(os, vec);
    } else if constexpr (is_iterable_v<D> && !is_string_like_v<D>) {
      os << "{";
      bool first = true;
      for (const auto &x: v) {
        if (!first) os << ", ";
        first = false;
        print_value(os, x);
      }
      os << "}";
    } else if constexpr (is_streamable_v<D>) {
      os << v;
    } else {
      os << "<?>";
    }
  }

  inline std::vector<std::string> split_names(const std::string &s) {
    std::vector<std::string> res;
    int depth = 0;
    std::string cur;
    for (char c: s) {
      if (c == '(' || c == '<' || c == '[' || c == '{') depth++;
      if (c == ')' || c == '>' || c == ']' || c == '}') depth--;
      if (c == ',' && depth == 0) {
        res.push_back(cur);
        cur.clear();
      } else {
        cur += c;
      }
    }
    if (!cur.empty()) res.push_back(cur);
    for (auto &t: res) {
      size_t a = t.find_first_not_of(" \t");
      size_t b = t.find_last_not_of(" \t");
      t = (a == std::string::npos) ? "" : t.substr(a, b - a + 1);
    }
    return res;
  }

  inline void debug_print(const std::vector<std::string> &, size_t) { std::cerr << "\n"; }

  template<typename T, typename... Rest>
  void debug_print(const std::vector<std::string> &names, size_t idx, const T &v, const Rest &... rest) {
    std::cerr << "\033[36m" << names[idx] << "\033[0m" << " = \033[33m";
    print_value(std::cerr, v);
    std::cerr << "\033[0m";
    if constexpr (sizeof...(rest) > 0) std::cerr << ", ";
    debug_print(names, idx + 1, rest...);
  }
} // namespace dbgutil

#define debug(...)                                                              \
  do {                                                                          \
    std::cerr << "\033[32m[" << __FILE__ << ":" << __LINE__ << "]\033[0m ";     \
    dbgutil::debug_print(dbgutil::split_names(#__VA_ARGS__), 0, __VA_ARGS__);   \
  } while (0)

#else
#define debug(...) void(0)
#endif

void solve();

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(15);
  ll T = 1;
  // cin >> T;
  while (T--) { solve(); }
  return 0;
}

//#include <atcoder/all>
//using namespace atcoder;

void solve() {
}
