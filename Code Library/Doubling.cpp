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
using Graph = vector<vector<ll>>;
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

//状態変数と値を分離してテーブルに格納する
void solve() {
	ll n, k; cin >> n >> k;
	vl a(n);
	rep(i, n) cin >> a[i];
	const int MAX_P = 40;
	vvl next_pos(MAX_P, vl(n));//インデックス
	vvl candy_sum(MAX_P, vl(n));//飴の合計数
	rep(i, n){
		next_pos[0][i] = (i + a[i])%n;
		candy_sum[0][i] = a[i];
	}
	rep(p, MAX_P - 1) rep(i, n){
		ll mid = next_pos[p][i];
		next_pos[p + 1][i] = next_pos[p][mid];
		candy_sum[p + 1][i] = candy_sum[p][i] + candy_sum[p][mid];
	}
	ll ans = 0;
	ll now = 0;
	rep(p, MAX_P){
		if((k>>p)&1){
			ans += candy_sum[p][now];
			now = next_pos[p][now];
		}
	}
	cout << ans << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T = 1;
    while (T--) {solve();}
    return 0;
}
// 10進数文字列を 2進数の bit 列 (下位 bit が先頭) に変換
//もしkがとてつもなくと大きければこれを使えばいい
vector<int> to_binary(string s) {
  vector<int> bits;
  while (!s.empty() && s != "0") {
    int rem = 0;
    string next_s = "";
    for (char c : s) {
      int cur = rem * 10 + (c - '0');
      int q = cur / 2;
      rem = cur % 2;
      if (!next_s.empty() || q > 0) {
        next_s += (char)('0' + q);
      }
    }
    bits.push_back(rem);
    s = next_s;
  }
  return bits;
}
