#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <ranges>
#include <cctype>
#include <iomanip>
#include <random>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;
using mint = modint998244353;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * LIS(最長増加部分列)
 * 頂点になる部分を全探索 両端から見る
 */
void solve() {
    ll N; cin >> N;
    Vec<ll> A(N); rep(i, 0, N) cin >> A[i];

    Vec<ll> dp1(N+1, INF), P(N);
    rep(i, 0, N){
        auto it = lower_bound(all(dp1), A[i]) - dp1.begin();
        chmin(dp1[it], A[i]); P[i]=it+1;
    }

    Vec<ll> dp2(N+1, INF), Q(N);
    rrep(i, 0, N){
        auto it = lower_bound(all(dp2), A[i]) - dp2.begin();
        chmin(dp2[it], A[i]); Q[i]=it+1;
    }

    ll ans=0;
    rep(i, 0, N) chmax(ans, P[i]+Q[i]-1);
    out(ans);
}

/**
 * LIS(最長増加部分列)
 * dp[i]:LISの長さはiとなるときの, 部分列の末尾のmin
 * ans:LISが構築できるときのiのmax
 */
// void solve() {
//     // ロジックをちゃんと考える！！！
//     ll N; cin >> N;
//     vl A(N); rep(i, 0, N) cin >> A[i];
//     vl dp(N+2, INF);
//     rep(i, 0, N){
//         auto it = lower_bound(all(dp), A[i]) - dp.begin();
//         chmin(dp[it], A[i]);
//     }
//     ll ans=-INF;
//     rep(i, 0, N) if(dp[i]!=INF) chmax(ans, i+1);
//     out(ans);
// }


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}