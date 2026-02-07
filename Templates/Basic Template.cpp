#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <iomanip>
#include <limits>
#include <cstdint>
#ifdef ONLINE_JUDGE
#define dbg(x) (void)0
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#else
#define dbg(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl;
#endif
#define rep(i,n) for(ll i=0;i<n;i++)
#define rep1(i,n) for(ll i=1;i<=n;i++)
#define fore(v, g) for (const auto& v : g)
#define yes cout << "Yes" << endl;
#define no cout << "No" << endl;
#define eb emplace_back
#define em emplace
#define pb pop_back
using namespace std;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ld = long double;
using P = pair<ll,ll>;
struct Edge{
	ll to, cost;
};
using Graph = vector<vector<Edge>>;
void yn(bool f) { cout << (f ? "Yes" : "No") << "\n"; }
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>;
template<class T> using pq = priority_queue<T, vector<T>>;//降順
template<class T> using pq_g = priority_queue<T, vector<T>, greater<T>>;//昇順
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
//const ll dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
//bool out_grid(const ll i, const ll j, const ll h, const ll w) {return(!(0 <= i && i < h && 0 <= j && j < w));}
void solve() {


}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T = 1;
    while (T--) {solve();}
    return 0;
}
