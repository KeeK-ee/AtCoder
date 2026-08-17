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
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
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
#define se second
#define fi first

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
 * 具体的な経路はどうでもよくて、足場iへたどり着くまでの最小コストは直前の足場2つに対するこの問題の答えが分かれば解けるから、iが小さい方から決められる->DP
 * メモ化再帰でも解ける
 */
void solve() {
    ll N; cin >> N;
    vl H(N); rep(i, 0, N) cin >> H[i];
    vl dp(N+1, INF);
    dp[0]=0; dp[1]=0;
    rep(i, 2, N+1){
        // dp[i-1]とdp[i-2]を見てdp[i]を決める
        if(i-2>=0) chmin(dp[i], dp[i-1]+abs(H[i-1]-H[i-2]));
        if(i-3>=0) chmin(dp[i], dp[i-2]+abs(H[i-1]-H[i-3]));
    }
    out(dp[N]);
}

/**
 * ダイクストラ法でも解ける
 * N頂点2N辺
 */
void solve2(){
    ll N; cin >> N;
    vector<ll> H(N);
    rep(i, 0, N) cin >> H[i];

    vvpll G(N);
    rep(i, 0, N){
        if(i+1<=N-1) G[i].push_back({i+1, abs(H[i]-H[i+1])});
        if(i+2<=N-1) G[i].push_back({i+2, abs(H[i]-H[i+2])});
    }
    vector<ll> dist(N, INF); dist[0]=0;
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({0, 0}); //{その頂点への現時点の最小コスト, 頂点番号}

    while(!q.empty()){
        auto [c, to] = q.top(); q.pop();
        if(dist[to]!=c) continue; //確定している
        for(auto [nv, nc] : G[to]){
            if(dist[nv]<=c+nc) continue; //更新せず
            dist[nv]=c+nc;
            q.push({c+nc, nv});
        }
    }

    out(dist[N-1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve2();

    return 0;
}