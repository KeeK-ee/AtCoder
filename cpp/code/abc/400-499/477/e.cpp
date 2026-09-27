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
 * E:最短経路は頂点N+1を通るか否かしかない
N+1を通る場合(SかTがN+1に一致する場合を含む)->頂点N+1からの最短経路をダイクストラで前計算してクエリ毎O(1)
N+1を通らない場合->経路は必ずs->s+1->..t-1>tかs->s-1->..t+1>tのどちらか 累積和でO(1)(自分はBITなのでO(logN))
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    Vec<ll> A(N+1), B(N+1);
    rep(i, 1, N+1) cin >> A[i];
    rep(i, 1, N+1) cin >> B[i];
    
    Vec<ll> dist(N+2, INF); dist[N+1]=0; // N+1からの最短距離
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({0, N+1}); //{その頂点への現時点の最小コスト, 頂点番号}

    Vec<Vec<pll>> G(N+2);
    rep(i, 1, N+1){
        G[i].push_back({(i%N)+1, A[i]}); G[(i%N)+1].push_back({i , A[i]});
    }
    rep(i, 1, N+1){
        G[i].push_back({N+1, B[i]}); G[N+1].push_back({i, B[i]});
    }
    while(!q.empty()){
        auto [c, to] = q.top(); q.pop();
        if(dist[to]!=c) continue; //確定している
        for(auto [nv, nc] : G[to]){
            if(dist[nv]<=c+nc) continue; //更新せず
            dist[nv]=c+nc;
            q.push({c+nc, nv});
        }
    }

    fenwick_tree<ll> BIT(N+1);
    rep(i, 1, N+1) BIT.add(i, A[i]);
    BIT.add(0, 0);
    rep(qi, 0, Q){
        ll s, t; cin >> s >> t;
        if(s>t) swap(s, t);
        ll ans=INF;
        chmin(ans, (ll)dist[s]+(ll)dist[t]);
        // cout << dist[s]+dist[t] << "\n";
        if(s!=N+1 and t!=N+1){
            chmin(ans, (ll)BIT.sum(s, t));
            // cout << (ll)BIT.sum(s, t) << "\n";
            chmin(ans, (ll)BIT.sum(t, N+1)+(ll)BIT.sum(0, s));
            // cout << (ll)BIT.sum(t, N+1) << " "  << (ll)BIT.sum(0, s) << "\n";
        }
        out(ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}