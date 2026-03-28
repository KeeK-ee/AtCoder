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

// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

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
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
// using bint = cpp_int;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

// 重み付きUnion-Find
struct PotentializedUnionFind {
    vector<int> par;
    vector<ll> weight;

    PotentializedUnionFind(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        weight.assign(n, 0);
    }

    int find(int x) {
        if (par[x] == x) {
            return x;
        }
        int root = find(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = root;
    }

    void merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        par[ry] = rx;
        weight[ry] = w + weight[x] - weight[y];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    ll diff(int x, int y) {
        // yの重み - xの重み (B_y - B_x)
        return weight[y] - weight[x];
    }
};

/**
 * 各頂点からの距離が最小の頂点は必ずその頂点への辺が存在
 * 
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vvpll G(N);
    rep(i, 0, N-1){
        rep(j, i+1, N){
            ll a; cin >> a;
            G[i].push_back({a, j});
            G[j].push_back({a, i});
        }
    }
    vvl C(N, vl(N));
    rep(i, 0, N){
        for(auto [c, to] : G[i]){
            C[i][to]=c; C[to][i]=c;
        }
    }
    rep(i, 0, N) sort(all(G[i]));
    set<tuple<ll, ll, ll>> s;
    rep(i, 0, N){
        auto [w, to]=G[i][0];
        if(s.count({i, to, w}) || s.count({to, i, w})) continue;
        else s.insert({i, to, w});
    }
    assert(sz(s)==N-1);
    vvpll GG(N);
    for(auto [u, v, w] : s){
        G[u].push_back({v, w}); G[v].push_back({u, w});
    }

    rep(i, 0, N){
        vl dist(N, INF); dist[i]=0;
        queue<ll> q; q.push(i);
        while(!q.empty()){
            auto v = q.front(); q.pop();
            for(auto [to, c] : GG[v]){
                if(dist[to]!=INF) continue;
                dist[to]=dist[v]+C[v][to];
                q.push(to);
            }
        }
        rep(j, 0, N) if(dist[j]!=C[i][j]){ No; return; }
    }
    Yes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}