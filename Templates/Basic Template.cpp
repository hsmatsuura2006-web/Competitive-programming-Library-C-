#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <iomanip>
#include <limits>
#include <cstdint>
#include <bit>

#pragma GCC optimize("Ofast")

#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define reps(i, m, n) for (ll i = (ll)(m); i < (ll)(n); ++i)
#define fore(v, g) for (const auto& v : g)
#define yes cout << "Yes" << "\n"
#define no cout << "No" << "\n"
#define eb emplace_back
#define em emplace
#define pb pop_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

using namespace std;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ld = long double;
using P = pair<ll, ll>;

struct Edge {
    ll to, cost;
};
using Graph = vector<vector<Edge>>;

void yn(bool f) { cout << (f ? "Yes" : "No") << "\n"; }

template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>;

template<class T> using pq = priority_queue<T, vector<T>>; // 降順
template<class T> using pq_g = priority_queue<T, vector<T>, greater<T>>; // 昇順

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<typename T, typename... Ts>
bool is_any_of(T val, Ts... vals) {
    return ((val == vals) || ...);
}

#ifdef LOCAL
#define debug(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#else
#define debug(x) void(0)
#endif

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

template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) { os << p.first << " " << p.second; return os; }

template<typename T>
istream& operator>>(istream& is, vector<T>& v) { for (auto& x : v) is >> x; return is; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) os << v[i] << (i + 1 == v.size() ? "" : " ");
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
    for (size_t i = 0; i < v.size(); ++i) os << v[i] << (i + 1 == v.size() ? "" : "\n");
    return os;
}

const ll dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const ll dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
bool out_grid(const ll i, const ll j, const ll h, const ll w) { return (!(0 <= i && i < h && 0 <= j && j < w)); }

const ll INF = 1e18;
const ll MOD = 998244353;
const ll MOD1 = 1000000007;

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

void solve() {
    // ここにコードを書く
}
