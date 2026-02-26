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
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * ダイクストラ法
 * 頂点にcostがある最短経路問題->分からない
 * ->頂点のcostを辺に移す
 * ->無向辺==双方向の有向辺と見なせるから, 頂点v向きの辺のコスト==辺のコスト+頂点vのコストと見なす
 * ダイクストラは有向辺でも正しく動くから大丈夫
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vector<vpll> G(N);
    rep(i, 0, M){
        ll u, v, b; cin >> u >> v >> b;
        u--; v--;
        G[u].push_back({v, b+A[v]});
        G[v].push_back({u, b+A[u]});
    }
    vl dist(N, INF);
    dist[0]=A[0];
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({A[0], 0});
    while(!q.empty()){
        auto [c, to] = q.top(); q.pop();
        if(dist[to]!=c) continue;
        for(auto[nv, nc] : G[to]){
            if(dist[nv]<=nc+dist[to]) continue;
            dist[nv] = nc+dist[to];
            q.push({dist[nv], nv});
        }
    }
    rep(i, 1, N) cout << dist[i] << " ";
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