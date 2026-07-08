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
 * 木の直径
 */
void solve() {
    ll N; cin >> N;
    ll sumc=0;
    ll tyokkei=0;
    vvpll G(N);
    rep(i, 0, N-1){
        ll a, b, c; cin >> a >> b >> c; a--; b--;
        sumc+=c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
    
    queue<ll> q1;  vl dist1(N, INF);
    q1.push(0); dist1[0]=0;
    ll mx1=-INF;
    while(!q1.empty()){
        auto v = q1.front(); q1.pop();
        for(auto [to, c] : G[v]){
            if(dist1[to]<=dist1[v]+c) continue;
            dist1[to]=dist1[v]+c;
            q1.push(to); chmax(mx1, dist1[to]);
        }
    }
    ll frm=0;
    rep(i, 0, N) if(dist1[i]==mx1){
        frm=i; break;
    }

    queue<ll> q2;  vl dist2(N, INF);
    q2.push(frm); dist2[frm]=0;
    ll mx2=-INF;
    while(!q2.empty()){
        auto v = q2.front(); q2.pop();
        for(auto [to, c] : G[v]){
            if(dist2[to]<=dist2[v]+c) continue;
            dist2[to]=dist2[v]+c;
            q2.push(to); chmax(mx2, dist2[to]);
        }
    }
    tyokkei=mx2;
    out(2*(sumc-tyokkei)+tyokkei);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}