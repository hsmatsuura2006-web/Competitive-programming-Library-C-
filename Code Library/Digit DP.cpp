#include <cmath>
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
ll solve(const string& s){
	ll limit = s.size();
	vector dp(limit + 1, vector(10, vector(2, vl(2, 0))));
	dp[0][0][0][0] = 1;
	rep(i, limit) rep(j, 10) rep(k, 2) rep(l, 2){
		if(dp[i][j][k][l] == 0) continue;
		ll range = k ? 9 : s[i] - '0';//一回通ってればなにしてもいい
		rep(d, range + 1){
			ll next_j = j;
			ll next_k = k;
			ll next_l = l;
			if(l == 0){
				if(d == 0){
					next_l = 0;
					next_j = 0;
				}else{
					next_l = 1;
					next_j = d;
				}
			}else{//すでに始まってる場合
				if(d >= j) continue;//ここが要、最初より大きいか選別する
				next_l = 1;
				next_j = j;
			}
			if(d < s[i] - '0'){
					next_k = 1;
			}
			dp[i + 1][next_j][next_k][next_l] += dp[i][j][k][l];
		}
	}
	ll ans = 0;
	rep(i, 10) rep(j, 2){
		ans += dp[limit][i][j][1];
	}
	return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll l, r; cin >> l >> r;
    cout << solve(to_string(r)) - solve(to_string(l - 1)) << endl;
    return 0;
}
